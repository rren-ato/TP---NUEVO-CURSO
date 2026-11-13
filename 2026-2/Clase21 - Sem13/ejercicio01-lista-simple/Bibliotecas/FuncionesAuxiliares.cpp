#include "FuncionesAuxiliares.h"

using namespace std;

// Cada dato leído entra en su posición: al terminar, la lista ya está ordenada.
void crearLista(const char* nombArch, struct Nodo*& lista) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    int dato;
    lista = nullptr;
    while (true) {
        arch >> dato;
        if (arch.eof()) {
            break;
        }
        // insertarAlFinal(lista, dato);
        // insertar(lista, dato);
        insertarOrdenada(lista, dato);
    }
}

// Inserta al inicio: no recorre la lista.
void insertar(struct Nodo*& lista, int d) {
    struct Nodo* nuevo;
    nuevo = new struct Nodo;
    nuevo->dato = d;
    nuevo->siguiente = lista; // apunta a la anterior cabeza de la lista
    lista = nuevo; // la cabeza de la lista apunta al nuevo nodo
}

// Hay que recorrer la lista hasta llegar al último nodo.
void insertarAlFinal(struct Nodo*& lista, int d) {
    struct Nodo* p = lista;
    struct Nodo* nuevo;
    nuevo = new struct Nodo;
    nuevo->dato = d;
    nuevo->siguiente = nullptr;
    if (lista == nullptr) {
        lista = nuevo;
    } else {
        while (p->siguiente != nullptr) {
            p = p->siguiente;
        }
        p->siguiente = nuevo;
    }
}

// p busca el primer dato mayor o igual y ant queda un nodo detrás.
void insertarOrdenada(struct Nodo*& lista, int d) {
    struct Nodo* p = lista;
    struct Nodo* ant = nullptr;
    struct Nodo* nuevo;
    nuevo = new struct Nodo;
    nuevo->dato = d;
    while (p != nullptr and d > p->dato) {
        ant = p;
        p = p->siguiente;
    }
    nuevo->siguiente = p;
    if (ant == nullptr) {
        lista = nuevo;
    } else {
        ant->siguiente = nuevo;
    }
}

void mostrarLista(const char* nombArch, struct Nodo* lista) {
    ofstream arch(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    struct Nodo* p = lista;
    while (p) {
        arch << setw(5) << p->dato;
        p = p->siguiente;
    }
    arch << endl;
}

// Devuelve la dirección del nodo encontrado, o nullptr.
struct Nodo* buscar(int dato, struct Nodo* lista) {
    struct Nodo* p = lista;
    while (p and p->dato != dato) {
        p = p->siguiente;
    }
    return p;
}

// La lista está ordenada: se avanza mientras el dato sea menor.
void eliminarDeLaLista(int dato, struct Nodo*& lista) {
    struct Nodo* p = lista;
    struct Nodo* ant = nullptr;
    while (p and p->dato < dato) {
        ant = p;
        p = p->siguiente;
    }
    if (p and p->dato == dato) {
        if (ant == nullptr) {
            lista = lista->siguiente;
        } else {
            ant->siguiente = p->siguiente;
        }
        delete p;
    }
}

// Elimina todos los nodos cuyo dato es menor que minimo.
void eliminarMenores(struct Nodo*& lista, int minimo) {
    struct Nodo* p = lista;
    struct Nodo* ant = nullptr;
    struct Nodo* sale;
    while (p) {
        if (p->dato >= minimo) {
            ant = p;
            p = p->siguiente;
        } else {
            sale = p;
            if (ant == nullptr) {
                lista = p->siguiente;
                p = lista;
            } else {
                ant->siguiente = p->siguiente;
                p = p->siguiente;
            }
            delete sale;
        }
    }
}

// Libera todos los nodos; al terminar lista vale nullptr.
void eliminarLista(struct Nodo*& lista) {
    struct Nodo* sale;
    while (lista) {
        sale = lista;
        lista = lista->siguiente;
        delete sale;
    }
}
