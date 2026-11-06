//
// Created by Eric Huiza on 11/5/26.
//

#include "FuncionesAuxiliares.h"

void cargarDatos(const char* nombreArchivo, struct Alumno* alumnos, int& num) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    num = 0;
    struct Alumno alumno;
    while (archivo >> alumno.codigo) {
        archivo.ignore();
        alumno.nombre = leerCadena(archivo);
        archivo >> alumno.promedio;
        archivo.ignore();
        archivo >> alumno.ciclo;
        archivo.ignore();
        archivo >> alumno.matriculado;
        archivo.ignore();

        alumnos[num++] = alumno;
    }
}

char* leerCadena(ifstream& archivo, char delim) {
    char buffer[50];
    archivo.getline(buffer, 50, delim);
    if (archivo.eof()) {
        return nullptr;
    }
    char* cadena = new char[strlen(buffer) + 1];
    strcpy(cadena, buffer);
    return cadena;
}

void generarReporte(const char* nombreArchivo, const struct Alumno* alumnos, int num) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se pudo abrir el reporte" << endl;
        exit(1);
    }

    imprimirEncabezado(archivo);
    for (int i = 0; i < num; i++) {
        imprimirAlumno(archivo, alumnos[i]);
    }
}

void ordebarPorPromedio(struct Alumno* alumnos, int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (alumnos[i].promedio < alumnos[j].promedio) {
                intercambiar(alumnos[i], alumnos[j]);
            }
        }
    }
}

void ordenarPorNombre(struct Alumno* alumnos, int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (strcmp(alumnos[i].nombre, alumnos[j].nombre) > 0) {
                intercambiar(alumnos[i], alumnos[j]);
            }
        }
    }
}

void intercambiar(struct Alumno& a, struct Alumno& b) {
    struct Alumno aux = a;
    a = b;
    b = aux;
}

void imprimirEncabezado(ofstream& archivo) {
    archivo
        << left << setw(20) << "CODIGO"
        << setw(10) << "CICLO"
        << setw(15) << "PROMEDIO"
        << setw(10) << "MAT."
        << setw(30) << "NOMBRE"
        << endl;
}

void imprimirAlumno(ofstream& archivo, const struct Alumno& a) {
    archivo
        << left << setw(20) << a.codigo
        << setw(10) << a.ciclo
        << setw(15) << fixed << setprecision(2) << a.promedio
        << left << setw(10) << (a.matriculado ? "Si" : "No")
        << setw(30) << a.nombre
        << endl;
}

void liberarMemoria(struct Alumno* alumnos, int num) {
    for (int i = 0; i < num; i++) {
        liberarEstructura(alumnos[i]);
    }
    // delete[] alumnos;
}

void liberarEstructura(struct Alumno& a) {
    delete[] a.nombre;
}
