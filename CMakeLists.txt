cmake_minimum_required(VERSION 3.15)
project(Game_of_Life)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DPROJECT_NAME="Game of Life")

find_package(SDL2 REQUIRED)

set(SDL2_TTF_INCLUDE_DIRS "/usr/include/SDL2")
set(SDL2_TTF_LIBRARIES "/usr/lib/x86_64-linux-gnu/libSDL2_ttf.so")

set(SOURCES
    src/GameWindow.cpp
    src/GameMenu.cpp
    src/GameArea.cpp
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR} 
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)