#include "Server.hpp"
Server::Server()
{

}
void Server::run()
{
    if (newPlayersListener.listen(TCP_PORT) == sf::TcpListener::Error)
    {
        if (newPlayersListener.listen(TCP_PORT) == sf::TcpListener::Error) throw std::runtime_error("Server cannot bind to socket");
    }
    newPlayersListener.setBlocking(false);
    tickPacket.tick_number = 0;
    tickPacket.num_updates = 0;
    tick_number = 0;
    while (true) {
        tickPacket.tick_number = tick_number;
        tickPacket.num_updates = 0;
        updates_packet.clear();
        connectPlayer();
        tick();
    }
}
void Server::tick()
{
    sf::Clock clock;
    clock.restart();
    int updateCount = worldMap.checkCollisions(updates_packet);
    tickPacket.num_updates += updateCount;
    while (clock.getElapsedTime().asMilliseconds() < TICK_TIME_MILLIS)
    {
        for (std::map< std::unique_ptr<sf::TcpSocket> , WorldMap::ID_TYPE>::iterator player = players.begin(); player != players.end();)
        {
            (*player).first->setBlocking(false);
            sf::Packet packet;
            sf::Socket::Status status = (*player).first->receive(packet);
            while (status == sf::Socket::Status::Done)
            {
                UpdatePacket update;
                packet >> update;
#ifdef DO_DEBUG
                printf("\tReceived Update TYPE=%u ID=%u From\n", update.type, update.id);
#endif
                switch (update.type)
                {
                case UpdatePacket::UPDATE_ENTITY:
                {
                    Entity* e = worldMap.getEntity(update.id);
                    e->fromPacket(packet);
                    updates_packet << update;
                    e->toPacket(updates_packet);
                    tickPacket.num_updates++;
#ifdef DO_DEBUG
                    printf("\tUPDATE ENTITY ID=%u VELOCITY X=%f Y=%f\n", update.id, e->getVelocity().x, e->getVelocity().y);
#endif
                }
                break;
                case UpdatePacket::UPDATE_POLYGON:
                {
                    Polygon* p = (Polygon*) worldMap.getEntity(update.id);
                    p->fromPacket(packet);
                    updates_packet << update;
                    p->toPacket(updates_packet);
                    tickPacket.num_updates++;
#ifdef DO_DEBUG
                    printf("\tUPDATE Polygon ID=%u VELOCITY X=%f Y=%f\n", update.id, p->getVelocity().x, p->getVelocity().y);
#endif
                }
                break;
                case UpdatePacket::SHOOT:
                {
                    sf::Vector2f velocity;
                    packet >> velocity;
                    Entity* owner = worldMap.getEntity((*player).second);
                    sf::Vector2f position = owner->getCenter();
                    // std::cout << -std::atan2(velocity.y, velocity.x)*180/3.1415 << std::endl;
                    Rectangle* bullet = new Rectangle(position, velocity, sf::Vector2f(10, 50), -std::atan2(velocity.x, velocity.y) * 180 / 3.1415, (*player).second, sf::Color::Red);
                    auto id = worldMap.newEntity(bullet);
                    update.type = UpdatePacket::NEW_RECTANGLE;
                    update.id = id;
                    updates_packet << update;
                    bullet->toPacket(updates_packet);
                    tickPacket.num_updates++;
#ifdef DO_DEBUG
                    printf("\tUPDATE SHOOT ID=%u OWNER=%u", update.id, (*player).second);
#endif
                }
                break;
                }
                packet.clear();
                status = (*player).first->receive(packet);
            }
            if (status ==  sf::Socket::Status::Disconnected || status == sf::Socket::Status::Error)
            {
                auto id = (*player).second;
                worldMap.removeEntity(id);
                UpdatePacket update(UpdatePacket::REMOVE_ENTITY, id);
                updates_packet << update;
                tickPacket.num_updates++;
                player = players.erase(player);
            } else player++;
        }
        sf::sleep(sf::milliseconds(10));
    }
    //Ready to send tick
    sf::Packet header_packet;
    header_packet << tickPacket;
#ifdef DO_DEBUG
    //printf("Sending Tick #%u Updates=%i Players=%lu HEADER_SIZE=%lu UPDATES_SIZE=%lu\n", tickPacket.tick_number, tickPacket.num_updates, players.size(), header_packet.getDataSize(), updates_packet.getDataSize ());
#endif
    for (std::map< std::unique_ptr<sf::TcpSocket> , WorldMap::ID_TYPE>::iterator player = players.begin(); player != players.end(); player++)
    {
        (*player).first->setBlocking(true);
        (*player).first->send(header_packet);
        if (tickPacket.num_updates > 0) (*player).first->send(updates_packet);
    }

    worldMap.tick();
    tick_number++;
}
void Server::connectPlayer()
{
    HandshakeRequest req;
    HandshakeResponse res;
    sf::Packet req_packet, res_packet;
    std::unique_ptr<sf::TcpSocket> client(new sf::TcpSocket);
    sf::Socket::Status  s = newPlayersListener.accept(*client);
    if (s != sf::Socket::Status::Done) return;
    client->setBlocking(true);
    client->receive(req_packet);
#ifdef DO_DEBUG
    printf("Recieving Handshake Request Size = %lu\n", req_packet.getDataSize ());
#endif
    req_packet >> req;
    //Create new player entity
    Polygon* character = new Polygon(sf::Vector2f(0, 0), sf::Vector2f(0, 0), 50, 3, sf::Color(rand()%255, rand()%255, rand()%255));
    auto id = worldMap.newEntity((Entity*) character);
    //Send player response with their character id
    res.id = id;
    res_packet << res;
#ifdef DO_DEBUG
    printf("Sending Handshake Response Size = %lu\n", res_packet.getDataSize ());
#endif
    client->send(res_packet);
    //  std::cout << "Size: " << worldMap.entities.size() << std::endl;
    updateNewPlayer(*client, id);
    //Tell other players about new player
    UpdatePacket update;
    update.type = UpdatePacket::NEW_POLYGON;
    update.id = id;
    updates_packet << update;
    character->toPacket(updates_packet);
    tickPacket.num_updates++;

#ifdef DO_DEBUG
    std::cout << "Added IP: " << client->getRemoteAddress() << std::endl;
#endif
    players.insert(std::pair< std::unique_ptr<sf::TcpSocket> , WorldMap::ID_TYPE>(std::move(client), id) );
}
void Server::updateNewPlayer(sf::TcpSocket& socket, WorldMap::ID_TYPE id)
{
    sf::Packet header;
    TickPacket tp;
    tp.num_updates = 0;
    tp.tick_number = tick_number - 1;
    socket.setBlocking(true);
    sf::Packet updates;
    printf("New player id %d\n", id);
    for (auto p =  worldMap.entities.begin(); p != worldMap.entities.end(); p++)
    {
        if (p->first == id) continue;
        printf("Sending New player update %d ID=%d TYPE=%d\n", tp.num_updates, p->first, p->second->type);
        UpdatePacket up;
        up.id = p->first;
        switch (p->second->type)
        {
        case Entity::EntityType::polygon:
        {
            up.type = UpdatePacket::NEW_POLYGON;
            updates << up;
            Polygon* poly = (Polygon*) worldMap.getEntity(p->first);
            poly->toPacket(updates);
            tp.num_updates++;
        }
        break;
        case Entity::EntityType::rectangle:
        {
            up.type = UpdatePacket::NEW_RECTANGLE;
            updates << up;
            Rectangle* rect = (Rectangle*) worldMap.getEntity(p->first);
            rect->toPacket(updates);
            tp.num_updates++;
        }
        break;
        default:
            throw std::runtime_error("Type unknown");
            break;
        }
    }
    if (tp.num_updates > 0)
    {
        printf("Sending New player PACKETS TICK=%u UPDATE=%u\n", tp.tick_number, tp.num_updates);
        header << tp;
        socket.send(header);
        socket.send(updates);
    }
}
Server::~Server()
{

    for (std::map< std::unique_ptr<sf::TcpSocket> , WorldMap::ID_TYPE>::iterator player = players.begin(); player != players.end(); player++)
    {
        (*player).first->disconnect();
    }
    newPlayersListener.close();
}
