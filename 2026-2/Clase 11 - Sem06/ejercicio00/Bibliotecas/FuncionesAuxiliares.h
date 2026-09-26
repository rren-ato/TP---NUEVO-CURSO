//
// Created by Eric Huiza on 9/24/26.
//

#ifndef EJERCICIO00_FUNCIONESAUXILIARES_H
#define EJERCICIO00_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>

#define CAP_ALU 6
#define CAP_CAT 6

using namespace std;

void cargarAlumnos(const char*, int*, char*, int&);
void cargarCategorias(const char*, char*, int&);
int buscarCategoria(const char*, char, int);

void generarReporte(const char*, const int*, const char*, const char*, int, int);

#endif //EJERCICIO00_FUNCIONESAUXILIARES_H
