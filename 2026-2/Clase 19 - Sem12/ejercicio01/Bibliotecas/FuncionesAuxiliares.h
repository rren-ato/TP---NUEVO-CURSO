//
// Created by Eric Huiza on 11/5/26.
//

#ifndef EJERCICIO01_FUNCIONESAUXILIARES_H
#define EJERCICIO01_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Alumno.h"

using namespace std;

#define TAM_ALUMNOS 20

void cargarDatos(const char*, struct Alumno*, int&);
void generarReporte(const char*, const struct Alumno*, int);

void ordebarPorPromedio(struct Alumno*, int);
void ordenarPorNombre(struct Alumno*, int);

void intercambiar(struct Alumno&, struct Alumno&);

char* leerCadena(ifstream&, char = ',');

void imprimirEncabezado(ofstream&);
void imprimirAlumno(ofstream&, const struct Alumno&);
void liberarMemoria(struct Alumno*, int num);
void liberarEstructura(struct Alumno&);

#endif //EJERCICIO01_FUNCIONESAUXILIARES_H
