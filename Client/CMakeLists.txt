cmake_minimum_required(VERSION 3.25)
project(Client)

set(CMAKE_CXX_STANDARD 17)

add_executable(Client main.cpp Client.cpp Client.h ServerHandler.cpp ServerHandler.h Socket.cpp Socket.h
                Table.cpp Table.h Person.cpp Person.h Package.h)
