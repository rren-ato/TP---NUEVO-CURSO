#include "FuncionesAuxiliares.h"
#include <iomanip>

#define TAM_LINEA 200

bool abrirArchivos(ifstream& archivoCSV, ofstream& json) {
    archivoCSV.open("ArchivosDeDatos/reservas.csv", ios::in);
    json.open("ArchivosDeDatos/reservas.json", ios::out);
    return archivoCSV.is_open() and json.is_open();
}

void cerrarArchivos(ifstream& archivoCSV, ofstream& archivoJSON) {
    archivoCSV.close();
    archivoJSON.close();
}

bool abrirArchivos2(ifstream& archivoJSON, ofstream& archivoReporte) {
    archivoJSON.open("ArchivosDeDatos/reservas.json", ios::in);
    archivoReporte.open("ArchivosDeReporte/reporte.txt", ios::out);
    return archivoJSON.is_open() and archivoReporte.is_open();
}

void cerrarArchivos2(ifstream& archivoJSON, ofstream& archivoReporte) {
    archivoJSON.close();
    archivoReporte.close();
}

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter) {
    archivoReporte << setfill(caracter)
                   << setw(longitud)
                   << ""
                   << setfill(' ') << endl;
}

void imprimirFechaHoraISO(ofstream& archivoReporte,
                          int anio, int mes, int dia, int hora, int minuto, int segundo) {
    archivoReporte << setfill('0')
                   << setw(4) << anio << "-" << setw(2) << mes << "-" << setw(2) << dia << "T"
                   << setw(2) << hora << ":" << setw(2) << minuto << ":" << setw(2) << segundo
                   << setfill(' ');
}

long long fechaHora(int anio, int mes, int dia, int hora, int minuto, int segundo) {
    long long fechaEntera = (long long) anio * 10000 + mes * 100 + dia;  // yyyymmdd
    long long horaEntera  = (long long) hora * 10000 + minuto * 100 + segundo;  // hhmmss
    return fechaEntera * 1000000 + horaEntera;  // yyyymmddhhmmss
}

void imprimirFechaHoraISO(ofstream& archivoReporte, long long fechaHora) {
    int segundo = (int) (fechaHora % 100);
    fechaHora /= 100;
    int minuto = (int) (fechaHora % 100);
    fechaHora /= 100;
    int hora = (int) (fechaHora % 100);
    fechaHora /= 100;
    int dia = (int) (fechaHora % 100);
    fechaHora /= 100;
    int mes = (int) (fechaHora % 100);
    fechaHora /= 100;
    int anio = (int) fechaHora;
    imprimirFechaHoraISO(archivoReporte, anio, mes, dia, hora, minuto, segundo);
}

bool esBisiesto(int anio) {
    if (anio % 400 == 0) {
        return true;
    }
    if (anio % 100 == 0) {
        return false;
    }
    if (anio % 4 == 0) {
        return true;
    }
    return false;
}

int diasDelMes(int mes, int anio) {
    if (mes == 1 or mes == 3 or mes == 5 or mes == 7 or mes == 8 or mes == 10 or mes == 12) {
        return 31;
    }
    if (mes == 4 or mes == 6 or mes == 9 or mes == 11) {
        return 30;
    }
    if (esBisiesto(anio)) {
        return 29;
    }
    return 28;
}

bool fechaHoraValida(int dia, int mes, int anio, int hora, int minuto, int segundo) {
    if (anio < 1) {
        return false;
    }
    if (mes < 1 or mes > 12) {
        return false;
    }
    if (dia < 1 or dia > diasDelMes(mes, anio)) {
        return false;
    }
    if (hora < 0 or hora > 23) {
        return false;
    }
    if (minuto < 0 or minuto > 59) {
        return false;
    }
    if (segundo < 0 or segundo > 59) {
        return false;
    }
    return true;
}

bool leerReservaCSV(ifstream& archivoCSV, int& dia, int& mes, int& anio,
                    int& hora, int& minuto, int& segundo, int& id, char& habitacion,
                    double& importe) {
    int noches;
    char sep;
    double precioPorNoche;

    if (!(archivoCSV >> dia)) {
        return false;
    }
    archivoCSV >> sep >> mes >> sep >> anio
               >> sep >> hora >> sep >> minuto >> sep >> segundo
               >> sep >> id >> sep >> habitacion
        >> sep >> noches >> sep >> precioPorNoche;

    importe = noches * precioPorNoche;
    return true;
}

void acumularReserva(double importe, long long fechaHora, int id,
                     int& nReservas, double& total, double& mayor,
                     long long& fechaHoraMayor, int& idMayor, double& menor,
                     long long& fechaHoraMenor, int& idMenor) {
    nReservas++;
    total += importe;

    if (nReservas == 1 or importe > mayor) {
        mayor = importe;
        fechaHoraMayor = fechaHora;
        idMayor = id;
    }
    if (nReservas == 1 or importe < menor) {
        menor = importe;
        fechaHoraMenor = fechaHora;
        idMenor = id;
    }
}

void imprimirResumenJSON(ofstream& archivoJSON, int nReservas, int reservasInvalidas, double total,
                         double mayor, long long fechaHoraMayor, int idMayor,
                         double menor, long long fechaHoraMenor, int idMenor) {
    archivoJSON << "{\"reservas\": " << nReservas
         << ", \"reservasInvalidas\": " << reservasInvalidas
         << ", \"total\": " << fixed << setprecision(2) << total
         << ", \"mayorImporte\": " << mayor
         << ", \"mayorId\": " << idMayor
         << ", \"mayorFechaHora\": \"";
    imprimirFechaHoraISO(archivoJSON, fechaHoraMayor);
    archivoJSON << "\", \"menorImporte\": " << menor
         << ", \"menorId\": " << idMenor
         << ", \"menorFechaHora\": \"";
    imprimirFechaHoraISO(archivoJSON, fechaHoraMenor);
    archivoJSON << "\"}" << endl;
}

void imprimirReservaJSON(ofstream& archivoJSON, int anio, int mes, int dia, int hora, int minuto,
                         int segundo, int id, char habitacion, double importe) {
    archivoJSON << "{\"fechaHora\": \"";
    imprimirFechaHoraISO(archivoJSON, anio, mes, dia, hora, minuto, segundo);
    archivoJSON << "\", \"id\": " << id
         << ", \"habitacion\": \"" << habitacion << "\""
         << ", \"importe\": " << fixed << setprecision(2) << importe
         << "}" << endl;
}

void generarJSON(ifstream& archivoCSV, ofstream& archivoJSON) {
    int dia, mes, anio, hora, minuto, segundo, id;
    char habitacion;
    double importe;

    int nReservas = 0, reservasInvalidas = 0, idMayor = 0, idMenor = 0;
    double total = 0, mayor = 0, menor = 0;
    long long fechaHoraMayor = 0, fechaHoraMenor = 0;

    while (leerReservaCSV(archivoCSV, dia, mes, anio, hora, minuto, segundo, id, habitacion, importe)) {
        if (!fechaHoraValida(dia, mes, anio, hora, minuto, segundo)) {
            reservasInvalidas++;
            continue;
        }

        long long clave = fechaHora(anio, mes, dia, hora, minuto, segundo);

        imprimirReservaJSON(archivoJSON, anio, mes, dia, hora, minuto, segundo, id, habitacion, importe);
        acumularReserva(importe, clave, id, nReservas, total, mayor,
                        fechaHoraMayor, idMayor, menor, fechaHoraMenor, idMenor);
    }

    imprimirResumenJSON(archivoJSON, nReservas, reservasInvalidas, total,
                        mayor, fechaHoraMayor, idMayor, menor, fechaHoraMenor, idMenor);
}

long long leerFechaHoraISO(ifstream& archivoJSON) {
    char sep;
    int anio, mes, dia, hora, minuto, segundo;

    archivoJSON.ignore(TAM_LINEA, ':');
    archivoJSON.ignore(TAM_LINEA, '"');
    archivoJSON >> anio >> sep >> mes >> sep >> dia >> sep
                >> hora >> sep >> minuto >> sep >> segundo;
    return fechaHora(anio, mes, dia, hora, minuto, segundo);
}

bool esLineaDeReserva(ifstream& json) {
    json.ignore(TAM_LINEA, '"');   // pasa el {" inicial
    return json.peek() == 'f';     // 'f' de "fechaHora"; el resumen empieza con "reservas"
}

void leerResumenJSON(ifstream& archivoJSON, int& nReservas, int& reservasInvalidas, double& total,
                     double& mayor, long long& fechaHoraMayor, int& idMayor,
                     double& menor, long long& fechaHoraMenor, int& idMenor) {
    archivoJSON.ignore(TAM_LINEA, ':');   // "reservas":
    archivoJSON >> nReservas;
    archivoJSON.ignore(TAM_LINEA, ':');   // "reservasInvalidas":
    archivoJSON >> reservasInvalidas;
    archivoJSON.ignore(TAM_LINEA, ':');   // "total":
    archivoJSON >> total;
    archivoJSON.ignore(TAM_LINEA, ':');   // "mayorImporte":
    archivoJSON >> mayor;
    archivoJSON.ignore(TAM_LINEA, ':');   // "mayorId":
    archivoJSON >> idMayor;
    fechaHoraMayor = leerFechaHoraISO(archivoJSON);   // "mayorFechaHora":
    archivoJSON.ignore(TAM_LINEA, ':');   // "menorImporte":
    archivoJSON >> menor;
    archivoJSON.ignore(TAM_LINEA, ':');   // "menorId":
    archivoJSON >> idMenor;
    fechaHoraMenor = leerFechaHoraISO(archivoJSON);   // "menorFechaHora":
    archivoJSON.ignore(TAM_LINEA, '\n');   // cierre } y fin de linea
}

void leerReservaJSON(ifstream& archivoJSON, long long& fechaHora, int& id,
                     char& habitacion, double& importe) {
    fechaHora = leerFechaHoraISO(archivoJSON);   // "fechaHora":
    archivoJSON.ignore(TAM_LINEA, ':');   // "id":
    archivoJSON >> id;
    archivoJSON.ignore(TAM_LINEA, ':');   // "habitacion":
    archivoJSON.ignore(TAM_LINEA, '"');
    archivoJSON >> habitacion;
    archivoJSON.ignore(TAM_LINEA, ':');   // "importe":
    archivoJSON >> importe;
    archivoJSON.ignore(TAM_LINEA, '\n');   // cierre } y fin de linea
}

void imprimirEncabezadoReporte(ofstream& archivoReporte) {
    imprimirLineaSeparadora(archivoReporte, 46);
    archivoReporte << "REPORTE DE RESERVAS" << endl;
    imprimirLineaSeparadora(archivoReporte, 46);
    archivoReporte << left  << setw(19) << "Fecha y hora"
            << right << setw(6)  << "Id"
            << right << setw(7)  << "Hab"
            << right << setw(14) << "Importe" << endl;
    imprimirLineaSeparadora(archivoReporte, 46);
}

void imprimirFilaReserva(ofstream& archivoReporte, long long fechaHora, int id, char habitacion, double importe) {
    imprimirFechaHoraISO(archivoReporte, fechaHora);
    archivoReporte << right << setw(6) << id
            << setw(7) << habitacion
            << fixed << setprecision(2) << setw(14) << importe << endl;
}

void imprimirExtremo(ofstream& archivoReporte, double valor, int id, long long fechaHora) {
    archivoReporte << right << setw(26) << fixed << setprecision(2) << valor << endl;
    archivoReporte << setw(2) << "" << "reserva #" << id << " del ";
    imprimirFechaHoraISO(archivoReporte, fechaHora);
    archivoReporte << endl;
}

void imprimirTotales(ofstream& archivoReporte, int nReservas, int reservasInvalidas, double total,
                 double mayor, long long fechaHoraMayor, int idMayor,
                 double menor, long long fechaHoraMenor, int idMenor) {
    imprimirLineaSeparadora(archivoReporte, 46);
    archivoReporte << fixed << setprecision(2);
    archivoReporte << left << setw(20) << "Reservas validas:" << right << setw(26) << nReservas << endl;
    archivoReporte << left << setw(20) << "Reservas invalidas:" << right << setw(26) << reservasInvalidas << endl;
    archivoReporte << left << setw(20) << "Total facturado:" << right << setw(26) << total << endl;

    archivoReporte << left << setw(20) << "Importe mayor:";
    imprimirExtremo(archivoReporte, mayor, idMayor, fechaHoraMayor);

    archivoReporte << left << setw(20) << "Importe menor:";
    imprimirExtremo(archivoReporte, menor, idMenor, fechaHoraMenor);

    imprimirLineaSeparadora(archivoReporte, 46);
}

void generarReporte(ifstream& json, ofstream& salida) {
    int nReservas = 0, reservasInvalidas = 0, idMayor = 0, idMenor = 0;
    double total = 0, mayor = 0, menor = 0;
    long long fechaHoraMayor = 0, fechaHoraMenor = 0;

    long long fechaHora;
    int id;
    char habitacion;
    double importe;

    imprimirEncabezadoReporte(salida);

    while (true) {
        if (json.peek() != '{' or json.eof()) {
            break;
        }

        if (esLineaDeReserva(json)) {
            leerReservaJSON(json, fechaHora, id, habitacion, importe);
            imprimirFilaReserva(salida, fechaHora, id, habitacion, importe);
        } else {
            leerResumenJSON(json, nReservas, reservasInvalidas, total,
                            mayor, fechaHoraMayor, idMayor, menor, fechaHoraMenor, idMenor);
        }
    }

    imprimirTotales(salida, nReservas, reservasInvalidas, total,
                mayor, fechaHoraMayor, idMayor, menor, fechaHoraMenor, idMenor);
}
