#include "Bibliotecas/NodoDoble.h"
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    struct NodoDoble* lista;
    crearLista("ArchivosDeDatos/numeros.txt", lista);
    eliminarMenores(lista, 10);
    mostrarLista("ArchivosDeReportes/Reporte.txt", lista);
    eliminarLista(lista);
    return 0;
}
