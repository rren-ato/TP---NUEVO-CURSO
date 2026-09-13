#include "FuncionesAuxiliares.h"
#include <iomanip>

#define TAM_LINEA 100

bool abrirArchivos(ifstream& entrada, ofstream& reporte) {
    entrada.open("ArchivosDeDatos/sensores.json", ios::in);
    reporte.open("ArchivosDeReporte/reporte.txt", ios::out);
    return entrada.is_open() and reporte.is_open();
}

void cerrarArchivos(ifstream& entrada, ofstream& reporte) {
    entrada.close();
    reporte.close();
}

void imprimirLineaSeparadora(ofstream& salida, int longitud, char caracter) {
    salida << setfill(caracter)
           << setw(longitud)
           << ""
           << setfill(' ') << endl;
}

void leerLecturaJSON(ifstream& entrada, int& id, char& sensor, double& lectura) {
    entrada.ignore(TAM_LINEA, ':'); // Ignorar hasta el primer ':'
    entrada >> id; // Leer el ID

    entrada.ignore(TAM_LINEA, ':'); // Ignorar hasta el siguiente ':'
    entrada.ignore(TAM_LINEA, '"'); // Ignorar hasta la primera comilla
    entrada >> sensor; // Leer el sensor

    entrada.ignore(TAM_LINEA, ':'); // Ignorar hasta el siguiente ':'
    entrada >> lectura; // Leer la lectura
    entrada.ignore(TAM_LINEA, '\n'); // Ignorar hasta el final de la línea
}

void acumularLectura(double lectura, int& n, double& suma, double& minimo, double& maximo) {
    if (n == 0 or lectura < minimo) {
        minimo = lectura;
    }
    if (n == 0 or lectura > maximo) {
        maximo = lectura;
    }
    suma += lectura;
    n++;
}

void analizarSensores(ifstream& entrada,
    int& nA, double& sumaA, double& minA, double& maxA,
    int& nB, double& sumaB, double& minB, double& maxB,
    int& ignoradas) {

    int id;
    char sensor;
    double lectura;

    nA = 0; sumaA = 0; minA = 0; maxA = 0;
    nB = 0; sumaB = 0; minB = 0; maxB = 0;
    ignoradas = 0;

    while (entrada.peek() == '{') {
        leerLecturaJSON(entrada, id, sensor, lectura);

        if (sensor == 'A') {
            acumularLectura(lectura, nA, sumaA, minA, maxA);
        } else if (sensor == 'B') {
            acumularLectura(lectura, nB, sumaB, minB, maxB);
        } else {
            ignoradas++;
        }
    }
}

void imprimirEncabezadoSensores(ofstream& salida) {
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
}

void imprimirFilaSensor(ofstream& salida, char sensor, int n, double suma, double minimo, double maximo) {
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
    int nB, double sumaB, double minB, double maxB, int ignoradas) {
    imprimirEncabezadoSensores(salida);

    imprimirFilaSensor(salida, 'A', nA, sumaA, minA, maxA);
    imprimirFilaSensor(salida, 'B', nB, sumaB, minB, maxB);

    imprimirLineaSeparadora(salida, 68);
    salida << "Lineas ignoradas: " << ignoradas << endl;
    imprimirLineaSeparadora(salida, 68);
}
