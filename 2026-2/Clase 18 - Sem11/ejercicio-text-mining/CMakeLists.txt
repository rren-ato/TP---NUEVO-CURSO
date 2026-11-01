cmake_minimum_required(VERSION 4.3)
project(ejercicio-text-mining)

set(CMAKE_CXX_STANDARD 20)

add_executable(ejercicio-text-mining main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h)
