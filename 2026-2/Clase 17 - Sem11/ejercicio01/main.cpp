#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    char mensaje[50] = "Hola Mundo";

    cout << "\"" << mensaje << "\"" << endl;
    cout << "Longitud: " << strlen(mensaje) << endl;

    strcat(mensaje, ", a todos");
    cout << "\"" << mensaje << "\"" << endl;
    cout << "Longitud: " << strlen(mensaje) << endl;

    char mensaje2[50] = "Hola Mundo, a todos";

    if (strcmp(mensaje, mensaje2) == 0) {
        cout << "Son iguales" << endl;
    }

    char* ptr = strstr(mensaje, "Mundo");
    if (ptr != nullptr) {
        cout << ptr << endl;
    }

    reemplazar(mensaje, "Mundo", "Galaxia");
    cout << mensaje << endl;

    return 0;
}
