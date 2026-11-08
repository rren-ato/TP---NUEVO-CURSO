cmake_minimum_required(VERSION 4.0)
project(CapturasVehiculos)

set(CMAKE_CXX_STANDARD 20)

add_executable(CapturasVehiculos main.cpp
        Bibliotecas/Vehiculo.h
        Bibliotecas/Captura.h
        Bibliotecas/funcionesAdicionales.cpp
        Bibliotecas/funcionesAdicionales.h
        Bibliotecas/Infraccion.h)
