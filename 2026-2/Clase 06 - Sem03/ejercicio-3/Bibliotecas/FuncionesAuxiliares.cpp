#include "FuncionesAuxiliares.h"
#include <iomanip>

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoReporte) {
    archivoEntrada.open("ArchivosDeDatos/sensores.csv", ios::in);
    archivoReporte.open("ArchivosDeReporte/reporte.txt", ios::out);
    return archivoEntrada.is_open() and archivoReporte.is_open();
}

void cerrarArchivos(ifstream& archivoEntrada, ofstream& archivoReporte) {
    archivoEntrada.close();
    archivoReporte.close();
}

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter) {
    archivoReporte << setfill(caracter)
                   << setw(longitud)
           << ""
           << setfill(' ') << endl;
}

void analizarSensores(ifstream& archivoEntrada,
                      int& nA, double& sumaA, double& minA, double& maxA,
                      int& nB, double& sumaB, double& minB, double& maxB,
                      int& filasInvalidas) {
    int dia, mes, anio, hora, minuto, segundo;
    char sensor, sep;
    double lectura;

    nA = 0; sumaA = 0; minA = 0; maxA = 0;
    nB = 0; sumaB = 0; minB = 0; maxB = 0;
    filasInvalidas = 0;

    while (true) {
        archivoEntrada >> dia;

        if (archivoEntrada.eof()) break;

        archivoEntrada >> sep >> mes >> sep >> anio
                       >> sep >> hora >> sep >> minuto >> sep >> segundo
                       >> sep >> sensor
                       >> sep >> lectura;

        // Detectar filas incompletas.
        if (archivoEntrada.fail()) {
            archivoEntrada.clear();
            archivoEntrada.ignore(1000, '\n');
            filasInvalidas++;
            continue;
        }

        if (sensor == 'A') {
            if (nA == 0 or lectura < minA) minA = lectura;
            if (nA == 0 or lectura > maxA) maxA = lectura;
            sumaA += lectura;
            nA++;
        } else if (sensor == 'B') {
            if (nB == 0 or lectura < minB) minB = lectura;
            if (nB == 0 or lectura > maxB) maxB = lectura;
            sumaB += lectura;
            nB++;
        } else {
            filasInvalidas++;
        }
    }
}

void imprimirFilaSensor(ofstream& salida, char sensor,
                        int n, double suma, double minimo, double maximo) {
    double promedio = n > 0 ? suma / n : 0;
    double rango = maximo - minimo;

    salida << left  << setw(10) << sensor
           << right << setw(10) << n
           << fixed << setprecision(2)
           << setw(12) << promedio
           << setw(12) << minimo
           << setw(12) << maximo
           << setw(12) << rango << endl;
}

void generarReporte(ofstream& salida,
                    int nA, double sumaA, double minA, double maxA,
                    int nB, double sumaB, double minB, double maxB,
                    int filasInvalidas) {
    imprimirLineaSeparadora(salida, 68);
    salida << "REPORTE DE SENSORES A / B" << endl;
    imprimirLineaSeparadora(salida, 68);

    salida << left  << setw(10) << "Sensor"
           << right << setw(10) << "Lecturas"
           << right << setw(12) << "Promedio"
           << right << setw(12) << "Minimo"
           << right << setw(12) << "Maximo"
           << right << setw(12) << "Rango" << endl;
    imprimirLineaSeparadora(salida, 68);

    imprimirFilaSensor(salida, 'A', nA, sumaA, minA, maxA);
    imprimirFilaSensor(salida, 'B', nB, sumaB, minB, maxB);

    imprimirLineaSeparadora(salida, 68);
    salida << "Filas ignoradas: " << filasInvalidas << endl;
    imprimirLineaSeparadora(salida, 68);
}
