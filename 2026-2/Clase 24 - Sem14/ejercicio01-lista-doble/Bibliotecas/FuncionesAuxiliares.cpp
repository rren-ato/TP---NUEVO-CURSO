#include "FuncionesAuxiliares.h"

// Cada dato leído se agrega al final: se respeta el orden del archivo.
void crearLista(const char* nombArch, struct NodoDoble*& lista) {
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
        // insertar(lista, dato);
        // insertarOrdenada(lista, dato);
        insertarAlFinal(lista, dato);
    }
}

// Inserta al inicio: el antiguo primero apunta hacia atrás al nuevo.
void insertar(struct NodoDoble*& lista, int d) {
    struct NodoDoble* nuevo;
    nuevo = new struct NodoDoble;
    nuevo->dato = d;
    nuevo->anterior = nullptr;
    nuevo->siguiente = lista;
    if (lista != nullptr) {
        lista->anterior = nuevo;
    }
    lista = nuevo;
}

// Hay que recorrer la lista hasta llegar al último nodo.
void insertarAlFinal(struct NodoDoble*& lista, int d) {
    struct NodoDoble* p = lista;
    struct NodoDoble* nuevo;
    nuevo = new struct NodoDoble;
    nuevo->dato = d;
    nuevo->siguiente = nullptr;
    if (lista == nullptr) {
        nuevo->anterior = nullptr;
        lista = nuevo;
    } else {
        while (p->siguiente != nullptr) {
            p = p->siguiente;
        }
        nuevo->anterior = p;
        p->siguiente = nuevo;
    }
}

// p busca el primer dato mayor o igual y ant queda un nodo detrás.
void insertarOrdenada(struct NodoDoble*& lista, int d) {
    struct NodoDoble* p = lista;
    struct NodoDoble* ant = nullptr;
    struct NodoDoble* nuevo;
    nuevo = new struct NodoDoble;
    nuevo->dato = d;
    while (p != nullptr and d > p->dato) {
        ant = p;
        p = p->siguiente;
    }
    nuevo->anterior = ant;
    nuevo->siguiente = p;
    if (p != nullptr) {
        p->anterior = nuevo;
    }
    if (ant == nullptr) {
        lista = nuevo;
    } else {
        ant->siguiente = nuevo;
    }
}

// Devuelve la dirección del nodo encontrado, o nullptr.
struct NodoDoble* buscar(int dato, struct NodoDoble* lista) {
    struct NodoDoble* p = lista;
    while (p and p->dato != dato) {
        p = p->siguiente;
    }
    return p;
}

// No hace falta ant: el nodo encontrado conoce a su anterior.
void eliminarDeLaLista(int dato, struct NodoDoble*& lista) {
    struct NodoDoble* p = buscar(dato, lista);
    if (p) {
        if (p->anterior == nullptr) {
            lista = p->siguiente;
        } else {
            p->anterior->siguiente = p->siguiente;
        }
        if (p->siguiente != nullptr) {
            p->siguiente->anterior = p->anterior;
        }
        delete p;
    }
}

// Elimina todos los nodos cuyo dato es menor que minimo.
void eliminarMenores(struct NodoDoble*& lista, int minimo) {
    struct NodoDoble* p = lista;
    struct NodoDoble* sale;
    while (p) {
        if (p->dato >= minimo) {
            p = p->siguiente;
        } else {
            sale = p;
            if (p->anterior == nullptr) {
                lista = p->siguiente;
            } else {
                p->anterior->siguiente = p->siguiente;
            }
            if (p->siguiente != nullptr) {
                p->siguiente->anterior = p->anterior;
            }
            p = p->siguiente;
            delete sale;
        }
    }
}

void mostrarLista(const char* nombArch, struct NodoDoble* lista) {
    ofstream arch(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    arch << left << setw(18) << "En orden:";
    imprimeEnOrden(arch, lista);
    arch << left << setw(18) << "En orden inverso:";
    imprimeEnOrdenInverso(arch, lista);
}

// Recorre del primero al último siguiendo el puntero siguiente.
void imprimeEnOrden(ofstream& arch, struct NodoDoble* lista) {
    struct NodoDoble* p = lista;
    while (p) {
        arch << right << setw(5) << p->dato;
        p = p->siguiente;
    }
    arch << endl;
}

// Primero llega al último nodo y luego regresa con el puntero anterior.
void imprimeEnOrdenInverso(ofstream& arch, struct NodoDoble* lista) {
    struct NodoDoble* p = lista;
    if (p) {
        while (p->siguiente) {
            p = p->siguiente;
        }
    }
    while (p) {
        arch << right << setw(5) << p->dato;
        p = p->anterior;
    }
    arch << endl;
}

// Libera todos los nodos; al terminar lista vale nullptr.
void eliminarLista(struct NodoDoble*& lista) {
    struct NodoDoble* sale;
    while (lista) {
        sale = lista;
        lista = lista->siguiente;
        delete sale;
    }
}
