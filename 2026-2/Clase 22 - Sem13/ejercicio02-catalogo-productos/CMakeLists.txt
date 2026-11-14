cmake_minimum_required(VERSION 3.20)
project(catalogo-productos)

set(CMAKE_CXX_STANDARD 20)

add_executable(catalogo-productos main.cpp
        Bibliotecas/Venta.h
        Bibliotecas/Producto.h
        Bibliotecas/Nodo.h
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/FuncionesAuxiliares.cpp)
