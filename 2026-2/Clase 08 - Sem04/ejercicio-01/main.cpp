#include <iostream>
#include <fstream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    ifstream productos;
    ifstream movimientos;
    ofstream reporte;

    if (!abrirArchivos(productos, movimientos, reporte)) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    generarReporte(productos, movimientos, reporte);

    cerrarArchivos(productos, movimientos, reporte);

    return 0;
}
