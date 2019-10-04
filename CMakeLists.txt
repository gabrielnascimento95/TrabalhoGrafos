cmake_minimum_required(VERSION 3.14)
project(Grafos2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Grafos2
        main.cpp
        Grafo.cpp
        Floyd.cpp
        Aresta.cpp
        Dijkstra.cpp
        Kruskal.cpp
        No.cpp
        Prim.cpp
        )