#cmake_minimum_required(VERSION 3.17)
#project(Puissance_4 C)

#set(CMAKE_C_STANDARD 99)

#add_executable(Puissance_4 main.c SDL.h)

cmake_minimum_required(VERSION 3.17)
project(Jeu_de_la_Vie C)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(SDL2_INCLUDE_DIR C:/SDL/SDL2-2.0.3/include/SDL2)
set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(Jeu_de_la_Vie main.c Vie.h Vie.c Fourmis.c Fourmis.h)

target_link_libraries(Jeu_de_la_Vie ${SDL2_LIBRARY})

