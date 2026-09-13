#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoReporte);
void cerrarArchivos(ifstream& archivoEntrada, ofstream& archivoReporte);

void imprimirLineaSeparadora(ofstream& archivoEntrada, int longitud, char caracter = '-');

// Recorre el CSV una sola vez y acumula por separado los sensores A y B.
void analizarSensores(ifstream& archivoEntrada,
                      int& nA, double& sumaA, double& minA, double& maxA,
                      int& nB, double& sumaB, double& minB, double& maxB,
                      int& filasInvalidas);

// Imprime una fila del reporte calculando promedio y rango del sensor.
void imprimirFilaSensor(ofstream& archivoReporte, char sensor,
                        int n, double suma, double minimo, double maximo);

void generarReporte(ofstream& archivoReporte,
                    int nA, double sumaA, double minA, double maxA,
                    int nB, double sumaB, double minB, double maxB,
                    int filasInvalidas);

#endif
