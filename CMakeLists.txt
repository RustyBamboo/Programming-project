cmake_minimum_required(VERSION 2.6)
project(programmingproject)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

set(CMAKE_CXX_FLAGS "-g -W")
add_subdirectory(client build/client)
add_subdirectory(server build/server)

