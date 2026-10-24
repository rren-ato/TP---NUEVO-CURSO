# Ejercicio 01: Validación de DNI, placas y fechas

## De qué trata

Recibimos un archivo donde cada fila tiene un dato y el tipo de dato que debería ser:

```
45879632,DNI
ABC-123,PLACA
29-02-2023,FECHA
```

El programa revisa cada fila y genera un reporte que dice cuáles son válidas y cuáles no. Para las inválidas también indica el motivo.

Las reglas son:

| Tipo  | Formato válido | Ejemplo      |
|-------|----------------|--------------|
| DNI   | exactamente 8 dígitos | `45879632` |
| PLACA | 3 letras mayúsculas, un guion y 3 dígitos | `ABC-123` |
| FECHA | `dd-mm-aaaa`, y además la fecha debe existir | `24-10-2026` |

El tipo puede venir escrito en mayúscula o en minúscula (`dni`, `Placa`), así que antes de compararlo se pasa a mayúsculas.

## Archivos

- `ArchivosDeDatos/Registros.csv`: los datos a validar.
- `ArchivosDeReportes/ReporteValidacion.txt`: el resultado de cada fila.
- `ArchivosDeReportes/ResumenValidacion.txt`: cuántos válidos e inválidos hubo por tipo.

## Cómo está organizado

En este ejercicio no guardamos el archivo en memoria. Cada fila se **lee, se valida y se escribe en el reporte** antes de pasar a la siguiente.

El `main` declara los contadores del resumen y llama a dos funciones:

```cpp
int validos[NUM_TIPOS] = {0};
int invalidos[NUM_TIPOS] = {0};
int numReg;

validarYReportar("ArchivosDeDatos/Registros.csv",
                 "ArchivosDeReportes/ReporteValidacion.txt",
                 validos, invalidos, numReg);
imprimirResumen("ArchivosDeReportes/ResumenValidacion.txt",
                validos, invalidos, numReg);
```

Los arreglos `validos` e `invalidos` se inicializan en 0 al declararlos. Cuando una lista entre llaves tiene menos valores que el tamaño del arreglo, las posiciones que faltan se completan con 0. Ojo: `{1}` **no** llena todo con unos; solo pone un 1 en la primera posición.

`validarYReportar` llena esos contadores y `numReg`, que va por referencia (`int&`) para que el `main` reciba la cantidad de filas. Luego `imprimirResumen` usa esos mismos datos para escribir el segundo archivo.

Dentro de `validarYReportar` se abren el archivo de datos y el de reporte, se imprime el encabezado y luego viene el ciclo principal:

```cpp
while (leerRegistro(archDatos, valor, tipo)) {
    numReg++;
    motivo = validarRegistro(valor, tipo);
    imprimirRegistro(archReporte, numReg, valor, tipo, motivo);
    acumularResultado(validos, invalidos, tipo, motivo);
}
```

En cada vuelta:

1. se lee una fila;
2. se valida;
3. se escribe su línea en el reporte;
4. se suma a los contadores del resumen.

Cuando el archivo se termina, la función acaba y los contadores ya tienen los totales. Como cada fila se usa y se descarta, solo necesitamos dos cadenas pequeñas, `valor` y `tipo`, sin importar cuántas filas tenga el archivo.

## Leer el valor y el tipo con `getline`

Cada fila tiene la forma `valor,TIPO`. `getline` acepta un tercer parámetro que indica hasta qué carácter leer, así que la fila se lee en dos partes:

```cpp
arch.getline(valor, TAM_VALOR, ',');   // hasta la coma: "45879632"
...
arch.getline(tipo, TAM_TIPO);          // hasta el fin de linea: "DNI"
```

Las dos lecturas **consumen** su delimitador: la coma y el `'\n'` se sacan del archivo pero no se guardan. Así la siguiente lectura empieza justo en el dato que sigue, sin caracteres sobrantes.

Para saber cuándo terminar, después de leer el valor se pregunta si se llegó al fin del archivo:

```cpp
if (arch.eof()) {
    return false;
}
```

Cuando ya no quedan filas, el intento de leer el valor encuentra el fin del archivo, `leerRegistro` devuelve `false` y el `while` termina. Es la misma idea de `leerLinea` en el ejercicio del archivo CSV de la sesión 15.

Finalmente, el tipo se pasa a mayúsculas con `pasaAMayusculas`, para que `dni`, `Dni` y `DNI` se traten igual.

## Por qué los motivos son números

Cada validación devuelve un número que indica el resultado. Cada número tiene un nombre definido con `#define`:

```cpp
#define MOTIVO_OK 0
#define MOTIVO_LONGITUD 1
#define MOTIVO_NO_NUMERICO 2
...
```

Es más simple devolver y comparar un número que una cadena. Recién al imprimir, la función `obtenerMotivo` convierte el código en texto con `mi_strcpy`.

Para decidir qué validación aplicar, se compara el tipo con `mi_strcmp`.

## Las validaciones

**DNI.** Primero se revisa la longitud con `mi_strlen`. Si no es 8, ya es inválido. Si lo es, se revisa que los 8 caracteres sean dígitos.

**Placa.** La longitud debe ser 7. Luego se revisa por posiciones: de la 0 a la 2, mayúsculas; en la 3, un `'-'`; de la 4 a la 6, dígitos. Para no repetir ciclos se usan dos funciones pequeñas, `sonMayusculas` y `sonDigitos`, que revisan un tramo de la cadena.

**Fecha.** Es la más interesante. Primero se revisa que tenga la forma `dd-mm-aaaa` (10 caracteres, con guiones en las posiciones 2 y 5). Después hay que sacar los números, y aquí `mi_atoi` nos ayuda mucho: como se detiene en el primer carácter que no es dígito, basta con darle la dirección donde empieza cada parte:

```cpp
dia  = mi_atoi(&fecha[0]);   // lee "29" y se detiene en el '-'
mes  = mi_atoi(&fecha[3]);   // lee "02"
anio = mi_atoi(&fecha[6]);   // lee "2023"
```

Tener la forma correcta no basta: la fecha tiene que existir. `31-04-2026` no existe porque abril tiene 30 días, y `29-02-2023` tampoco porque 2023 no es bisiesto. Para eso están `esBisiesto` y `diasDelMes`.

Recuerden la regla del año bisiesto: es divisible entre 4, pero no entre 100, salvo que también sea divisible entre 400. Por eso 2000 es bisiesto y 1900 no lo es. Ambos casos están en el archivo de datos.

## El resumen del reporte

El archivo de resumen tiene una tabla con cuántos válidos e inválidos hubo por tipo. Se usan dos arreglos de 4 posiciones (DNI, PLACA, FECHA y OTRO). En cada vuelta del ciclo, `acumularResultado` suma 1 en la posición que corresponde al tipo de la fila, en `validos` o en `invalidos` según el motivo.

## Para practicar

1. Agreguen al archivo la fila `2-2-2024,FECHA`. ¿Qué motivo creen que va a salir? Compruébenlo.
2. Agreguen un nuevo tipo `CODIGO` para el código PUCP: 8 dígitos que empiezan con `20`.
3. Hoy `abc-123` es inválido porque está en minúsculas. ¿Qué cambiarían para aceptarlo y convertirlo a mayúsculas antes de validar?
4. Agreguen un motivo nuevo para fechas con año menor a 1900.
