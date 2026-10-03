//
// Created by Eric Huiza on 10/1/26.
//

#include "FuncionesAuxiliares.h"

void cargarAlumnos(const char* nombreArchivo,
    int*& codigos, int*& ciclos, int& num) {

    int bufferCodigos[CAPACIDAD];
    int bufferCiclos[CAPACIDAD];

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    int codigo;
    char c;
    num = 0;
    while (archivo >> codigo) {
        bufferCodigos[num] = codigo;
        archivo >> c >> bufferCiclos[num];
        num++;
    }

    codigos = new int[num];
    ciclos = new int[num];

    for (int i = 0; i < num; i++) {
        codigos[i] = bufferCodigos[i];
        ciclos[i] = bufferCiclos[i];
    }
}

void cargarNotas(const char* nombreArchivo,
    int*& codigos, double*& notas, int& num) {

    int bufferCodigos[CAPACIDAD];
    double bufferNotas[CAPACIDAD];

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    int codigo;
    char c;
    num = 0;
    while (archivo >> codigo) {
        bufferCodigos[num] = codigo;
        archivo >> c >> bufferNotas[num];
        num++;
    }

    codigos = new int[num];
    notas = new double[num];

    for (int i = 0; i < num; i++) {
        codigos[i] = bufferCodigos[i];
        notas[i] = bufferNotas[i];
    }
}

void intercambiar(double& n1, double& n2) {
    double aux = n1;
    n1 = n2;
    n2 = aux;
}

void intercambiar(int& n1, int& n2) {
    int aux = n1;
    n1 = n2;
    n2 = aux;
}

void calcularPromedios(int* codigos, int* codigoNotas, double* notas,
    double*& promedios, int numAlumnos, int numNotas) {

    promedios = new double[numAlumnos];

    for (int i = 0; i < numAlumnos; i++) {
        int codigo = codigos[i];
        double promedio = calcularPromedio(codigo, codigoNotas, notas, numNotas);
        promedios[i] = promedio;
    }
}

double calcularPromedio(int codigo, int* codigoNotas, double* notas, int numNotas) {
    double sum = 0.0;
    int numNotasPorAlumno = 0;
    for (int i = 0; i < numNotas; i++) {
        if (codigo ==  codigoNotas[i]) {
            sum += notas[i];
            numNotasPorAlumno++;
        }
    }
    return sum / numNotasPorAlumno;
}

void ordenarPromediosSeleccion(double* promedios, int num) {
    for (int i = 0; i < num - 1; i++) {
        int m = i;

        for (int j = i + 1; j < num; j++) {
            if (promedios[j] < promedios[m]) {
                m = j;
            }
        }

        if (m != i) {
            intercambiar(promedios[i], promedios[m]);
        }
        // cout << "Pasada " << i + 1 << endl;
        // imprimirNotas(promedios, num);
    }
}

void ordenarPromediosBurbuja(double* promedios, int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (promedios[j] > promedios[j + 1]) {
                intercambiar(promedios[j], promedios[j + 1]);
            }
        }
        // cout << "Pasada " << i + 1 << endl;
        // imprimirNotas(promedios, num);
    }
}

void ordenarAlumnosPorPromedio(int* codigos, int* ciclos, double* promedios, int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (promedios[j] < promedios[j + 1]) {
                intercambiar(codigos[j], codigos[j + 1]);
                intercambiar(ciclos[j], ciclos[j + 1]);
                intercambiar(promedios[j], promedios[j + 1]);
            }
        }
        // cout << "Pasada " << i + 1 << endl;
        // imprimirNotas(promedios, num);
    }
}

void ordenarAlumnosPorCiclos(int* codigos, int* ciclos, double* promedios, int num) {
    for (int i = 0; i < num - 1; i++) {
        int m = i;
        for (int j = i + 1; j < num; j++) {
            if (ciclos[j] > ciclos[m]) {
                m = j;
            }
        }

        if (m != i) {
            intercambiar(codigos[i], codigos[m]);
            intercambiar(ciclos[i], ciclos[m]);
            intercambiar(promedios[i], promedios[m]);
        }
    }
}

void imprimirPromedios(const double* notas, int numNotas) {
    for (int i = 0; i < numNotas; i++) {
        cout << setprecision(2) << fixed << notas[i] << " ";
    }
    cout << endl;
}

void imprimirRanking(const int* codigos, const int* ciclos, double* promedios, int num) {
    ofstream archivo("ArchivosDeReportes/ranking.txt");
    archivo << setw(20) << "CÓDIGO" << setw(20) << "CICLO" << setw(15) << "PROMEDIO" << endl;
    for (int i = 0; i < num; i++) {
        archivo
            << setw(20) << codigos[i]
            << setw(20) << ciclos[i]
            << setw(15) << setprecision(2) << fixed << promedios[i]
            << endl;
    }
}

