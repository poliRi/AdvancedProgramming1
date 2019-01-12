cmake_minimum_required(VERSION 3.12)
project(prj2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(prj2 main.cpp Astar.h Astar.cpp BFS.cpp BFS.h DFS.cpp DFS.h FileCacheManager.cpp FileCacheManager.h GreedyBFS.cpp GreedyBFS.h interface.h Matrix.cpp Matrix.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h ServerSide.cpp ServerSide.h StringReverser.cpp StringReverser.h Timeout.cpp Timeout.h Utils.cpp Utils.h)