#include "FuncionesAuxiliares.h"
#include <iomanip>

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoSalida) {
    archivoEntrada.open("ArchivosDeDatos/numeros.txt", ios::in);
    archivoSalida.open("ArchivosDeReporte/reporte.txt", ios::out);
    return archivoEntrada.is_open() and archivoSalida.is_open();
}

void calcularPromedio(ifstream& archivoEntrada, int& cantidad, double& suma, double& promedio) {
    double numero;
    suma = 0;
    cantidad = 0;

    while (archivoEntrada >> numero) {
        suma += numero;
        cantidad++;
    }

    // Ejemplo de uso del operador Ternario
    promedio = cantidad > 0 ? suma / cantidad : 0;

    // Ejemplo de uso de if-else
    // if (cantidad > 0) {
    //     promedio = suma / cantidad;
    // } else {
    //     promedio = 0;
    // }
}

void mostrarReporte(ofstream& archivoSalida, int cantidad, double suma, double promedio) {
    archivoSalida << fixed << setprecision(2);
    archivoSalida << "Cantidad de numeros: " << setw(10) << cantidad << endl;
    archivoSalida << "Suma total:          " << setw(10) << suma << endl;
    archivoSalida << "Promedio:            " << setw(10) << promedio << endl;
}

void cerrarArchivos(ifstream& archivoEntrada, ofstream& archivoSalida) {
    archivoEntrada.close();
    archivoSalida.close();
}
