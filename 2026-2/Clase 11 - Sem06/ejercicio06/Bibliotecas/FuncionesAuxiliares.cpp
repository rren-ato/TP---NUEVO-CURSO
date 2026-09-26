//
// Created by Eric Huiza on 9/24/26.
//

#include "FuncionesAuxiliares.h"

bool leerProducto(ifstream& archivo, int& codigo, char& categoria,
    double& precio, int& stock, bool& importado) {
    char coma;
    if (!(archivo >> codigo)) {
        return false;
    }
    archivo >> coma >> categoria >> coma >> precio >> coma >> stock >> coma >> importado;
    return true;
}

// Devuelve la posicion donde quedo el producto, o -1 si no hay capacidad
int insertarOrdenado(int* codigos, char* categorias, double* precios, int* stocks,
    bool* importados, int capacidad, int& longitud,
    int codigo, char categoria, double precio, int stock, bool importado) {
    if (longitud >= capacidad) {
        return -1;
    }

    int i;
    for (i = longitud - 1; i >= 0 and codigos[i] > codigo; i--) {
        codigos[i + 1] = codigos[i];           // desplazamos a la derecha
        categorias[i + 1] = categorias[i];     // TODOS los arreglos
        precios[i + 1] = precios[i];
        stocks[i + 1] = stocks[i];
        importados[i + 1] = importados[i];
    }

    int pos = i + 1;                           // aqui va el nuevo producto
    codigos[pos] = codigo;
    categorias[pos] = categoria;
    precios[pos] = precio;
    stocks[pos] = stock;
    importados[pos] = importado;
    longitud++;

    return pos;
}

void cargarProductos(const char* nombreArchivo, int* codigos, char* categorias,
    double* precios, int* stocks, bool* importados, int& longitud) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    longitud = 0;
    int codigo;
    char categoria;
    double precio;
    int stock;
    bool importado;
    while (leerProducto(archivo, codigo, categoria, precio, stock, importado)) {
        insertarOrdenado(codigos, categorias, precios, stocks, importados, CAPACIDAD, longitud,
            codigo, categoria, precio, stock, importado);
    }
}

int buscarCodigo(const int* codigos, int longitud, int codigo) {
    for (int i = 0; i < longitud; i++) {
        if (codigos[i] == codigo) {
            return i;
        }
    }
    return -1;
}

// Devuelve la posicion donde quedo el producto, o -1 si se rechaza
// (codigo repetido o sin capacidad)
int intentarInsertar(int* codigos, char* categorias, double* precios, int* stocks,
    bool* importados, int& longitud,
    int codigo, char categoria, double precio, int stock, bool importado) {
    if (buscarCodigo(codigos, longitud, codigo) != -1) {
        return -1;
    }
    return insertarOrdenado(codigos, categorias, precios, stocks, importados,
        CAPACIDAD, longitud, codigo, categoria, precio, stock, importado);
}

void procesarNuevos(const char* nombreArchivo, int* codigos, char* categorias,
    double* precios, int* stocks, bool* importados, int& longitud,
    int* codigosNuevos, int* posicionesNuevos, int& nNuevos) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    nNuevos = 0;
    int codigo;
    char categoria;
    double precio;
    int stock;
    bool importado;
    while (leerProducto(archivo, codigo, categoria, precio, stock, importado)) {
        codigosNuevos[nNuevos] = codigo;
        posicionesNuevos[nNuevos] = intentarInsertar(codigos, categorias, precios, stocks,
            importados, longitud, codigo, categoria, precio, stock, importado);
        nNuevos++;
    }
}

void inicializarResumen(int* cantidades, int* unidades, double* valores,
    double* sumaPrecios, int* posMasCaro) {
    for (int i = 0; i < NUM_CATEGORIAS; i++) {
        cantidades[i] = 0;
        unidades[i] = 0;
        valores[i] = 0;
        sumaPrecios[i] = 0;
        posMasCaro[i] = -1;   // -1: todavia no hay producto en esa categoria
    }
}

// El producto de la posicion pos se acumula en la fila de su categoria
void acumularProducto(int pos, const char* categorias, const double* precios,
    const int* stocks, int* cantidades, int* unidades, double* valores,
    double* sumaPrecios, int* posMasCaro) {
    int indice = categorias[pos] - 'A';
    if (indice < 0 or indice >= NUM_CATEGORIAS) {
        return;
    }

    cantidades[indice]++;
    unidades[indice] += stocks[pos];
    valores[indice] += precios[pos] * stocks[pos];
    sumaPrecios[indice] += precios[pos];
    if (posMasCaro[indice] == -1 or precios[pos] > precios[posMasCaro[indice]]) {
        posMasCaro[indice] = pos;
    }
}

void calcularResumen(const char* categorias, const double* precios, const int* stocks,
    int longitud, int* cantidades, int* unidades, double* valores,
    double* sumaPrecios, int* posMasCaro) {
    inicializarResumen(cantidades, unidades, valores, sumaPrecios, posMasCaro);
    for (int i = 0; i < longitud; i++) {
        acumularProducto(i, categorias, precios, stocks,
            cantidades, unidades, valores, sumaPrecios, posMasCaro);
    }
}

int buscarCategoriaMayorValor(const double* valores, double& mayorValor) {
    int indice = 0;
    for (int i = 1; i < NUM_CATEGORIAS; i++) {
        if (valores[i] > valores[indice]) {
            indice = i;
        }
    }
    mayorValor = valores[indice];
    return indice;
}

void imprimirLineaSeparadora(ofstream& reporte, int longitud, char caracter) {
    reporte << setfill(caracter) << setw(longitud) << "" << setfill(' ') << endl;
}

void imprimirTitulo(ofstream& reporte, const char* titulo) {
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE, '=');
    reporte << titulo << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE, '=');
}

void imprimirNuevos(ofstream& reporte, const int* codigosNuevos,
    const int* posicionesNuevos, int nNuevos) {
    imprimirTitulo(reporte, "INSERCION DE PRODUCTOS NUEVOS");
    for (int i = 0; i < nNuevos; i++) {
        reporte << "Producto " << codigosNuevos[i] << ": ";
        if (posicionesNuevos[i] == -1) {
            reporte << "rechazado, el codigo ya existe" << endl;
        } else {
            reporte << "insertado en la posicion " << posicionesNuevos[i] << endl;
        }
    }
    reporte << endl;
}

void imprimirListado(ofstream& reporte, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, const bool* importados, int longitud) {
    imprimirTitulo(reporte, "PRODUCTOS ORDENADOS POR CODIGO");
    reporte << right << setw(5) << "Pos" << setw(8) << "Codigo" << setw(5) << "Cat"
            << setw(10) << "Precio" << setw(8) << "Stock"
            << setw(2) << "" << left << "Importado" << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE);

    for (int i = 0; i < longitud; i++) {
        reporte << right << setw(5) << i
                << setw(8) << codigos[i]
                << setw(5) << categorias[i]
                << fixed << setprecision(2) << setw(10) << precios[i]
                << setw(8) << stocks[i]
                << setw(2) << "";
        if (importados[i]) {
            reporte << "Si" << endl;
        } else {
            reporte << "No" << endl;
        }
    }
    reporte << endl;
}

void imprimirFilaCategoria(ofstream& reporte, int indice, const int* cantidades,
    const int* unidades, const double* valores, const double* sumaPrecios,
    const int* posMasCaro, const int* codigos) {
    char categoria = 'A' + indice;
    reporte << right << setw(5) << categoria << setw(11) << cantidades[indice]
            << setw(10) << unidades[indice]
            << fixed << setprecision(2) << setw(12) << valores[indice];
    if (cantidades[indice] == 0) {
        reporte << setw(2) << "" << "Sin productos" << endl;
        return;
    }

    double promedio = sumaPrecios[indice] / cantidades[indice];
    reporte << setw(12) << promedio
            << setw(12) << codigos[posMasCaro[indice]] << endl;
}

void imprimirResumen(ofstream& reporte, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, int longitud) {
    int cantidades[NUM_CATEGORIAS];
    int unidades[NUM_CATEGORIAS];
    double valores[NUM_CATEGORIAS];
    double sumaPrecios[NUM_CATEGORIAS];
    int posMasCaro[NUM_CATEGORIAS];
    calcularResumen(categorias, precios, stocks, longitud,
        cantidades, unidades, valores, sumaPrecios, posMasCaro);

    imprimirTitulo(reporte, "RESUMEN POR CATEGORIA");
    reporte << right << setw(5) << "Cat" << setw(11) << "Productos" << setw(10) << "Unidades"
            << setw(12) << "Valor" << setw(12) << "Prom.precio" << setw(12) << "Mas caro" << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE);
    for (int i = 0; i < NUM_CATEGORIAS; i++) {
        imprimirFilaCategoria(reporte, i, cantidades, unidades, valores, sumaPrecios,
            posMasCaro, codigos);
    }
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE);

    double mayorValor = 0;
    int indice = buscarCategoriaMayorValor(valores, mayorValor);
    char categoria = 'A' + indice;
    reporte << "Categoria con mayor valor de inventario: " << categoria
            << " (" << fixed << setprecision(2) << mayorValor << ")" << endl;
}

void generarReporte(const char* nombreArchivo, const int* codigosNuevos,
    const int* posicionesNuevos, int nNuevos, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, const bool* importados, int longitud) {
    ofstream reporte(nombreArchivo);
    if (!reporte) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    imprimirNuevos(reporte, codigosNuevos, posicionesNuevos, nNuevos);
    imprimirListado(reporte, codigos, categorias, precios, stocks, importados, longitud);
    imprimirResumen(reporte, codigos, categorias, precios, stocks, longitud);
}
