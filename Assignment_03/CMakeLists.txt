cmake_minimum_required(VERSION 3.22)
project(Assignment_03)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment_03 main.cpp MemorySpace.cpp MemorySpace.h MemoryPage.cpp MemoryPage.h processQueue.cpp processQueue.h LinkedList.cpp Node.cpp)
