#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& archivoCSV, ofstream& archivoJSON);
void cerrarArchivos(ifstream& archivoCSV, ofstream& archivoJSON);

bool abrirArchivos2(ifstream& archivoJSON, ofstream& archivoReporte);
void cerrarArchivos2(ifstream& archivoJSON, ofstream& archivoReporte);

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter = '-');

void imprimirFechaHoraISO(ofstream& archivoReporte,
    int anio, int mes, int dia, int hora, int minuto, int segundo);

// Empaqueta la fecha y la hora en un long long comparable (yyyymmddhhmmss).
long long fechaHora(int anio, int mes, int dia, int hora, int minuto, int segundo);

void imprimirFechaHoraISO(ofstream& archivoReporte, long long fechaHora);

// Reglas del calendario para decidir si una fecha existe.
bool esBisiesto(int anio);
int diasDelMes(int mes, int anio);
bool fechaHoraValida(int dia, int mes, int anio, int hora, int minuto, int segundo);

// Lee una reserva de reservas.csv
// (dd/mm/yyyy,hh:mm:ss,id,habitacion,noches,precioPorNoche) y devuelve el
// importe ya calculado (noches * precioPorNoche). Devuelve false al fin de archivo.
bool leerReservaCSV(ifstream& archivoCSV, int& dia, int& mes, int& anio,
    int& hora, int& minuto, int& segundo, int& id, char& habitacion, double& importe);

// Actualiza contador, total y los extremos (mayor y menor importe con su fecha).
void acumularReserva(double importe, long long fechaHora, int id,
    int& nReservas, double& total, double& mayor, long long& fechaHoraMayor, int& idMayor,
    double& menor, long long& fechaHoraMenor, int& idMenor);

// Escribe el objeto JSON de resumen (ultima linea del archivo).
void imprimirResumenJSON(ofstream& archivoJSON, int nReservas, int reservasInvalidas, double total,
    double mayor, long long fechaHoraMayor, int idMayor,
    double menor, long long fechaHoraMenor, int idMenor);

// Escribe un objeto JSON por reserva, con la fecha y hora en formato ISO.
void imprimirReservaJSON(ofstream& archivoJSON, int anio, int mes, int dia, int hora, int minuto,
    int segundo, int id, char habitacion, double importe);

// Recorre reservas.csv una sola vez: valida la fecha, escribe una linea JSON por
// reserva valida y acumula los totales. Al final escribe el objeto de resumen.
void generarJSON(ifstream& archivoCSV, ofstream& archivoJSON);

// Lee una fecha y hora ISO entre comillas y la devuelve como entero comparable.
long long leerFechaHoraISO(ifstream& archivoJSON);

// Deja el cursor pasado el {" inicial y responde si la linea es una reserva
// (primera clave "fechaHora"); si no, es el objeto de resumen ("reservas").
bool esLineaDeReserva(ifstream& archivoJSON);

void leerResumenJSON(ifstream& archivoJSON, int& nReservas, int& reservasInvalidas, double& total,
    double& mayor, long long& fechaHoraMayor, int& idMayor,
    double& menor, long long& fechaHoraMenor, int& idMenor);

void leerReservaJSON(ifstream& archivoJSON, long long& fechaHora, int& id,
    char& habitacion, double& importe);

void imprimirEncabezadoReporte(ofstream& archivoReporte);
void imprimirFilaReserva(ofstream& archivoReporte, long long fechaHora, int id, char habitacion, double importe);
void imprimirExtremo(ofstream& archivoReporte, double valor, int id, long long fechaHora);
void imprimirTotales(ofstream& archivoReporte, int nReservas, int reservasInvalidas, double total,
    double mayor, long long fechaHoraMayor, int idMayor,
    double menor, long long fechaHoraMenor, int idMenor);

// Vuelve a leer el JSON generado y produce el reporte final.
void generarReporte(ifstream& archivoJSON, ofstream& archivoReporte);

#endif
