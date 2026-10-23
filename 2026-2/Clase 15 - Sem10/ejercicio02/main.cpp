#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    // Parte 2: lectura y escritura de cadenas
    probarLecturaPorPalabras("ArchivosDeDatos/palabras.txt");
    probarLecturaDeCampos("ArchivosDeDatos/campos.txt");
    probarGetline("ArchivosDeDatos/delimitador.txt");
    probarGet("ArchivosDeDatos/delimitador.txt");
    probarGetlineConArregloPequenio("ArchivosDeDatos/delimitador.txt");
    probarGetConArregloPequenio("ArchivosDeDatos/delimitador.txt");
    probarLecturaMixtaSinLimpiar("ArchivosDeDatos/mixta.txt");
    probarLecturaMixtaLimpiando("ArchivosDeDatos/mixta.txt");

    // Parte 3: busqueda, reemplazo y conversion
    probarMiStrstr();
    probarReemplazar();
    probarMiAtoi("ArchivosDeDatos/enteros.txt");
    probarMiAtof("ArchivosDeDatos/reales.txt");

    return 0;
}
