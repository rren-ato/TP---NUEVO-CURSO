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
    calcularPromedio(entrada, cantidad, suma, promedio);

    mostrarReporte(reporte, cantidad, suma, promedio);

    cerrarArchivos(entrada, reporte);

    return 0;
}
