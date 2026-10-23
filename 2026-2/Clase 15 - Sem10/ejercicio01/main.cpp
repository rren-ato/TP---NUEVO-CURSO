#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    // Parte 1: concepto de cadena
    probarCaracterNulo();
    probarInicializacionYAsignacion();

    // Parte 3: funciones propias de cadenas
    probarMiStrlen();
    probarMiStrcpy();
    probarMiStrcmp();
    probarMiStrcat();
    probarPasaAMayusculas();
    probarInvertirCadena();

    return 0;
}
