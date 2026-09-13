#include <iostream>
#include <fstream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    ifstream entrada;
    ofstream reporte;

    if (!abrirArchivos(entrada, reporte)) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    int cantidad;
    double suma, promedio;
    double maximo, minimo;
    int fechaMaximo, fechaMinimo;
    calcularEstadisticas(entrada, cantidad, suma, promedio,
                         maximo, fechaMaximo, minimo, fechaMinimo);

    reabrirEntrada(entrada);
    int sobre, bajo, iguales;
    contarRelativosAlPromedio(entrada, promedio, sobre, bajo, iguales);

    generarReporte(reporte, cantidad, suma, promedio,
                   maximo, fechaMaximo, minimo, fechaMinimo,
                   sobre, bajo, iguales);

    cerrarArchivos(entrada, reporte);

    return 0;
}
