#include "FuncionesAuxiliares.h"

void crearLista(const char* nombArch, struct Nodo*& lista, struct Resumen& resumen) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    struct Envio envioNuevo {};
    lista = nullptr;
    while (true) {
        envioNuevo.codigo = leerCadenaExacta(arch, ',');
        if (arch.eof()) {
            delete[] envioNuevo.codigo;
            break;
        }
        leerDatosEnvio(arch, envioNuevo);
        if (fechaValida(envioNuevo.registro)) {
            insertarOrdenada(lista, envioNuevo);
        } else {
            delete[] envioNuevo.codigo;
            resumen.filasDescartadas++;
        }
    }
}

// Lee lo que sigue al código: fecha, DNIs, distrito y peso
void leerDatosEnvio(ifstream& arch, struct Envio& envio) {
    leerFecha(arch, envio.registro);
    arch.get();
    arch >> envio.remitente.dni;
    arch.get();
    arch >> envio.destinatario.dni;
    arch.get();
    arch >> envio.destino.codigo;
    arch.get();
    arch >> envio.peso;
    arch.get();
    inicializarDatosPendientes(envio);
}

// Los datos que llegan en otros archivos quedan vacíos por ahora.
void inicializarDatosPendientes(struct Envio& envio) {
    envio.remitente.nombre = nullptr;
    envio.remitente.telefono = 0;
    envio.destinatario.nombre = nullptr;
    envio.destinatario.telefono = 0;
    envio.destino.distrito = nullptr;
    envio.destino.zona = ' ';
    envio.destino.tarifa.base = 0;
    envio.destino.tarifa.porKg = 0;
    envio.costo = 0;
    envio.entrega.estado = PENDIENTE;
    envio.entrega.diasDemora = 0;
}

// p busca el primer envío que no va antes y ant queda un nodo detrás.
void insertarOrdenada(struct Nodo*& lista, struct Envio& envio) {
    struct Nodo* p = lista;
    struct Nodo* ant = nullptr;
    struct Nodo* nuevo;
    nuevo = new struct Nodo;
    nuevo->envio = envio;
    while (p != nullptr and vaAntes(p->envio, envio)) {
        ant = p;
        p = p->siguiente;
    }
    nuevo->siguiente = p;
    if (ant == nullptr) {
        lista = nuevo;
    } else {
        ant->siguiente = nuevo;
    }
}

// Orden: por fecha de registro y, a igual fecha, por código.
bool vaAntes(const struct Envio& a, const struct Envio& b) {
    int comparacion = compararFechas(a.registro, b.registro);
    if (comparacion != 0) {
        return comparacion < 0;
    }
    return strcmp(a.codigo, b.codigo) < 0;
}

// La lista no está ordenada por código: se recorre hasta encontrarlo.
struct Nodo* buscarEnvio(const char* codigo, struct Nodo* lista) {
    struct Nodo* p = lista;
    while (p and strcmp(p->envio.codigo, codigo) != 0) {
        p = p->siguiente;
    }
    return p;
}

char* leerCadenaExacta(ifstream& arch, char delimitador) {
    char cadena[TAM_LINEA];
    char* cad;
    arch.getline(cadena, TAM_LINEA, delimitador);
    cad = new char[strlen(cadena) + 1];
    strcpy(cad, cadena);
    return cad;
}

// Formato: dni,nombre,telefono. Cada cliente completa a todos los
// envíos donde aparece como remitente o destinatario.
void completarClientes(const char* nombArch, struct Nodo* lista) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    int dni;
    int telefono;
    char nombre[TAM_LINEA];
    while (true) {
        arch >> dni;
        if (arch.eof()) {
            break;
        }
        arch.get();
        arch.getline(nombre, TAM_LINEA, ',');
        arch >> telefono;
        asignarCliente(lista, dni, nombre, telefono);
    }
}

void asignarCliente(struct Nodo* lista, int dni, const char* nombre, int telefono) {
    struct Nodo* p = lista;
    while (p) {
        if (p->envio.remitente.dni == dni) {
            asignarPersona(p->envio.remitente, nombre, telefono);
        }
        if (p->envio.destinatario.dni == dni) {
            asignarPersona(p->envio.destinatario, nombre, telefono);
        }
        p = p->siguiente;
    }
}

// Cada persona guarda su propia copia del nombre.
void asignarPersona(struct Persona& persona, const char* nombre, int telefono) {
    delete[] persona.nombre;
    persona.nombre = new char[strlen(nombre) + 1];
    strcpy(persona.nombre, nombre);
    persona.telefono = telefono;
}

// Formato: codigo,distrito,zona,tarifaBase,tarifaPorKg
void completarDestinos(const char* nombArch, struct Nodo* lista) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    struct Destino destino {};
    while (true) {
        arch >> destino.codigo;
        if (arch.eof()) {
            break;
        }
        arch.get();
        leerDestino(arch, destino);
        asignarDestino(lista, destino);
        delete[] destino.distrito;
    }
}

// Lee lo que sigue al código: distrito, zona y tarifas
void leerDestino(ifstream& arch, struct Destino& destino) {
    destino.distrito = leerCadenaExacta(arch, ',');
    arch >> destino.zona;
    arch.get();
    arch >> destino.tarifa.base;
    arch.get();
    arch >> destino.tarifa.porKg;
}

// Cada envío guarda su propia copia del nombre del distrito.
void asignarDestino(struct Nodo* lista, const struct Destino& destino) {
    struct Nodo* p = lista;
    while (p) {
        if (p->envio.destino.codigo == destino.codigo) {
            p->envio.destino = destino;
            p->envio.destino.distrito = new char[strlen(destino.distrito) + 1];
            strcpy(p->envio.destino.distrito, destino.distrito);
        }
        p = p->siguiente;
    }
}

// Elimina todos los envíos cuyo distrito no apareció en Distritos.csv.
void eliminarSinCobertura(struct Nodo*& lista, struct Resumen& resumen) {
    struct Nodo* p = lista;
    struct Nodo* ant = nullptr;
    struct Nodo* sale;
    while (p) {
        if (p->envio.destino.distrito != nullptr) {
            ant = p;
            p = p->siguiente;
        } else {
            // distrito sin cobertura
            sale = p;
            if (ant == nullptr) {
                lista = p->siguiente;
                p = lista;
            } else {
                ant->siguiente = p->siguiente;
                p = p->siguiente;
            }
            liberarEnvio(sale->envio);
            delete sale;
            resumen.eliminadosSinCobertura++;
        }
    }
}

// Formato: codigo,dd/mm/aaaa,estado
void registrarEntregas(const char* nombArch, struct Nodo* lista, struct Resumen& resumen) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    char codigo[TAM_LINEA];
    struct Entrega entrega {};
    while (true) {
        arch.getline(codigo, TAM_LINEA, ',');
        if (arch.eof()) {
            break;
        }
        leerFecha(arch, entrega.fecha);
        arch.get();
        arch >> entrega.estado;
        arch.get();
        if (not aplicarEntrega(lista, codigo, entrega)) {
            resumen.entregasIgnoradas++;
        }
    }
}

// Se ignora si el envío no existe, la fecha es inválida o es anterior al registro.
bool aplicarEntrega(struct Nodo* lista, const char* codigo, const struct Entrega& entrega) {
    struct Nodo* p = buscarEnvio(codigo, lista);
    if (p == nullptr or not fechaValida(entrega.fecha)) {
        return false;
    }
    if (compararFechas(entrega.fecha, p->envio.registro) < 0) {
        return false;
    }
    p->envio.entrega = entrega;
    p->envio.entrega.diasDemora = diasEntre(p->envio.registro, entrega.fecha);
    return true;
}

void calcularCostos(struct Nodo* lista) {
    struct Nodo* p = lista;
    while (p) {
        calculaCostoDeEnvio(p->envio);
        p = p->siguiente;
    }
}

// costo = base + porKg * peso, con recargo si supera el peso límite.
void calculaCostoDeEnvio(struct Envio& envio) {
    envio.costo = envio.destino.tarifa.base + envio.destino.tarifa.porKg * envio.peso;
    if (envio.peso > PESO_LIMITE) {
        envio.costo = envio.costo * (1 + RECARGO_PESO);
    }
}

// Formato dd/mm/aaaa
void leerFecha(ifstream& arch, struct Fecha& fecha) {
    arch >> fecha.dia;
    arch.get();
    arch >> fecha.mes;
    arch.get();
    arch >> fecha.anio;
}

bool esBisiesto(int anio) {
    return (anio % 4 == 0 and anio % 100 != 0) or anio % 400 == 0;
}

int diasDelMes(int mes, int anio) {
    if (mes == 2) {
        if (esBisiesto(anio)) {
            return 29;
        }
        return 28;
    }
    if (mes == 4 or mes == 6 or mes == 9 or mes == 11) {
        return 30;
    }
    return 31;
}

int diasDelAnio(int anio) {
    if (esBisiesto(anio)) {
        return 366;
    }
    return 365;
}

bool fechaValida(const struct Fecha& fecha) {
    if (fecha.anio < ANIO_BASE or fecha.mes < 1 or fecha.mes > 12) {
        return false;
    }
    return fecha.dia >= 1 and fecha.dia <= diasDelMes(fecha.mes, fecha.anio);
}

// Negativo si a es anterior, 0 si son iguales, positivo si a es posterior.
int compararFechas(const struct Fecha& a, const struct Fecha& b) {
    if (a.anio != b.anio) {
        return a.anio - b.anio;
    }
    if (a.mes != b.mes) {
        return a.mes - b.mes;
    }
    return a.dia - b.dia;
}

// Cantidad de días desde el 01/01 del ANIO_BASE (respeta bisiestos).
int diasDesdeBase(const struct Fecha& fecha) {
    int dias = 0;
    for (int anio = ANIO_BASE; anio < fecha.anio; anio++) {
        dias += diasDelAnio(anio);
    }
    for (int mes = 1; mes < fecha.mes; mes++) {
        dias += diasDelMes(mes, fecha.anio);
    }
    dias += fecha.dia;
    return dias;
}

int diasEntre(const struct Fecha& desde, const struct Fecha& hasta) {
    return diasDesdeBase(hasta) - diasDesdeBase(desde);
}

// Los totales por zona, los pendientes y la mayor demora se calculan
// mientras se recorre la lista.
void mostrarLista(const char* nombArch, const char* titulo, struct Nodo* lista,
                  const struct Resumen& resumen) {
    ofstream arch(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo "
                << nombArch << endl;
        exit(1);
    }
    struct TotalZona zonas[NUM_ZONAS];
    int cantidad = 0;
    int pendientes = 0;
    const char* codMayor = nullptr;
    int diasMayor = -1;
    arch.precision(2);
    arch << fixed;
    inicializarZonas(zonas);
    imprimeEncabezado(arch, titulo);
    struct Nodo* p = lista;
    while (p) {
        imprimeEnvio(arch, p->envio);
        acumularZona(zonas, p->envio);
        cantidad++;
        if (p->envio.entrega.estado == PENDIENTE) {
            pendientes++;
        }
        if (p->envio.entrega.estado == ENTREGADO and
            p->envio.entrega.diasDemora > diasMayor) {
            codMayor = p->envio.codigo;
            diasMayor = p->envio.entrega.diasDemora;
        }
        p = p->siguiente;
    }
    imprimeZonas(arch, zonas);
    imprimeResumen(arch, cantidad, pendientes, codMayor, diasMayor, resumen);
}

void inicializarZonas(struct TotalZona zonas[]) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        zonas[i].zona = 'A' + i;
        zonas[i].envios = 0;
        zonas[i].peso = 0;
        zonas[i].monto = 0;
    }
}

// Los envíos sin cobertura (zona ' ') no se acumulan.
void acumularZona(struct TotalZona zonas[], const struct Envio& envio) {
    int i = envio.destino.zona - 'A';
    if (i >= 0 and i < NUM_ZONAS) {
        zonas[i].envios++;
        zonas[i].peso += envio.peso;
        zonas[i].monto += envio.costo;
    }
}

void imprimeEncabezado(ofstream& arch, const char* titulo) {
    arch << titulo << endl;
    imprimeLinea(arch, '=', ANCHO_REPORTE);
    arch << left << setw(9) << "CODIGO" << setw(13) << "REGISTRO"
            << setw(22) << "DISTRITO" << setw(6) << "ZONA"
            << right << setw(8) << "PESO" << setw(10) << "COSTO"
            << setw(4) << "" << left << setw(12) << "ESTADO"
            << setw(12) << "FECHA" << "DIAS" << endl;
    imprimeLinea(arch, '-', ANCHO_REPORTE);
}

void imprimeEnvio(ofstream& arch, const struct Envio& envio) {
    arch << left << setw(9) << envio.codigo;
    imprimeFecha(arch, envio.registro);
    arch << setw(3) << "" << left << setw(22);
    if (envio.destino.distrito != nullptr) {
        arch << envio.destino.distrito;
    } else {
        arch << "(sin cobertura)";
    }
    arch << setw(6) << envio.destino.zona << right << setw(8) << envio.peso
            << setw(10) << envio.costo << setw(4) << "";
    imprimeEntrega(arch, envio.entrega);
    imprimePersona(arch, "Remitente:", envio.remitente);
    imprimePersona(arch, "Destinatario:", envio.destinatario);
}

void imprimeEntrega(ofstream& arch, const struct Entrega& entrega) {
    if (entrega.estado == PENDIENTE) {
        arch << left << "PENDIENTE" << endl;
        return;
    }
    if (entrega.estado == ENTREGADO) {
        arch << left << setw(12) << "ENTREGADO";
    } else {
        arch << left << setw(12) << "DEVUELTO";
    }
    imprimeFecha(arch, entrega.fecha);
    arch << right << setw(6) << entrega.diasDemora << endl;
}

void imprimePersona(ofstream& arch, const char* rol, const struct Persona& persona) {
    arch << setw(9) << "" << left << setw(15) << rol << right;
    arch.fill('0');
    arch << setw(8) << persona.dni;
    arch.fill(' ');
    arch << setw(3) << "" << left << setw(30);
    if (persona.nombre != nullptr) {
        arch << persona.nombre;
    } else {
        arch << "(cliente no registrado)";
    }
    if (persona.telefono != 0) {
        arch << "Tel. " << persona.telefono;
    }
    arch << endl;
}

void imprimeZonas(ofstream& arch, const struct TotalZona zonas[]) {
    imprimeLinea(arch, '=', ANCHO_REPORTE);
    arch << "RESUMEN POR ZONA" << endl;
    arch << left << setw(6) << "ZONA" << right << setw(8) << "ENVIOS"
            << setw(12) << "PESO (KG)" << setw(14) << "MONTO (S/)" << endl;
    for (int i = 0; i < NUM_ZONAS; i++) {
        arch << left << setw(6) << zonas[i].zona << right
                << setw(8) << zonas[i].envios << setw(12) << zonas[i].peso
                << setw(14) << zonas[i].monto << endl;
    }
    imprimeLinea(arch, '-', ANCHO_REPORTE);
}

// La mayor demora solo se imprime si ya hay entregas registradas.
void imprimeResumen(ofstream& arch, int cantidad, int pendientes, const char* codMayor,
                    int diasMayor, const struct Resumen& resumen) {
    arch << "Envios en el reporte: " << cantidad << endl;
    arch << "Envios pendientes de entrega: " << pendientes << endl;
    if (codMayor != nullptr) {
        arch << "Entrega con mayor demora: " << codMayor
                << " (" << diasMayor << " dias)" << endl;
    }
    arch << "Filas de envios descartadas por fecha invalida: "
            << resumen.filasDescartadas << endl;
    arch << "Envios eliminados por distrito sin cobertura: "
            << resumen.eliminadosSinCobertura << endl;
    arch << "Entregas ignoradas: " << resumen.entregasIgnoradas << endl;
}

// La fecha se imprime como dd/mm/aaaa.
void imprimeFecha(ofstream& arch, const struct Fecha& fecha) {
    arch.fill('0');
    arch << right << setw(2) << fecha.dia << '/' << setw(2) << fecha.mes
            << '/' << setw(4) << fecha.anio;
    arch.fill(' ');
}

void imprimeLinea(ofstream& arch, char car, int n) {
    for (int i = 0; i < n; i++) {
        arch.put(car);
    }
    arch << endl;
}

// delete[] sobre nullptr no hace nada, por eso no se valida.
void liberarEnvio(struct Envio& envio) {
    delete[] envio.codigo;
    delete[] envio.remitente.nombre;
    delete[] envio.destinatario.nombre;
    delete[] envio.destino.distrito;
}

void eliminarLista(struct Nodo*& lista) {
    struct Nodo* sale;
    while (lista) {
        sale = lista;
        lista = lista->siguiente;
        liberarEnvio(sale->envio);
        delete sale;
    }
}
