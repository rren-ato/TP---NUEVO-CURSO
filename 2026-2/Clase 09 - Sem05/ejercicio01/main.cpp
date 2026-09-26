#include <iostream>
#include <iomanip>

#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int numeros[CAPACIDAD];
    double promedio;
    cargarNumeros("ArchivosDeDatos/numeros.txt", numeros);
    imprimirNumeros(numeros);
    calcularPromedio(numeros, promedio);

    cout << "El promedio es: " << setprecision(2)
        << fixed << promedio << endl;

    return 0;
}
