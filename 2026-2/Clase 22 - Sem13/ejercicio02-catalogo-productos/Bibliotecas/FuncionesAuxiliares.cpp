#include "FuncionesAuxiliares.h"

void crearLista(const char* nombArch, struct Nodo*& lista) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    struct Producto productoNuevo {};
    lista = nullptr;
    while (true) {
        leerProducto(arch, productoNuevo);
        if (arch.eof()) {
            break;
        }
        insertarOrdenada(lista, productoNuevo);
    }
}

void agregarProductos(const char* nombArch, struct Nodo*& lista) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    struct Producto productoNuevo{};
    int codProd;
    while (true) {
        arch >> codProd;
        if (arch.eof()) {
            break;
        }
        arch.get();
        if (buscarProducto(codProd, lista) == nullptr) {
            productoNuevo.codigo = codProd;
            leerDatosProducto(arch, productoNuevo);
            insertarOrdenada(lista, productoNuevo);
        } else {
            // código repetido: se salta la línea
            while (arch.get() != '\n') {
            }
        }
    }
}

void retirarProductos(const char* nombArch, struct Nodo*& lista) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    int codProd;
    while (true) {
        arch >> codProd;
        if (arch.eof()) {
            break;
        }
        eliminarDeLaLista(codProd, lista);
    }
}

void leerProducto(ifstream& arch, struct Producto& producto) {
    arch >> producto.codigo;
    if (arch.eof()) {
        return;
    }
    arch.get();
    leerDatosProducto(arch, producto);
}

// Lee lo que sigue al código: descripción, precio y stock
void leerDatosProducto(ifstream& arch, struct Producto& producto) {
    producto.descripcion = leerCadenaExacta(arch, ',');
    arch >> producto.precio;
    arch.get();
    arch >> producto.stock;
    producto.numVen = 0;
    producto.unidadesVendidas = 0;
    producto.montoVendido = 0;
    producto.stockFinal = producto.stock;
}

char* leerCadenaExacta(ifstream& arch, char delimitador) {
    char cadena[100];
    char* cad;
    arch.getline(cadena, 100, delimitador);
    cad = new char[strlen(cadena) + 1];
    strcpy(cad, cadena);
    return cad;
}

void insertarOrdenada(struct Nodo*& lista, struct Producto& producto) {
    struct Nodo* p = lista;
    struct Nodo* ant = nullptr;
    struct Nodo* nuevo;
    nuevo = new struct Nodo;
    nuevo->producto = producto;
    while (p != nullptr and producto.codigo > p->producto.codigo) {
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

struct Nodo* buscarProducto(int codProd, struct Nodo* lista) {
    struct Nodo* p = lista;
    while (p and p->producto.codigo < codProd) {
        p = p->siguiente;
    }
    if (p == nullptr or p->producto.codigo > codProd) {
        return nullptr;
    } else {
        return p;
    }
}

void eliminarDeLaLista(int codProd, struct Nodo*& lista) {
    struct Nodo* p = lista;
    struct Nodo* ant = nullptr;
    while (p and p->producto.codigo < codProd) {
        ant = p;
        p = p->siguiente;
    }
    if (p and p->producto.codigo == codProd) {
        if (ant == nullptr) {
            lista = lista->siguiente;
        } else {
            ant->siguiente = p->siguiente;
        }
        delete[] p->producto.descripcion;
        delete p;
    }
}

void cargarVentas(const char* nombArch, struct Nodo* lista) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    struct Nodo* p;
    int codProd;
    while (true) {
        arch >> codProd;
        if (arch.eof()) {
            break;
        }
        arch.get();
        p = buscarProducto(codProd, lista);
        if (p != nullptr) {
            modificarProducto(arch, p->producto);
        } else {
            // producto inexistente: se salta la línea
            while (arch.get() != '\n') {}
        }
    }
}

void modificarProducto(ifstream& arch, struct Producto& producto) {
    int n;
    n = producto.numVen;
    if (n == MAX_VENTAS) {
        // el arreglo está lleno: se ignora la venta
        while (arch.get() != '\n') {
        }
        return;
    }
    arch >> producto.ventas[n].fecha;
    arch.get();
    arch >> producto.ventas[n].cantidad;
    producto.numVen++;
}

void calcularTotales(struct Nodo* lista) {
    struct Nodo* p = lista;
    while (p) {
        calculaTotalesDeProducto(p->producto);
        p = p->siguiente;
    }
}

void calculaTotalesDeProducto(struct Producto& producto) {
    int suma = 0;
    for (int i = 0; i < producto.numVen; ++i) {
        suma += producto.ventas[i].cantidad;
    }
    producto.unidadesVendidas = suma;
    producto.montoVendido = suma * producto.precio;
    producto.stockFinal = producto.stock - suma;
}

void eliminarSinVentas(struct Nodo*& lista) {
    struct Nodo* p = lista;
    struct Nodo* ant = nullptr;
    struct Nodo* sale;
    while (p) {
        if (p->producto.numVen > 0) {
            ant = p;
            p = p->siguiente;
        } else {
            // no tuvo ventas
            sale = p;
            if (ant == nullptr) {
                lista = p->siguiente;
                p = lista;
            } else {
                ant->siguiente = p->siguiente;
                p = p->siguiente;
            }
            delete[] sale->producto.descripcion;
            delete sale;
        }
    }
}

void mostrarLista(const char* nombArch, const char* titulo, struct Nodo* lista) {
    ofstream arch(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    int cantidad = 0;
    int unidades = 0;
    double monto = 0;
    arch.precision(2);
    arch << fixed;
    imprimeEncabezado(arch, titulo);
    struct Nodo* p = lista;
    while (p) {
        imprimeProducto(arch, p->producto);
        cantidad++;
        unidades += p->producto.unidadesVendidas;
        monto += p->producto.montoVendido;
        p = p->siguiente;
    }
    imprimeResumen(arch, cantidad, unidades, monto);
}

void imprimeEncabezado(ofstream& arch, const char* titulo) {
    arch << titulo << endl;
    imprimeLinea(arch, '=', 60);
    arch << left << setw(10) << "CÓDIGO" << setw(28) << "DESCRIPCIÓN"
            << right << setw(12) << "PRECIO" << setw(10) << "STOCK" << endl;
    imprimeLinea(arch, '=', 60);
}

// Los totales de ventas solo se imprimen si ya se cargaron las ventas.
void imprimeResumen(ofstream& arch, int cantidad, int unidades, double monto) {
    arch << left << setw(23) << "Cantidad de productos:" << cantidad << endl;
    if (unidades > 0) {
        arch << setw(23) << "Unidades vendidas:" << unidades << endl;
        arch << setw(23) << "Monto total vendido:" << monto << endl;
    }
}

void imprimeProducto(ofstream& arch, const struct Producto& producto) {
    arch << left << setw(10) << producto.codigo << setw(28)
            << producto.descripcion << right << setw(12) << producto.precio
            << setw(10) << producto.stock << endl;
    for (int i = 0; i < producto.numVen; ++i) {
        if (i == 0) {
            arch << setw(10) << "Ventas:" << endl;
        }
        arch << setw(3) << "";
        imprimeFecha(arch, producto.ventas[i].fecha);
        arch << setw(10) << producto.ventas[i].cantidad
                << setw(3) << "u." << endl;
    }
    if (producto.numVen > 0) {
        arch << setw(22) << "Unidades vendidas =" << setw(4) << producto.unidadesVendidas
                << setw(10) << "Monto =" << setw(10) << producto.montoVendido
                << setw(16) << "Stock final =" << setw(4) << producto.stockFinal;
        if (producto.stockFinal <= STOCK_MINIMO) {
            arch << setw(12) << "<< REPONER";
        }
        arch << endl;
    }
    imprimeLinea(arch, '-', 60);
}

// fecha llega como aaaammdd y se imprime como dd/mm/aaaa.
void imprimeFecha(ofstream& arch, int fecha) {
    int dd = fecha % 100;
    int mm = fecha / 100 % 100;
    int aa = fecha / 10000;
    arch.fill('0');
    arch << right << setw(2) << dd << '/' << setw(2) << mm << '/' << aa;
    arch.fill(' ');
}

void imprimeLinea(ofstream& arch, char car, int n) {
    for (int i = 0; i < n; i++) {
        arch.put(car);
    }
    arch << endl;
}

void eliminarLista(struct Nodo*& lista) {
    struct Nodo* sale;
    while (lista) {
        sale = lista;
        lista = lista->siguiente;
        delete[] sale->producto.descripcion;
        delete sale;
    }
}
