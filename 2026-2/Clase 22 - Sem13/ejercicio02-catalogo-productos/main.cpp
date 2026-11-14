#include "Bibliotecas/Nodo.h"
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main(int argc, char** argv) {
    struct Nodo* lista;
    crearLista("ArchivosDeDatos/Productos.csv", lista);
    mostrarLista("ArchivosDeReporte/ReporteDeProductos.txt",
                 "CATÁLOGO INICIAL", lista);

    agregarProductos("ArchivosDeDatos/ProductosNuevos.csv", lista);
    retirarProductos("ArchivosDeDatos/ProductosRetirados.txt", lista);
    mostrarLista("ArchivosDeReporte/ReporteDeCatalogoActualizado.txt",
                 "CATÁLOGO ACTUALIZADO (ALTAS Y RETIROS)", lista);

    cargarVentas("ArchivosDeDatos/Ventas.csv", lista);
    calcularTotales(lista);
    mostrarLista("ArchivosDeReporte/ReporteDeVentas.txt",
                 "VENTAS POR PRODUCTO", lista);

    eliminarSinVentas(lista);
    mostrarLista("ArchivosDeReporte/ReporteFinal.txt",
                 "CATÁLOGO FINAL (SIN PRODUCTOS SIN VENTAS)", lista);

    eliminarLista(lista);
    return 0;
}
