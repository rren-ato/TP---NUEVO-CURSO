//
// Created by Eric Huiza on 9/24/26.
//

#include "FuncionesAuxiliares.h"

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
    char coma;
    while (archivo >> codigo) {
        archivo >> coma >> categoria >> coma >> precio >> coma >> stock >> coma >> importado;
        codigos[longitud] = codigo;
        categorias[longitud] = categoria;
        precios[longitud] = precio;
        stocks[longitud] = stock;
        importados[longitud] = importado;
        longitud++;
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

// Devuelve la posicion del producto mas barato de la categoria que tenga stock.
int buscarMasBaratoDisponible(const char* categorias, const double* precios,
    const int* stocks, int longitud, char categoria, double& precio) {
    int pos = -1;
    for (int i = 0; i < longitud; i++) {
        if (categorias[i] == categoria and stocks[i] > 0) {
            if (pos == -1 or precios[i] < precios[pos]) {
                pos = i;
            }
        }
    }

    if (pos != -1) {
        precio = precios[pos];
    }
    return pos;
}

int buscarMayorStock(const int* stocks, int longitud, int& mayorStock) {
    if (longitud == 0) {
        return -1;
    }

    int pos = 0;
    for (int i = 1; i < longitud; i++) {
        if (stocks[i] > stocks[pos]) {
            pos = i;
        }
    }
    mayorStock = stocks[pos];
    return pos;
}

// Busca desde la posicion "desde"; llamandola de nuevo con pos + 1
// se encuentran todos los agotados, uno por uno.
int buscarAgotado(const int* stocks, int longitud, int desde) {
    for (int i = desde; i < longitud; i++) {
        if (stocks[i] == 0) {
            return i;
        }
    }
    return -1;
}

int contarPorCategoria(const char* categorias, int longitud, char categoria) {
    int cantidad = 0;
    for (int i = 0; i < longitud; i++) {
        if (categorias[i] == categoria) {
            cantidad++;
        }
    }
    return cantidad;
}

void procesarConsultasCodigo(const char* nombreArchivo, const int* codigos, int longitud,
    int* codigosConsulta, int* posicionesConsulta, int& nConsultas) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    nConsultas = 0;
    int codigo;
    while (nConsultas < CAPACIDAD and archivo >> codigo) {
        codigosConsulta[nConsultas] = codigo;
        posicionesConsulta[nConsultas] = buscarCodigo(codigos, longitud, codigo);
        nConsultas++;
    }
}

void procesarConsultasCategoria(const char* nombreArchivo, const char* categorias,
    const double* precios, const int* stocks, int longitud,
    char* categoriasConsulta, int* cantidadesCategoria, int* posicionesBarato,
    double* preciosBarato, int& nCategorias) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    nCategorias = 0;
    char categoria;
    while (nCategorias < CAPACIDAD and archivo >> categoria) {
        categoriasConsulta[nCategorias] = categoria;
        cantidadesCategoria[nCategorias] = contarPorCategoria(categorias, longitud, categoria);
        preciosBarato[nCategorias] = 0;
        posicionesBarato[nCategorias] = buscarMasBaratoDisponible(categorias, precios, stocks,
            longitud, categoria, preciosBarato[nCategorias]);
        nCategorias++;
    }
}

void imprimirLineaSeparadora(ofstream& reporte, int longitud, char caracter) {
    reporte << setfill(caracter) << setw(longitud) << "" << setfill(' ') << endl;
}

void imprimirTitulo(ofstream& reporte, const char* titulo) {
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE, '=');
    reporte << titulo << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE, '=');
}

void imprimirConsultaCodigo(ofstream& reporte, int codigo, int pos, const char* categorias,
    const double* precios, const int* stocks) {
    reporte << right << setw(8) << codigo;
    if (pos == -1) {
        reporte << setw(2) << "" << "No registrado" << endl;
        return;
    }

    reporte << setw(6) << pos
            << setw(5) << categorias[pos]
            << fixed << setprecision(2) << setw(10) << precios[pos]
            << setw(8) << stocks[pos]
            << setw(2) << "";
    if (stocks[pos] > 0) {
        reporte << "Disponible" << endl;
    } else {
        reporte << "Agotado" << endl;
    }
}

void imprimirConsultasCodigo(ofstream& reporte, const int* codigosConsulta,
    const int* posicionesConsulta, int nConsultas, const char* categorias,
    const double* precios, const int* stocks) {
    imprimirTitulo(reporte, "CONSULTAS POR CODIGO");
    reporte << right << setw(8) << "Codigo" << setw(6) << "Pos" << setw(5) << "Cat"
            << setw(10) << "Precio" << setw(8) << "Stock"
            << setw(2) << "" << left << "Estado" << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE);

    for (int i = 0; i < nConsultas; i++) {
        imprimirConsultaCodigo(reporte, codigosConsulta[i], posicionesConsulta[i],
            categorias, precios, stocks);
    }
    reporte << endl;
}

void imprimirConsultaCategoria(ofstream& reporte, char categoria, int cantidad,
    int pos, double precio, const int* codigos) {
    reporte << right << setw(5) << categoria << setw(11) << cantidad;
    if (pos == -1) {
        reporte << setw(2) << "" << "Sin productos disponibles" << endl;
        return;
    }

    reporte << setw(12) << codigos[pos]
            << setw(6) << pos
            << fixed << setprecision(2) << setw(10) << precio << endl;
}

void imprimirConsultasCategoria(ofstream& reporte, const char* categoriasConsulta,
    const int* cantidadesCategoria, const int* posicionesBarato,
    const double* preciosBarato, int nCategorias, const int* codigos) {
    imprimirTitulo(reporte, "MAS BARATO DISPONIBLE POR CATEGORIA");
    reporte << right << setw(5) << "Cat" << setw(11) << "Productos"
            << setw(12) << "Codigo" << setw(6) << "Pos" << setw(10) << "Precio" << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE);

    for (int i = 0; i < nCategorias; i++) {
        imprimirConsultaCategoria(reporte, categoriasConsulta[i], cantidadesCategoria[i],
            posicionesBarato[i], preciosBarato[i], codigos);
    }
    reporte << endl;
}

void imprimirMayorStock(ofstream& reporte, const int* codigos, const int* stocks, int longitud) {
    int mayorStock = 0;
    int pos = buscarMayorStock(stocks, longitud, mayorStock);

    imprimirTitulo(reporte, "PRODUCTO CON MAYOR STOCK");
    if (pos == -1) {
        reporte << "No hay productos" << endl;
        return;
    }
    reporte << "Producto " << codigos[pos] << " con " << mayorStock
            << " unidades (posicion " << pos << ")" << endl << endl;
}

void imprimirAgotados(ofstream& reporte, const int* codigos, const int* stocks, int longitud) {
    imprimirTitulo(reporte, "PRODUCTOS AGOTADOS");

    int cantidad = 0;
    int pos = buscarAgotado(stocks, longitud, 0);
    while (pos != -1) {
        reporte << "Producto " << codigos[pos] << " (posicion " << pos << ")" << endl;
        cantidad++;
        pos = buscarAgotado(stocks, longitud, pos + 1);
    }
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE);
    reporte << "Total de agotados: " << cantidad << endl;
}

void generarReporte(const char* nombreArchivo, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, int longitud,
    const int* codigosConsulta, const int* posicionesConsulta, int nConsultas,
    const char* categoriasConsulta, const int* cantidadesCategoria,
    const int* posicionesBarato, const double* preciosBarato, int nCategorias) {
    ofstream reporte(nombreArchivo);
    if (!reporte) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    imprimirConsultasCodigo(reporte, codigosConsulta, posicionesConsulta, nConsultas,
        categorias, precios, stocks);
    imprimirConsultasCategoria(reporte, categoriasConsulta, cantidadesCategoria,
        posicionesBarato, preciosBarato, nCategorias, codigos);
    imprimirMayorStock(reporte, codigos, stocks, longitud);
    imprimirAgotados(reporte, codigos, stocks, longitud);
}

void gererarReporte(const char* archivoConsultas, const char* archivoCategorias,
    const char* archivoReporte, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, int longitud) {
    // resultado de las consultas por codigo (posicion -1 = no registrado)
    int codigosConsulta[CAPACIDAD];
    int posicionesConsulta[CAPACIDAD];
    int nConsultas;

    // resultado de las consultas por categoria (posicion -1 = sin disponibles)
    char categoriasConsulta[CAPACIDAD];
    int cantidadesCategoria[CAPACIDAD];
    int posicionesBarato[CAPACIDAD];
    double preciosBarato[CAPACIDAD];
    int nCategorias;

    procesarConsultasCodigo(archivoConsultas, codigos, longitud,
        codigosConsulta, posicionesConsulta, nConsultas);
    procesarConsultasCategoria(archivoCategorias, categorias, precios, stocks, longitud,
        categoriasConsulta, cantidadesCategoria, posicionesBarato, preciosBarato, nCategorias);

    generarReporte(archivoReporte, codigos, categorias, precios, stocks, longitud,
        codigosConsulta, posicionesConsulta, nConsultas, categoriasConsulta,
        cantidadesCategoria, posicionesBarato, preciosBarato, nCategorias);
}
