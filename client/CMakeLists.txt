set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

set(EXECUTABLE_NAME "game")
add_executable(${EXECUTABLE_NAME} main.cpp screens/screenmainmenu.cpp screens/screengame.cpp gui/cursor.cpp gui/textbox.cpp gui/button.cpp gui/form.cpp gui/sound.cpp gui/font.cpp ${COMMON_CPP})

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# copies sfml textures
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)

    # list of files for which we add a copy rule
    set(data_SHADOW resources/song.wav resources/hit.wav resources/levelup.wav resources/shoot.wav resources/Raleway-Light.ttf resources/mainmenu.png resources/background.png)

    foreach(item IN LISTS data_SHADOW)
        message(STATUS ${item})
        add_custom_command(
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
        )
    endforeach()
endif()

# files are only copied if a target depends on them
add_custom_target(font_Raleway ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/resources/Raleway-Light.ttf")
add_custom_target(mainmenu ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/resources/mainmenu.png")
add_custom_target(background ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/resources/background.png")

add_custom_target(song ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/resources/song.wav")
add_custom_target(hit_sound ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/resources/hit.wav")
add_custom_target(levelup_sound ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/resources/levelup.wav")
add_custom_target(shoot_sound ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/resources/shoot.wav")

