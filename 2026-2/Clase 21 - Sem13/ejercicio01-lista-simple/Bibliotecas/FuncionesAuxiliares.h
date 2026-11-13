#ifndef LISTASIMPLE_FUNCIONESAUXILIARES_H
#define LISTASIMPLE_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Nodo.h"

void crearLista(const char* nombArch, struct Nodo*& lista);
void insertar(struct Nodo*& lista, int d);
void insertarAlFinal(struct Nodo*& lista, int d);
void insertarOrdenada(struct Nodo*& lista, int d);
void mostrarLista(const char* nombArch, struct Nodo* lista);
struct Nodo* buscar(int dato, struct Nodo* lista);
void eliminarDeLaLista(int dato, struct Nodo*& lista);
void eliminarMenores(struct Nodo*& lista, int minimo);
void eliminarLista(struct Nodo*& lista);

#endif //LISTASIMPLE_FUNCIONESAUXILIARES_H
