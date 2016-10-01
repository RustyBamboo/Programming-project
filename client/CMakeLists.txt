cmake_minimum_required(VERSION 2.6)
project(programmingproject)

set(EXECUTABLE_NAME "game")
add_executable(${EXECUTABLE_NAME} main.cpp screens/screenmainmenu.cpp screens/screengame.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

