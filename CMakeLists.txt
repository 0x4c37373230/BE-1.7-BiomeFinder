cmake_minimum_required(VERSION 3.19.4)
project(1_7BEBiomeFinder C)

set(CMAKE_C_STANDARD 99)

add_executable(1_7BEBiomeFinder main.c
        partyMT.c partyMT.h
        oceanMonument.c oceanMonument.h
        miscFeatures.c miscFeatures.h
        clusterFinders.c clusterFinders.h
        simDistance.c simDistance.h
        cubiomes/finders.h cubiomes/finders.c
        cubiomes/generator.h cubiomes/generator.c
        cubiomes/layers.c cubiomes/layers.h
        cubiomes/javarnd.h)
