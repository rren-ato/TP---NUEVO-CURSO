#include "FuncionesAuxiliares.h"
#include <iomanip>

#define TAM_LINEA 200
#define ANCHO_NOMBRE 10

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoReporte) {
    archivoEntrada.open("ArchivosDeDatos/operaciones.csv", ios::in);
    archivoReporte.open("ArchivosDeReporte/reporte.txt", ios::out);
    return archivoEntrada.is_open() and archivoReporte.is_open();
}

void cerrarArchivos(ifstream& archivoEntrada, ofstream& archivoReporte) {
    archivoEntrada.close();
    archivoReporte.close();
}

void saltarComentarios(ifstream& archivoEntrada) {
    while (archivoEntrada.peek() == '#') {
        archivoEntrada.ignore(TAM_LINEA, '\n');
    }
}

int leerNombre(ifstream& archivoEntrada, ofstream& archivoReporte) {
    char c;
    int longitud = 0;
    while (archivoEntrada.get(c) and c != ',') {
        if (c >= 'a' and c <= 'z') {
            c = c - 32;
        }
        archivoReporte << c;
        longitud++;
    }
    return longitud;
}

bool leerOperacion(ifstream& archivoEntrada, ofstream& archivoReporte,
                   int& dia, int& mes, int& anio,
                   int& hora, int& minuto, int& segundo,
                   char& tipo, double& monto) {
    char sep;
    if (!(archivoEntrada >> dia)) {
        return false;
    }

    archivoEntrada >> sep >> mes >> sep >> anio
            >> sep >> hora >> sep >> minuto >> sep >> segundo >> sep;

    imprimirFecha(archivoReporte, dia, mes, anio);
    archivoReporte << "  ";
    imprimirHora(archivoReporte, hora, minuto, segundo);
    archivoReporte << "  ";
    int longitud = leerNombre(archivoEntrada, archivoReporte);
    for (int i = longitud; i < ANCHO_NOMBRE; i++) {
        archivoReporte << ' ';
    }

    archivoEntrada >> tipo >> sep >> monto;

    archivoReporte << right << setw(6) << tipo
           << fixed << setprecision(2) << setw(14) << monto << endl;

    return true;
}

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter) {
    archivoReporte << setfill(caracter)
           << setw(longitud)
           << ""
           << setfill(' ') << endl;
}

void imprimirFecha(ofstream& archivoReporte, int dia, int mes, int anio) {
    archivoReporte << setfill('0')
           << setw(2) << dia << "/"
           << setw(2) << mes << "/"
           << setw(4) << anio
           << setfill(' ');
}

void imprimirHora(ofstream& archivoReporte, int hora, int minuto, int segundo) {
    archivoReporte << setfill('0')
           << setw(2) << hora << ":"
           << setw(2) << minuto << ":"
           << setw(2) << segundo
           << setfill(' ');
}

void imprimirEncabezadoOperaciones(ofstream& archivoReporte) {
    archivoReporte << left  << setw(12) << "Fecha" << "  "
           << left  << setw(10) << "Hora" << "  "
           << left  << setw(10) << "Nombre"
           << right << setw(6)  << "Tipo"
           << right << setw(14) << "Monto" << endl;
}

void imprimirTotales(ofstream& archivoReporte, int nOps, double totalDep, double totalRet) {
    archivoReporte << fixed << setprecision(2);
    archivoReporte << left << setw(20) << "Operaciones:"     << right << setw(14) << nOps << endl;
    archivoReporte << left << setw(20) << "Total depósitos:" << right << setw(14) << totalDep << endl;
    archivoReporte << left << setw(20) << "Total retiros:"   << right << setw(14) << totalRet << endl;
    archivoReporte << left << setw(20) << "Saldo:"           << right << setw(14) << (totalDep - totalRet) << endl;
}

void generarReporte(ifstream& entrada, ofstream& archivoReporte) {
    imprimirLineaSeparadora(archivoReporte, 56);
    archivoReporte << "REPORTE DETALLADO DE OPERACIONES" << endl;
    imprimirLineaSeparadora(archivoReporte, 56);
    imprimirEncabezadoOperaciones(archivoReporte);
    imprimirLineaSeparadora(archivoReporte, 56);

    int dia, mes, anio, hora, minuto, segundo;
    char tipo;
    double monto;
    int nOps = 0;
    double totalDep = 0, totalRet = 0;

    saltarComentarios(entrada);
    while (
        leerOperacion(entrada, archivoReporte, dia, mes, anio,
            hora, minuto, segundo, tipo, monto)) {

        nOps++;
        if (tipo == 'D') {
            totalDep += monto;
        } else {
            totalRet += monto;
        }
        saltarComentarios(entrada);
    }

    imprimirLineaSeparadora(archivoReporte, 56);
    imprimirTotales(archivoReporte, nOps, totalDep, totalRet);
    imprimirLineaSeparadora(archivoReporte, 56);
}
