cmake_minimum_required(VERSION 3.24)
project(project_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(project_2 main.cpp CPheadquarters.cpp CPheadquarters.h Graph.cpp Graph.h VertexEdge.cpp VertexEdge.h MutablePriorityQueue.h)
