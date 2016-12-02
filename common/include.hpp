//Basic include file for most files
// #define DO_DEBUG

#ifndef COMMON_INCLUDE_HPP

#define COMMON_INCLUDE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

#include "Entities/entity.hpp"
#include "Entities/polygon.hpp"
#include "Entities/rectangle.hpp"

#include "World/worldmap.hpp"

#include "Network/HandshakeRequest.hpp"
#include "Network/HandshakeResponse.hpp"
#include "Network/TickPacket.hpp"
#include "Network/UpdatePacket.hpp"

#include <stdexcept>

#endif
