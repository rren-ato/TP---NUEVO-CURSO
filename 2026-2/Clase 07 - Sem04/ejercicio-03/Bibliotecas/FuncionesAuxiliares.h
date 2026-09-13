#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& csv, ofstream& json);
void cerrarArchivos(ifstream& csv, ofstream& json);

bool abrirArchivos2(ifstream& json, ofstream& reporte);
void cerrarArchivos2(ifstream& json, ofstream& reporte);

void imprimirLineaSeparadora(ofstream& salida, int longitud, char caracter = '-');

void imprimirFechaHoraISO(ofstream& salida,
    int anio, int mes, int dia, int hora, int minuto, int segundo);

long long fechaHora(int anio, int mes, int dia, int hora, int minuto, int segundo);

void imprimirFechaHoraISO(ofstream& salida, long long fechaHora);

// Reglas del calendario.
bool esBisiesto(int anio);
int diasDelMes(int mes, int anio);
bool fechaHoraValida(int dia, int mes, int anio, int hora, int minuto, int segundo);

// Lee una venta de ventas.csv (dd/mm/yyyy,hh:mm:ss,id,categoria,cantidad,precio)
// y devuelve el importe ya calculado. Devuelve false al llegar al fin de archivo.
bool leerVentaCSV(ifstream& csv, int& dia, int& mes, int& anio, int& hora, int& minuto,
    int& segundo, int& id, char& categoria, double& importe);

// Actualiza contador, total y los extremos (mayor y menor importe con su fecha).
void acumularVenta(double importe, long long fechaHora, int id,
    int& nVentas, double& total, double& mayor, long long& fechaHoraMayor, int& idMayor,
    double& menor, long long& fechaHoraMenor, int& idMenor);

// Escribe el objeto JSON de resumen.
void imprimirResumenJSON(ofstream& json, int nVentas, int ventasInvalidas, double total,
    double mayor, long long fechaHoraMayor, int idMayor, double menor,
    long long fechaHoraMenor, int idMenor);

// Escribe un objeto JSON por venta con la fecha y hora en formato ISO.
void imprimirVentaJSON(ofstream& json, int anio, int mes, int dia, int hora, int minuto,
    int segundo, int id, char categoria, double importe);

// Recorre ventas.csv una sola vez: escribe una linea JSON por venta valida y,
// al mismo tiempo, acumula los totales. Al final escribe el objeto de resumen.
void generarJSON(ifstream& csv, ofstream& json);

// Lee una fecha y hora ISO entre comillas y la devuelve como entero comparable.
long long leerFechaHoraISO(ifstream& json);

// Deja el cursor pasado el {" inicial y responde si la linea es una venta
// (primera clave "fechaHora"); si no, es el objeto de resumen ("ventas").
bool esLineaDeVenta(ifstream& json);

// Lee el objeto de resumen (ultima linea del JSON).
void leerResumenJSON(ifstream& json, int& nVentas, int& ventasInvalidas, double& total,
    double& mayor, long long& fechaHoraMayor, int& idMayor,
    double& menor, long long& fechaHoraMenor, int& idMenor);

// Lee un objeto JSON de venta avanzando hasta cada separador conocido.
void leerVentaJSON(ifstream& json, long long& fechaHora, int& id,
    char& categoria, double& importe);

void imprimirEncabezadoReporte(ofstream& reporte);
void imprimirFilaVenta(ofstream& reporte, long long fechaHora, int id, char categoria, double importe);
void imprimirExtremo(ofstream& reporte, double valor, int id, long long fechaHora);
void imprimirPie(ofstream& reporte, int nVentas, int ventasInvalidas, double total,
                 double mayor, long long fechaHoraMayor, int idMayor,
                 double menor, long long fechaHoraMenor, int idMenor);

// Vuelve a leer el JSON generado y produce el reporte final.
void generarReporte(ifstream& json, ofstream& reporte);

#endif
