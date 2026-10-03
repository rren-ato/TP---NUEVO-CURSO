#include <iostream>

using namespace std;

int main() {
    int* numeros = new int[5] { 1, 2, 3, 4, 5 };

    for (int i = 0; i < 5; i++) {
        cout << numeros[i] << endl;
    }

    delete[] numeros;

    return 0;
}
