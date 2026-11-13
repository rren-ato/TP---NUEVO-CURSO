#include "Bibliotecas/Nodo.h"
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    struct Nodo* lista;
    crearLista("ArchivosDeDatos/Numeros.txt", lista);
    mostrarLista("ArchivosDeReporte/ReporteInicial.txt", lista);
    eliminarDeLaLista(23, lista);
    eliminarMenores(lista, 10);
    mostrarLista("ArchivosDeReporte/ReporteFinal.txt", lista);
    eliminarLista(lista);
    return 0;
}
