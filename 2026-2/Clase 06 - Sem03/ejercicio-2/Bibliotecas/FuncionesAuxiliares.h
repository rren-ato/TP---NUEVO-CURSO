#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoReporte);
void cerrarArchivos(ifstream& archivoEntrada, ofstream& archivoReporte);

void saltarComentarios(ifstream& archivoEntrada);
int leerNombre(ifstream& archivoEntrada, ofstream& archivoReporte);
bool leerOperacion(ifstream& archivoEntrada, ofstream& archivoReporte,
                   int& dia, int& mes, int& anio,
                   int& hora, int& minuto, int& segundo,
                   char& tipo, double& monto);

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter = '-');
void imprimirFecha(ofstream& archivoReporte, int dia, int mes, int anio);
void imprimirHora(ofstream& archivoReporte, int hora, int minuto, int segundo);
void imprimirEncabezadoOperaciones(ofstream& archivoReporte);
void imprimirTotales(ofstream& archivoReporte, int nOps, double totalDep, double totalRet);

void generarReporte(ifstream& archivoEntrada, ofstream& archivoReporte);

#endif
