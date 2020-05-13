cmake_minimum_required(VERSION 3.15)
project(AVLtree)

set(CMAKE_CXX_STANDARD 14)

add_executable(AVLtree main.cpp AVLTree.h Container.h AVLTree.cpp)