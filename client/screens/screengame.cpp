#include "screengame.hpp"
#include <string>
double ScreenGame::ZOOM_FACTOR = 2.0;
ScreenGame::ScreenGame() : player_id(0), created(false)
{
}
void ScreenGame::doTick()
{
	sf::Packet header_packet;
	TickPacket tp;
	sf::Socket::Status status = serverConnection.receive(header_packet);
        if (status == sf::Socket::Status::Disconnected) throw std::runtime_error("Server disconnected, closing");
        if (status == sf::Socket::Status::Error) throw std::runtime_error("Socket error, closing");
	header_packet >> tp;
#ifdef DO_DEBUG
	printf("Tick Header #%u updates=%u size=%lu\n",tp.tick_number,tp.num_updates,header_packet.getDataSize());
#endif
  if (tp.num_updates > 0)
  {
    sf::Packet updates_packet;
    serverConnection.receive(updates_packet);
#ifdef DO_DEBUG
    printf("Tick Updates size=%lu\n",updates_packet.getDataSize());
#endif
    for (uint i = 0; i < tp.num_updates; i++)
    {
      UpdatePacket update;
      updates_packet >> update;
      switch (update.type)
      {
        case UpdatePacket::REMOVE_ENTITY:
          {
#ifdef DO_DEBUG
            printf("Update REMOVE_ENTITY #%u ID=%u\n",i,update.id);
#endif
            worldMap.removeEntity(update.id);
          }
          break;
        case UpdatePacket::UPDATE_ENTITY:
          {
#ifdef DO_DEBUG
            printf("Update UPDATE_ENTITY #%u ID=%u\n",i,update.id);
#endif
            Entity* e = worldMap.getEntity(update.id);
            e->fromPacket(updates_packet);
          }
          break;
        case UpdatePacket::UPDATE_POLYGON:
          {
#ifdef DO_DEBUG
            printf("Update UPDATE_POLYGON #%u ID=%u\n",i,update.id);
#endif
            Polygon* p = (Polygon*) worldMap.getEntity(update.id);
            p->fromPacket(updates_packet);
          }
          break;
        case UpdatePacket::NEW_POLYGON:
          {
#ifdef DO_DEBUG
            printf("Update NEW_POLYGON #%u ID=%u\n",i,update.id);
#endif
            if (update.id == player_id) created = true;
            Polygon *p = new Polygon();
            p->fromPacket(updates_packet);
            worldMap.addEntity(update.id,p);
          }
          break;
        default:
#ifdef DO_DEBUG
          printf("Update UNKOWN #%u ID=%i\n",i,update.id);
#endif
          break;
      }
      //Do update depending on type
    }
  }
  worldMap.tick();
}
void ScreenGame::doHandshake()
{
  if (serverConnection.connect(SERVER_IP, TCP_PORT) == sf::Socket::Done) {
    serverConnection.setBlocking(true);
		HandshakeRequest req;
		sf::Packet req_packet;
		req_packet << req;
#ifdef DO_DEBUG
    printf("Sending Handshake Request Size = %lu\n",req_packet.getDataSize ());
#endif
		serverConnection.send(req_packet);
		sf::Packet res_packet;
		serverConnection.receive(res_packet);
#ifdef DO_DEBUG
    printf("Recieving Handshake Response Size = %lu\n",res_packet.getDataSize ());
#endif
		HandshakeResponse res;
		res_packet >> res;
    player_id = res.id;

    //Expect tick with all other entities
	} else {
    throw std::runtime_error("Could not connect to Server");
  }
}
void ScreenGame::handleUserInput()
{
  if (!created) return;
  Polygon* me_ptr = (Polygon*) worldMap.getEntity(player_id); //Create a copy of me
  sf::Vector2f velocity = me_ptr->getVelocity();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    velocity.x = -5.0;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    velocity.x = 5.0;
  }
  else velocity.x = 0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    velocity.y = -5.0;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    velocity.y = 5.0;
  } else velocity.y = 0;

  //If velocity changed, send out update
  if (abs(velocity.x - me_ptr->getVelocity().x) > .01 || abs(velocity.y - me_ptr->getVelocity().y) > .01 )
  {
    sf::Packet packet;
    UpdatePacket update;
    update.id = player_id;
    update.type = UpdatePacket::UPDATE_POLYGON;
    packet << update;
    me_ptr->setVelocity(velocity);
    me_ptr->toPacket(packet);
    serverConnection.send(packet);
  }
}
int ScreenGame::run(sf::RenderWindow &window)
{
  std::cout << "Connecting to server: " << SERVER_IP << std::endl;
  doHandshake();
  sf::Event Event;
  while (window.isOpen())
  {
    while (window.pollEvent(Event))
    {
      if (Event.type == sf::Event::Closed)
      {
        return (-1);
      }
      else if (Event.type == sf::Event::KeyPressed)
      {
        switch (Event.key.code) {
        case sf::Keyboard::Escape:
          return (-1); //Goes to Pause Menu
        }
      }
    }
    auto view = window.getDefaultView();
    view.zoom(ZOOM_FACTOR);
    window.setView(view);
    window.clear(sf::Color(0, 0, 0, 0));
    handleUserInput();
    doTick();

//if (created) worldMap.getEntity(player_id) -> setView(window);
    worldMap.draw(window);
    window.display();
  }
}

void ScreenGame::setServerIP (const sf::IpAddress &address) {
  SERVER_IP = address;
}
void ScreenGame::setName(const std::string &_name) {
  playerName = _name;
}

sf::IpAddress ScreenGame::SERVER_IP = sf::IpAddress("127.0.0.1");
std::string ScreenGame::playerName =  "";
