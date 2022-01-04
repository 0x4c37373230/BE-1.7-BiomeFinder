cmake_minimum_required(VERSION 3.20)
project(1_7BEBiomeFinder C)

set(CMAKE_C_STANDARD 99)

add_executable(1_7BEBiomeFinder main.c
        cubiomes/finders.h cubiomes/finders.c
        cubiomes/generator.h cubiomes/generator.c
        cubiomes/layers.c cubiomes/layers.h
        cubiomes/javarnd.h)
