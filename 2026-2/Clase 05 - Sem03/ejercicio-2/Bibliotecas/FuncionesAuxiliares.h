#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoReporte);
void cerrarArchivos(ifstream& archivoEntrada, ofstream& archivoReporte);

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter = '-');
void imprimirFecha(ofstream& archivoReporte, int dia, int mes, int anio);
void imprimirHora(ofstream& archivoReporte, int hora, int minuto, int segundo);
void imprimirFechaHora(ofstream& archivoReporte, long long clave);
void imprimirEncabezado(ofstream& archivoReporte);
void imprimirFila(ofstream& archivoReporte,
                  int dia, int mes, int anio,
                  int hora, int minuto, int segundo,
                  int codigo, int cantidad, double precioUnitario);
void imprimirTotales(ofstream& archivoReporte,
                     int movimientos, long long primerMov, long long ultimoMov,
                     double subtotalGeneral, double igv, double total);

void generarReporteFactura(ifstream& archivoEntrada, ofstream& archivoReporte);

#endif
