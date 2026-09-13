#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& archivoEntrada, ofstream& reporte);
void cerrarArchivos(ifstream& archivoEntrada, ofstream& reporte);

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter = '-');

// Lee un registro {"id": .., "turno": "..", "pacientes": ..} de turnos.json
// descartando cada clave con ignore() hasta ':' o '"' y extrayendo el valor con >>.
void leerTurnoJSON(ifstream& archivoEntrada, int& id, char& turno, int& pacientes);

// Patron contador/suma/minimo/maximo para un turno.
void acumularTurno(int pacientes, int& n, int& suma, int& minimo, int& maximo);

// Recorre el archivo controlando el ciclo con peek() y separa turno M y turno T.
void analizarTurnos(ifstream& archivoEntrada,
    int& nM, int& sumaM, int& minM, int& maxM,
    int& nT, int& sumaT, int& minT, int& maxT);

void imprimirEncabezadoTurnos(ofstream& archivoReporte);
void imprimirFilaTurno(ofstream& archivoReporte, char turno,
    int n, int suma, int minimo, int maximo);

void generarReporte(ofstream& archivoReporte,
    int nM, int sumaM, int minM, int maxM,
    int nT, int sumaT, int minT, int maxT);

#endif
