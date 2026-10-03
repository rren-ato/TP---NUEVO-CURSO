//
// Created by Eric Huiza on 10/1/26.
//

#ifndef EJERCICIO02_FUNCIONESAUXILIARES_H
#define EJERCICIO02_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define CAPACIDAD 300

void cargarAlumnos(const char*, int*&, int*&, int&);
void cargarNotas(const char*, int*&, double*&, int&);

void ordenarPromediosSeleccion(double*, int);
void ordenarPromediosBurbuja(double*, int);

void ordenarAlumnosPorPromedio(int*, int*, double*, int);
void ordenarAlumnosPorCiclos(int*, int*, double*, int);

void intercambiar(double&, double&);
void intercambiar(int&, int&);

void calcularPromedios(int*, int*, double*, double*&, int, int);
double calcularPromedio(int, int*, double*, int);

void imprimirPromedios(const double*, int);
void imprimirRanking(const int*, const int*, double*, int);

#endif //EJERCICIO02_FUNCIONESAUXILIARES_H
