#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int* codigosPacientes;
    char* generosPacientes;
    int* edadesPacientes;
    double* montosLimitesPacientes;
    int numPacientes;

    int* codigosEspecialidades;
    double* costosPorHoraEspecialidades;
    int numEspecialidades;

    int* codigosPacientesAtenciones;
    int* codigosEspecialidadesAtenciones;
    double* duracionesAtenciones;
    int numAtenciones;

    cargarPacientes("ArchivosDeDatos/Pacientes.txt",
        codigosPacientes, generosPacientes, edadesPacientes, montosLimitesPacientes, numPacientes);

    double* montosPagadosPacientes = new double[numPacientes] {};
    int* atencionesPagadasPacientes = new int[numPacientes] {};
    double* montosPendientesPacientes = new double[numPacientes] {};
    int* atencionesPendientesPacientes = new int[numPacientes] {};
    double* montosMaximosPacientes = new double[numPacientes] {};

    cargarEspecialidades("ArchivosDeDatos/Especialidades.txt", codigosEspecialidades, costosPorHoraEspecialidades,
        numEspecialidades);

    generarReportePrueba("ArchivosDeReportes/pruebas.txt", codigosPacientes, generosPacientes, edadesPacientes,
        montosLimitesPacientes, numPacientes, codigosEspecialidades, costosPorHoraEspecialidades, numEspecialidades);

    cargarAtenciones("ArchivosDeDatos/Atenciones.txt", codigosPacientesAtenciones, codigosEspecialidadesAtenciones,
        duracionesAtenciones, numAtenciones);

    procesarAtenciones(
        codigosPacientesAtenciones,
        codigosEspecialidadesAtenciones,
        duracionesAtenciones,
        numAtenciones,

        codigosPacientes,
        montosLimitesPacientes,
        montosPagadosPacientes,
        atencionesPagadasPacientes,
        montosPendientesPacientes,
        atencionesPendientesPacientes,
        montosMaximosPacientes,
        numPacientes,

        codigosEspecialidades,
        costosPorHoraEspecialidades,
        numEspecialidades);

    ordenarPacientes(codigosPacientes, generosPacientes, edadesPacientes,
        montosLimitesPacientes, montosPagadosPacientes, atencionesPagadasPacientes,
        montosPendientesPacientes, atencionesPendientesPacientes, montosMaximosPacientes, numPacientes);

    generarReporte("ArchivosDeReportes/ReporteDePacientes.txt", codigosPacientes, generosPacientes, edadesPacientes, montosPagadosPacientes,
        atencionesPagadasPacientes, montosPendientesPacientes, atencionesPendientesPacientes, montosMaximosPacientes,
        numPacientes);

    delete[] codigosPacientes;
    delete[] generosPacientes;
    delete[] edadesPacientes;
    delete[] montosLimitesPacientes;
    delete[] montosPagadosPacientes;
    delete[] atencionesPagadasPacientes;
    delete[] montosPendientesPacientes;
    delete[] atencionesPendientesPacientes;
    delete[] montosMaximosPacientes;

    delete[] codigosEspecialidades;
    delete[] costosPorHoraEspecialidades;

    delete[] codigosPacientesAtenciones;
    delete[] codigosEspecialidadesAtenciones;
    delete[] duracionesAtenciones;

    return 0;
}
