#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoSalida);
void calcularPromedio(ifstream& archivoEntrada, int& cantidad, double& suma, double& promedio);
void mostrarReporte(ofstream& archivoSalida, int cantidad, double suma, double promedio);
void cerrarArchivos(ifstream& archivoEntrada, ofstream& archivoSalida);

#endif
