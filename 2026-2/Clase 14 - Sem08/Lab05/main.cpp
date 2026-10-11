#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int codigosPacientes[CAP_PACIENTES];
    char generosPacientes[CAP_PACIENTES];
    int edadesPacientes[CAP_PACIENTES];
    double montosLimitesPacientes[CAP_PACIENTES];
    double montosPagadosPacientes[CAP_PACIENTES] {};
    int atencionesPagadasPacientes[CAP_PACIENTES] {};
    double montosPendientesPacientes[CAP_PACIENTES] {};
    int atencionesPendientesPacientes[CAP_PACIENTES] {};
    double montosMaximosPacientes[CAP_PACIENTES] {};
    int numPacientes;

    int codigosEspecialidades[CAP_ESPECIALIDADES];
    double costosPorHoraEspecialidades[CAP_ESPECIALIDADES];
    int numEspecialidades;

    int codigosPacientesAtenciones[CAP_ATENCIONES];
    int codigosEspecialidadesAtenciones[CAP_ATENCIONES];
    double duracionesAtenciones[CAP_ATENCIONES];
    int numAtenciones;

    cargarPacientes("ArchivosDeDatos/Pacientes.txt",
        codigosPacientes, generosPacientes, edadesPacientes, montosLimitesPacientes, numPacientes);
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

    return 0;
}
