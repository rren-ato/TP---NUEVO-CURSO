cmake_minimum_required(VERSION 4.0)
project(Estructuras1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Estructuras1 main.cpp
        Bibliotecas/funciones.cpp
        Bibliotecas/funciones.h
        Bibliotecas/Fecha.h
        Bibliotecas/Empleado.h
        Bibliotecas/FuncionesCadenas.cpp
        Bibliotecas/FuncionesCadenas.h
        Bibliotecas/NuevoEmpleado.h)
