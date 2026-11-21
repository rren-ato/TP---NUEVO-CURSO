#ifndef LISTADOBLE_FUNCIONESAUXILIARES_H
#define LISTADOBLE_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>

#include "NodoDoble.h"

using namespace std;

// Creación de la lista
void crearLista(const char* nombArch, struct NodoDoble*& lista);
void insertar(struct NodoDoble*& lista, int d);
void insertarAlFinal(struct NodoDoble*& lista, int d);
void insertarOrdenada(struct NodoDoble*& lista, int d);
struct NodoDoble* buscar(int dato, struct NodoDoble* lista);

// Eliminación de nodos
void eliminarDeLaLista(int dato, struct NodoDoble*& lista);
void eliminarMenores(struct NodoDoble*& lista, int minimo);

// Reportes
void mostrarLista(const char* nombArch, struct NodoDoble* lista);
void imprimeEnOrden(ofstream& arch, struct NodoDoble* lista);
void imprimeEnOrdenInverso(ofstream& arch, struct NodoDoble* lista);

// Liberación de memoria
void eliminarLista(struct NodoDoble*& lista);

#endif //LISTADOBLE_FUNCIONESAUXILIARES_H
