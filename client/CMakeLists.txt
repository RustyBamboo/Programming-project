include_directories(${CMAKEDEMO_SOURCE_DIR}/client)
link_directories(${CMAKEDEMO_BINARY_DIR}/client)

set(EXECUTABLE_NAME "game")
add_executable(${EXECUTABLE_NAME} main.cpp screens/screenmainmenu.cpp screens/screengame.cpp)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
