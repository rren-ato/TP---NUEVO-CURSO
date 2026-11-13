cmake_minimum_required(VERSION 3.20)
project(ejercicio01)

set(CMAKE_CXX_STANDARD 20)

add_executable(ejercicio01 main.cpp
        Bibliotecas/Nodo.h
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/FuncionesAuxiliares.cpp)
