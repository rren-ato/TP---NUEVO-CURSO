#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoReporte);
void reabrirEntrada(ifstream& archivoEntrada);
void cerrarArchivos(ifstream& archivoEntrada, ofstream& archivoReporte);

void calcularEstadisticas(ifstream& archivoEntrada,
                          int& cantidad, double& suma, double& promedio,
                          double& maximo, int& fechaMaximo,
                          double& minimo, int& fechaMinimo);

void contarRelativosAlPromedio(ifstream& archivoEntrada, double promedio,
                               int& sobre, int& bajo, int& iguales);

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter = '-');
void imprimirFechaEntera(ofstream& archivoReporte, int fecha);
void generarReporte(ofstream& archivoReporte,
                    int cantidad, double suma, double promedio,
                    double maximo, int fechaMaximo,
                    double minimo, int fechaMinimo,
                    int sobre, int bajo, int iguales);

#endif
