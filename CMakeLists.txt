cmake_minimum_required(VERSION 3.26)
project(Projekt_SDiZO2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projekt_SDiZO2
        Bellman_Ford.cpp
        Bellman_Ford.h
        Colors.h
        Dijkstra.cpp
        Dijkstra.h
        Graph.cpp
        Graph.h
        Kruskal.cpp
        Kruskal.h
        Prim.cpp
        Prim.h
        Terazjuzsdizo.cpp)
