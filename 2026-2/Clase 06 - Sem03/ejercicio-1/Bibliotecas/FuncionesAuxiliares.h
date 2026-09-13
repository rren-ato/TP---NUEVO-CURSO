#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoReporte);
void cerrarArchivos(ifstream& archivoEntrada, ofstream& archivoReporte);

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter = '-');
void imprimirFecha(ofstream& archivoReporte, int dia, int mes, int anio);
void imprimirHora(ofstream& archivoReporte, int hora, int minuto, int segundo);
void imprimirFechaEntera(ofstream& archivoReporte, int fecha);
void imprimirHoraEntera(ofstream& archivoReporte, int horaEntera);

void analizarLecturas(ifstream& archivoEntrada,
                      int& cantidad, double& suma, double& promedio,
                      double& maximo, int& maxId, char& maxSensor, int& maxFecha, int& maxHora,
                      double& minimo, int& minId, char& minSensor, int& minFecha, int& minHora);

void generarReporte(ofstream& archivoReporte,
                    int cantidad, double suma, double promedio,
                    double maximo, int maxId, char maxSensor, int maxFecha, int maxHora,
                    double minimo, int minId, char minSensor, int minFecha, int minHora);

#endif
