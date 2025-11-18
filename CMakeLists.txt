cmake_minimum_required(VERSION 4.0)
project(PrograEstructuras02 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(Impresor)
include_directories(Lector)
include_directories(Menu)

add_executable(PrograEstructuras02
        Menu/Menu.c
        Menu/Menu.h
        main.c
        Menu/Menu.c)
