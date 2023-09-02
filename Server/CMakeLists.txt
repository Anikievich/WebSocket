cmake_minimum_required(VERSION 3.20.0)
project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(Server main.cpp Server.cpp Server.h ClientHandler.cpp ClientHandler.h Socket.cpp Socket.h Person.cpp Person.h Table.cpp Table.h Package.h)
