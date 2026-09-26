//
// Created by Eric Huiza on 9/24/26.
//

#ifndef EJERCICIO01_FUNCIONESAUXILIARES_H
#define EJERCICIO01_FUNCIONESAUXILIARES_H

#define CAP_ALU 20
#define CAP_NOT 40

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void cargarAlumnos(const char*, int*, int*, int&);
void cargarNotas(const char*, int*, double*, int&);

int buscarCodigo(const int*, int, int);
int buscarNota(const int*, int, int);

void generarReporte(const char*, int*, int*, int*, double*, int, int);

#endif //EJERCICIO01_FUNCIONESAUXILIARES_H
