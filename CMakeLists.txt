cmake_minimum_required(VERSION 3.30)
project(CENG209HW C)

set(CMAKE_C_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "gcc -g -Wall -Wextra -Wconversion -fsanitize=address -o my_program main.c")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_library(CENG209HW STATIC
        Player.h
        Inventory.h
        Item.h
        Map.h
        Room.h
        Creature.h
        Room.c
        Map.c
        main.c
        Player.c
        Inventory.c
        Creature.c
        Item.c)
