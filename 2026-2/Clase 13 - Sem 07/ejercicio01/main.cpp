#include <iostream>
#include <iostream>

using namespace std;

int main() {
    int a = 10;

    // Imprime el valor de la variable
    cout << a << endl;
    // Imprime la dirección de la variable
    cout << &a << endl;

    int* p = &a;
    (*p)++; // Modifica el valor de la variable apuntada

    cout << "Dirección del puntero: " << &p << endl;
    cout << "Dirección que el puntero contiene: " << p << endl;
    cout << "Valor en la dirección que el puntero contiene: " << *p << endl;

    return 0;
}
