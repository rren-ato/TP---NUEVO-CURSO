#include "Bibliotecas/Nodo.h"
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    struct Nodo* lista;
    struct Resumen resumen {};
    crearLista("ArchivosDeDatos/Envios.csv", lista, resumen);
    completarClientes("ArchivosDeDatos/Clientes.csv", lista);
    completarDestinos("ArchivosDeDatos/Distritos.csv", lista);
    mostrarLista("ArchivosDeReporte/ReporteDeEnvios.txt",
                 "ENVIOS REGISTRADOS", lista, resumen);

    eliminarSinCobertura(lista, resumen);
    registrarEntregas("ArchivosDeDatos/Entregas.csv", lista, resumen);
    calcularCostos(lista);
    mostrarLista("ArchivosDeReporte/ReporteFinal.txt",
                 "REPORTE DE ENVIOS - COURIER", lista, resumen);

    eliminarLista(lista);
    return 0;
}
