#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& entrada, ofstream& reporte);
void cerrarArchivos(ifstream& entrada, ofstream& reporte);

void imprimirLineaSeparadora(ofstream& salida, int longitud, char caracter = '-');
void imprimirEncabezadoSensores(ofstream& salida);
void imprimirFilaSensor(ofstream& salida, char sensor,
    int n, double suma, double minimo, double maximo);

void leerLecturaJSON(ifstream& entrada, int& id, char& sensor, double& lectura);

void acumularLectura(double lectura, int& n, double& suma, double& minimo, double& maximo);

void analizarSensores(ifstream& entrada,
    int& nA, double& sumaA, double& minA, double& maxA,
    int& nB, double& sumaB, double& minB, double& maxB,
    int& ignoradas);

void generarReporte(ofstream& salida,
    int nA, double sumaA, double minA, double maxA,
    int nB, double sumaB, double minB, double maxB,
    int ignoradas);

#endif
