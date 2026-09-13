#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream archivo("ArchivosDeDatos/numeros.txt");

    double numero;
    archivo >> numero;
    cout << fixed << setprecision(1) << numero << endl;

    archivo.seekg(-3, ios::cur);
    archivo >> numero;
    cout << fixed << setprecision(1) << numero << endl;

    archivo.seekg(-6, ios::end);
    archivo >> numero;
    cout << fixed << setprecision(1) << numero << endl;

    cout << endl;
    cout << endl;

    archivo.clear();
    archivo.seekg(0, ios::beg);

    while (archivo >> numero) {
        cout << fixed << setprecision(1) << numero << endl;
        cout << "Posición actual del cursor: "
        << archivo.tellg() << endl;
    }

    return 0;
}
