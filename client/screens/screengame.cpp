#include "screengame.hpp"
#include <string>
ScreenGame::ScreenGame()
{
}
void ScreenGame::doTick()
{
  sf::Packet header_packet;
  TickPacket tp;
  serverConnection.receive(header_packet);
  header_packet >> tp;
  //~ if (tp.tick_number != last_packet + 1)
  //~ {
  //~ std::cout << "Wrong packet num" << std::endl;
  //~ return;
  //~ }
  printf("Tick Header #%u updates=%u size=%u\n", tp.tick_number, tp.num_updates, header_packet.getDataSize());
  if (tp.num_updates > 0)
  {
    sf::Packet updates_packet;
    serverConnection.receive(updates_packet);
    printf("Tick Updates size=%u\n", updates_packet.getDataSize());
    for (uint i = 0; i < tp.num_updates; i++)
    {
      UpdatePacket update;
      updates_packet >> update;
      switch (update.type)
      {
      case UpdatePacket::REMOVE_ENTITY:
      {
        printf("Update REMOVE_ENTITY #%u ID=%u\n", i, update.id);
        worldMap.removeEntity(update.id);
      }
      break;
      case UpdatePacket::UPDATE_ENTITY:
      {
        printf("Update UPDATE_ENTITY #%u ID=%u\n", i, update.id);
        Entity* e = worldMap.getEntity(update.id);
        *e << updates_packet;
      }
      break;
      case UpdatePacket::UPDATE_POLYGON:
      {
        printf("Update UPDATE_POLYGON #%u ID=%u\n", i, update.id);
        Polygon* p = (Polygon*) worldMap.getEntity(update.id);
        *p << updates_packet;
      }
      break;
      case UpdatePacket::NEW_POLYGON:
      {
        printf("Update NEW_POLYGON #%u ID=%u\n", i, update.id);
        Polygon *p = new Polygon();
        *p << updates_packet;
        worldMap.addEntity(update.id, p);
      }
      break;
      default:
        printf("Update UNKOWN #%u ID=%i\n", i, update.id);
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
    printf("Sending Handshake Request Size = %u\n", req_packet.getDataSize ());
    serverConnection.send(req_packet);
    sf::Packet res_packet;
    serverConnection.receive(res_packet);
    printf("Recieving Handshake Response Size = %u\n", res_packet.getDataSize ());
    HandshakeResponse res;
    res_packet >> res;
  } else {
    throw std::runtime_error("Could not connect to Server");
  }
}
void ScreenGame::handleUserInput()
{
  Entity* me = worldMap.getEntity(player_id);
  sf::Vector2f velocity = me->getVelocity();
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

  if (fabs(velocity.x - me->getVelocity().x) > .01 || fabs(velocity.y - me->getVelocity().y) > .01 )
  {
    //~ printf("Changing Velocity ID=%u WAS=(X=%f Y=%f) NOW=(X=%f Y=%f)\n",player_id,me->getVelocity().x,me->getVelocity().y,velocity.x,velocity.y);
    sf::Packet packet;
    UpdatePacket update;
    update.id = player_id;
    update.type = UpdatePacket::UPDATE_ENTITY;
    packet << update;
    me->setVelocity(velocity);
    //~ printf("Me (X=%f Y=%f)\n",me->getVelocity().x,me->getVelocity().y);
    *me >> packet;
    serverConnection.send(packet);
  }
}
int ScreenGame::run(sf::RenderWindow &window)
{
  std::cout<<"Running"<< " " << SERVER_IP << std::endl;
  doHandshake();
  std::cout<<"finished handshake"<<std::endl;
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
    window.clear(sf::Color(0, 0, 0, 0));
    handleUserInput();
    doTick();
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

sf::IpAddress ScreenGame::SERVER_IP = sf::IpAddress("128.0.0.1");
std::string ScreenGame::playerName =  "";