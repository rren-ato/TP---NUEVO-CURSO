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
    int maxId, maxFecha, maxHora;
    int minId, minFecha, minHora;
    char maxSensor, minSensor;

    analizarLecturas(entrada, cantidad, suma, promedio,
                     maximo, maxId, maxSensor, maxFecha, maxHora,
                     minimo, minId, minSensor, minFecha, minHora);

    generarReporte(reporte, cantidad, suma, promedio,
                   maximo, maxId, maxSensor, maxFecha, maxHora,
                   minimo, minId, minSensor, minFecha, minHora);

    cerrarArchivos(entrada, reporte);

    return 0;
}
