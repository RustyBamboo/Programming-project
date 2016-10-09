cmake_minimum_required(VERSION 2.6)
project(programmingproject)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
set(COMMON_CPP "../common/World/worldmap" "../common/Entities/entity.cpp" 
	"../common/Entities/polygon.cpp" "../common/Entities/rectangle.cpp"
	"../common/Network/HandshakeRequest.cpp" "../common/Network/HandshakeResponse.cpp"
	"../common/Network/TickPacket.cpp" "../common/Network/UpdatePacket.cpp")
set(CMAKE_CXX_FLAGS "-g -W")
add_subdirectory(client build/client)
add_subdirectory(server build/server)
