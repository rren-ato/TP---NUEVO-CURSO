cmake_minimum_required(VERSION 3.20)
project(courier-lista-simple)

set(CMAKE_CXX_STANDARD 20)

add_executable(courier-lista-simple main.cpp
        Bibliotecas/Fecha.h
        Bibliotecas/Persona.h
        Bibliotecas/Tarifa.h
        Bibliotecas/Destino.h
        Bibliotecas/Entrega.h
        Bibliotecas/Envio.h
        Bibliotecas/Nodo.h
        Bibliotecas/TotalZona.h
        Bibliotecas/Resumen.h
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/FuncionesAuxiliares.cpp)
