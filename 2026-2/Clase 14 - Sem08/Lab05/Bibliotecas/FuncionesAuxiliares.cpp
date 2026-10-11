//
// Created by Eric Huiza on 10/9/26.
//

#include "FuncionesAuxiliares.h"

void cargarPacientes(const char* nombreArchivo, int* codigosPacientes,
                     char* generosPacientes, int* edadesPacientes,
                     double* montosLimitesPacientes,
                     int& num) {

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    num = 0;
    int cod1, cod2, cod3, edad;
    char c, genero;
    double monto;
    while (archivo >> cod1 >> c >> cod2 >> c >> cod3) {
        archivo >> ws;
        archivo.ignore(TAM_LINEA, ' ');
        archivo >> genero >> edad >> monto;

        int codigo = cod1 * 1000000 + cod2 * 10000 + cod3;
        codigosPacientes[num] = codigo;
        generosPacientes[num] = genero;
        edadesPacientes[num] = edad;
        montosLimitesPacientes[num] = monto;
        num++;
    }
}

void cargarEspecialidades(const char* nombreArchivo, int* codigosEspecialidades,
    double* costosPorHoraEspecialidades, int& num) {

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    num = 0;
    int codigo;
    double costo;
    while (archivo >> codigo) {
        archivo >> ws;
        archivo.ignore(TAM_LINEA, ' ');
        archivo >> costo;

        codigosEspecialidades[num] = codigo;
        costosPorHoraEspecialidades[num] = costo;

        num++;
    }
}

void cargarAtenciones(const char* nombreArchivo, int* codigosPacientesAtenciones,
    int* codigosEspecialidadesAtenciones, double* duracionesAtenciones, int& num) {

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    num = 0;
    while (true) {
        if (archivo.eof()) {
            break;
        }

        archivo.ignore(TAM_LINEA, ' ');
        int cod1, cod2, cod3, codigoEspecialidad;
        char c;
        archivo >> cod1 >> c >> cod2 >> c >> cod3 >> codigoEspecialidad;
        int hh, mm, ss;
        archivo >> hh >> c >> mm >> c >> ss >> ws;

        codigosPacientesAtenciones[num] = cod1 * 1000000 + cod2 * 10000 + cod3;
        codigosEspecialidadesAtenciones[num] = codigoEspecialidad;
        duracionesAtenciones[num] = hh + mm / 60.0 + ss / 3600.0;

        num++;
    }
}

void procesarAtenciones(
    const int* codigosPacientesAtenciones,
    const int* codigosEspecialidadesAtenciones,
    const double* duracionesAtenciones,
    int numAtenciones,

    const int* codigosPacientes,
    double* montosLimitesPacientes,
    double* montosPagadosPacientes,
    int* atencionesPagadasPacientes,
    double* montosPendientesPacientes,
    int* atencionesPendientesPacientes,
    double* montosMaximosPacientes,
    int numPacientes,

    const int* codigosEspecialidad,
    const double* costosPorHoraEspecialidades,
    int numEspecialidades) {

    for (int i = 0; i < numAtenciones; i++) {
        int codigoPaciente = codigosPacientesAtenciones[i];
        int codigoEspecialidad = codigosEspecialidadesAtenciones[i];
        double duracion = duracionesAtenciones[i];

        double montoLimite = buscarMontoLimitePaciente(codigosPacientes, montosLimitesPacientes, codigoPaciente, numPacientes);
        double costoHora = buscarCostoHoraEspecialidad(codigosEspecialidad, costosPorHoraEspecialidades, codigoEspecialidad, numEspecialidades);

        if (montoLimite < 0 or costoHora < 0) {
            continue;
        }

        double costoAtencion = costoHora * duracion;

        if (montoLimite >= costoAtencion) {
            pagarAtencion(codigosPacientes, montosLimitesPacientes, montosPagadosPacientes,
                atencionesPagadasPacientes, codigoPaciente, costoAtencion, numPacientes);
        }
        else {
            registrarPagoPendiente(codigosPacientes, montosPendientesPacientes,
                atencionesPendientesPacientes, costoAtencion, codigoPaciente, numPacientes);
        }

        calcularMontoMax(codigosPacientes, montosMaximosPacientes, codigoPaciente, costoAtencion, numPacientes);
    }
}

void pagarAtencion(const int* codigosPacientes, double* montosLimitesPacientes, double* montosPagadosPacientes,
    int* atencionesPagadasPacientes, int codigoPaciente, double costoAtencion, int num) {
    for (int i = 0; i < num; i++) {
        if (codigosPacientes[i] == codigoPaciente) {
            montosPagadosPacientes[i] += costoAtencion;
            montosLimitesPacientes[i] -= costoAtencion;
            atencionesPagadasPacientes[i]++;
            break;
        }
    }
}

void registrarPagoPendiente(const int* codigosPacientes, double* montosPendientesPacientes,
    int* atencionesPendientesPacientes, double costoAtencion, int codigoPaciente, int num) {

    for (int i = 0; i < num; i++) {
        if (codigosPacientes[i] == codigoPaciente) {
            montosPendientesPacientes[i] += costoAtencion;
            atencionesPendientesPacientes[i]++;
            break;
        }
    }
}

void calcularMontoMax(const int* codigosPacientes, double* montosMaximosPacientes, int codigoPaciente, double monto, int num) {
    for (int i = 0; i < num; i++) {
        if (codigosPacientes[i] == codigoPaciente) {
            if (monto > montosMaximosPacientes[i]) {
                montosMaximosPacientes[i] = monto;
                break;
            }
        }
    }
}

double buscarMontoLimitePaciente(const int* codigosPacientes,
    const double* montosLimitesPacientes, int codigoPaciente, int num) {

    for (int i = 0; i < num; i++) {
        if (codigosPacientes[i] == codigoPaciente) {
            return montosLimitesPacientes[i];
        }
    }

    return -1.0;
}

double buscarCostoHoraEspecialidad(const int* codigosEspecialidad,
    const double* costosPorHoraEspecialidades, int codigoEspecialidad, int num) {

    for (int i = 0; i < num; i++) {
        if (codigosEspecialidad[i] == codigoEspecialidad) {
            return costosPorHoraEspecialidades[i];
        }
    }

    return -1.0;
}

void ordenarPacientes(int* codigosPacientes, char* generosPacientes, int* edadesPacientes,
    double* montosLimitesPacientes, double* montosPagadosPacientes, int* atencionesPagadasPacientes,
    double* montosPendientesPacientes, int* atencionesPendientesPacientes, double* montosMaximosPacientes, int num) {

    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (edadesPacientes[i] > edadesPacientes[j] or
                (edadesPacientes[i] == edadesPacientes[j] and
                    montosPendientesPacientes[i] < montosPendientesPacientes[j])) {

                intercambiar(codigosPacientes[i], codigosPacientes[j]);
                intercambiar(generosPacientes[i], generosPacientes[j]);
                intercambiar(edadesPacientes[i], edadesPacientes[j]);
                intercambiar(montosLimitesPacientes[i], montosLimitesPacientes[j]);
                intercambiar(montosPagadosPacientes[i], montosPagadosPacientes[j]);
                intercambiar(atencionesPagadasPacientes[i], atencionesPagadasPacientes[j]);
                intercambiar(montosPendientesPacientes[i], montosPendientesPacientes[j]);
                intercambiar(atencionesPendientesPacientes[i], atencionesPendientesPacientes[j]);
                intercambiar(montosMaximosPacientes[i], montosMaximosPacientes[j]);
            }
        }
    }
}

void intercambiar(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void intercambiar(char& a, char& b) {
    char temp = a;
    a = b;
    b = temp;
}

void intercambiar(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}

void generarReporte(const char* nombreArchivo, const int* codigosPacientes,
    const char* generosPacientes,
    const int* edadesPacientes,
    const double* montosPagadosPacientes,
    const int* atencionesPagadasPacientes,
    const double* montosPendientesPacientes,
    const int* atencionesPendientesPacientes,
    const double* montosMaximosPacientes,
    int numPacientes) {

    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    archivo << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    archivo << "REGISTRO DE PACIENTES [SV2.1]" << endl;
    imprimirLinea(archivo, TAM_LINEA);
    imprimirPaciente(archivo,
        codigosPacientes, generosPacientes, edadesPacientes, montosPagadosPacientes, atencionesPagadasPacientes,
        montosPendientesPacientes, atencionesPendientesPacientes, montosMaximosPacientes, numPacientes);
    imprimirLinea(archivo, TAM_LINEA);

    int cantPendientesDePago = cantidadDePacientesPendientesDePago(atencionesPendientesPacientes, numPacientes);
    double totalPendientesDePago = totalMontosPendientesDePago(montosPendientesPacientes, numPacientes);

    archivo << "RESUMEN:" << endl;
    archivo << "CANTIDAD DE PACIENTES CON MONTOS PENDIENTES DE PAGO: " << cantPendientesDePago << endl;
    archivo << "TOTAL MONTOS PENDIENTES DE PAGO: " << fixed << setprecision(2) << totalPendientesDePago << endl;
}

void imprimirPaciente(ofstream& archivo,
    const int* codigosPacientes,
    const char* generosPacientes,
    const int* edadesPacientes,
    const double* montosPagadosPacientes,
    const int* atencionesPagadasPacientes,
    const double* montosPendientesPacientes,
    const int* atencionesPendientesPacientes,
    const double* montosMaximosPacientes,
    int num) {

    archivo
        << setw(15) << "CODIGO"
        << setw(15) << "SEXO"
        << setw(15) << "EDAD"
        << setw(20) << fixed << setprecision(2) << "MONTO_MAX"
        << setw(20) << fixed << setprecision(2) << "MONTO_PAGADO"
        << setw(30) << fixed << setprecision(2) << "CANT_ATENCIONES_PAGADAS"
        << setw(30) << fixed << setprecision(2) << "MONTO_PENDIENTE_PAGO"
        << setw(30) << fixed << setprecision(2) << "CANT_ATENCIONES_POR_PAGAR"
        << endl;

    for (int i = 0; i < num; i++) {
        archivo
            << setw(15) << codigosPacientes[i]
            << setw(15) << generosPacientes[i]
            << setw(15) << edadesPacientes[i]
            << setw(20) << fixed << setprecision(2) << montosMaximosPacientes[i]
            << setw(20) << fixed << setprecision(2) << montosPagadosPacientes[i]
            << setw(30) << fixed << setprecision(2) << atencionesPagadasPacientes[i]
            << setw(30) << fixed << setprecision(2) << montosPendientesPacientes[i]
            << setw(30) << fixed << setprecision(2) << atencionesPendientesPacientes[i]
            << endl;
    }
}

void imprimirLinea(ofstream& archivo, int tam, char c) {
    archivo << setfill(c) << setw(tam) << "" << setfill(' ') << endl;
}

int cantidadDePacientesPendientesDePago(const int* atencionesPendientesPacientes, int num) {
    int cantidad = 0;
    for (int i = 0; i < num; i++) {
        int numPendientes = atencionesPendientesPacientes[i];
        if (numPendientes > 0) {
            cantidad++;
        }
    }
    return cantidad;
}

double totalMontosPendientesDePago(const double* montosPendientesPacientes, int num) {
    double total = 0.0;
    for (int i = 0; i < num; i++) {
        double montoPendiente = montosPendientesPacientes[i];
        if (montoPendiente > 0) {
            total += montoPendiente;
        }
    }
    return total;
}

void generarReportePrueba(const char* nombreArchivo,
    const int* codigosPacientes, const char* generosPacientes,
    const int* edadesPacientes, const double* montosLimitesPacientes, int numPacientes,
    const int* codigosEspecialidades, const double* costosPorHoraEspecialidades, int numEspecialidades) {

    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    generarReportePacientesPrueba(archivo, codigosPacientes, generosPacientes,edadesPacientes, montosLimitesPacientes, numPacientes);
    generarReporteEspecialidades(archivo, codigosEspecialidades, costosPorHoraEspecialidades, numEspecialidades);
}

void generarReportePacientesPrueba(ofstream& archivo, const int* codigosPacientes, const char* generosPacientes,
    const int* edadesPacientes, const double* montosLimitesPacientes, int num) {

    archivo
        << setw(15) << "CÓDIGO"
        << setw(10) << "GÉNERO"
        << setw(10) << "EDAD"
        << setw(10) << fixed << setprecision(2) << "MONTO L." << endl;
    for (int i = 0; i < num; i++) {
        archivo
            << setw(15) << codigosPacientes[i]
            << setw(10) << generosPacientes[i]
            << setw(10) << edadesPacientes[i]
            << setw(10) << fixed << setprecision(2) << montosLimitesPacientes[i]
            << endl;
    }
}

void generarReporteEspecialidades(ofstream& archivo, const int* codigosEspecialidades,
    const double* costosPorHoraEspecialidades, int num) {

    archivo
        << setw(15) << "CÓDIGO"
        << setw(10) << fixed << setprecision(2) << "COSTO H." << endl;
    for (int i = 0; i < num; i++) {
        archivo
        << setw(15) << codigosEspecialidades[i]
        << setw(10) << fixed << setprecision(2) << costosPorHoraEspecialidades[i] << endl;
    }
}
