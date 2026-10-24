#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int validos[NUM_TIPOS] = {0};   // todas las posiciones quedan en 0
    int invalidos[NUM_TIPOS] = {0};
    int numReg;

    validarYReportar("ArchivosDeDatos/Registros.csv",
                     "ArchivosDeReportes/ReporteValidacion.txt",
                     validos, invalidos, numReg);
    imprimirResumen("ArchivosDeReportes/ResumenValidacion.txt",
                    validos, invalidos, numReg);

    return 0;
}
