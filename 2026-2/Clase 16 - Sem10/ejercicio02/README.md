# Ejercicio 02: Normalización de texto

## De qué trata

Tenemos un texto que narra el final de *El retorno del Jedi*. Está escrito como lo escribiría cualquier persona: con mayúsculas, tildes, signos de exclamación, comillas, guiones largos y hasta algunos símbolos raros como `@`, `#` o `~`.

El programa "limpia" ese texto. Al final queremos quedarnos solo con las palabras importantes, todas en minúscula, sin tildes y sin signos. Por ejemplo, esta línea:

```
—Hay bien en él, lo he sentido —le confesó Luke a Leia bajo la luz de la luna.
```

termina así:

```
bien sentido confeso luke leia bajo luz luna
```

A esto se le llama **normalizar** un texto, y es lo primero que se hace cuando se quiere analizar mucho texto con una computadora (contar palabras, buscar temas, etc.).

## Archivos

En `ArchivosDeDatos`:

- `RetornoDelJedi.txt`: el texto original.
- `Equivalencias.txt`: pares `buscada|reemplazo`. Por ejemplo `á|a` o `Darth Vader|vader`.
- `StopWords.txt`: palabras muy comunes que no aportan significado (*el, la, de, que, y, ...*). En inglés se les llama *stop words*.
- `Terminos.txt`: palabras que queremos contar al final.

En `ArchivosDeReportes` se generan:

- `RetornoDelJediNormalizado.txt`: el texto ya limpio.
- `ReporteNormalizacion.txt`: cuántos cambios se hicieron y cuántas veces aparece cada término.

## La idea principal: leer una vez y trabajar en memoria

Cada archivo se lee **una sola vez** y se guarda completo en un arreglo de caracteres. La función `cargarArchivo` lee línea por línea y va pegando cada una al final de la cadena, sin olvidar el `'\n'` (porque `getline` lo descarta):

```cpp
while (arch.getline(linea, MAX_LINEA)) {
    mi_strcat(contenido, linea);
    mi_strcat(contenido, "\n");
}
```

Después de eso ya no volvemos a tocar los archivos de datos. Todo el trabajo se hace sobre las cadenas en memoria y al final se escriben los reportes.

Las stop words se cargan de otra forma: todas en una sola cadena, separadas por espacios y con un espacio al inicio y al final:

```
" el la los las lo le les un una ... "
```

Así, para saber si `"de"` es stop word, basta con buscar `" de "` (con espacios) dentro de esa cadena usando `mi_strstr`. Los espacios son importantes: sin ellos, `"de"` también aparecería dentro de `"desde"` y nos equivocaríamos.

## Paso a paso

El `main` solo carga, procesa y reporta. El procesamiento está en `normalizarTexto`, que hace cuatro pasos en este orden:

**1. Aplicar equivalencias.** Se recorre la cadena de equivalencias línea por línea. Cada línea se separa en lo que se busca y su reemplazo, y se reemplazan todas las apariciones en el texto con `reemplazarTodas`. Así `"Estrella de la Muerte"` pasa a ser `"estrellamuerte"` (una sola palabra, para que no la rompan los siguientes pasos) y `"á"` pasa a ser `"a"`.

¿Por qué va primero? Porque las letras con tilde no son caracteres ASCII simples, ocupan más de un byte. Si quitáramos los signos antes, la `á` se convertiría en espacios y la palabra `"última"` quedaría partida.

**2. Pasar a minúsculas.** Es la misma idea de `pasaAMayusculas` de la clase anterior, pero al revés: si el carácter está entre `'A'` y `'Z'`, se le suma `'a' - 'A'`.

**3. Quitar signos.** Todo carácter que no sea una letra minúscula, un dígito, un espacio o un salto de línea se cambia por un espacio.

**4. Quitar stop words.** Se recorre el texto línea por línea y, dentro de cada línea, palabra por palabra. Las palabras que no son stop words se van copiando a una cadena nueva (`resultado`). Al final, `resultado` se copia sobre el texto original. Con esto también desaparecen los espacios repetidos, porque solo copiamos palabras.

Por último, `contarTerminos` busca cada término en el texto limpio y cuenta cuántas veces aparece **como palabra completa**. Para eso revisa que antes y después de lo encontrado haya un espacio, un salto de línea o el fin de la cadena. Así `"jedi"` no se cuenta dentro de `"jedis"`.

## La función `extraerCadena`

Es la herramienta que más se repite en este ejercicio. Recibe un "cursor" (un puntero a donde vamos leyendo), un delimitador y una cadena donde dejar el resultado:

```cpp
char* cursor = equivalencias;
while (extraerCadena(cursor, "\n", linea)) {
    // linea tiene la siguiente linea del archivo
}
```

Por dentro usa `mi_strstr` para encontrar el delimitador. Para copiar el pedazo usa el mismo truco de `reemplazar`: pone un `'\0'` justo donde empieza el delimitador, copia con `mi_strcpy` y luego devuelve el carácter que estaba ahí:

```cpp
guardado = *pt;   // guarda el primer caracter del delimitador
*pt = 0;          // corta la cadena ahi
mi_strcpy(cadena, cursor);
*pt = guardado;   // restaura
```

Luego mueve el cursor justo después del delimitador. Cuando ya no queda nada, devuelve `false` y el ciclo termina.

Fíjense en que, al terminar, la cadena original queda **igual que antes**. Eso nos permite recorrer la lista de términos dos veces: una para contar y otra para imprimir el reporte.

## Funciones de cadenas que se usan

`mi_strlen`, `mi_strcpy`, `mi_strcat`, `mi_strstr` y `corresponde` vienen tal cual de la sesión 15. Las nuevas son:

- `pasaAMinusculas`.
- `reemplazarEnTexto`: igual que `reemplazar` de la sesión 15, pero con un `aux` más grande, porque el `aux[500]` original no alcanza para un texto completo.
- `reemplazarTodas`: llama a `reemplazarEnTexto` mientras siga encontrando la palabra.

## Para practicar

1. Agreguen a `Terminos.txt` las palabras `chewbacca` y `yoda`, y verifiquen en el reporte que los conteos tienen sentido.
2. Quiten `no` de `StopWords.txt`. ¿Cuántas stop words menos se eliminan? ¿Por qué podría ser mala idea borrar `no` de un texto?
3. Cambien el orden de los pasos 1 y 3 en `normalizarTexto` y miren qué les pasa a las palabras con tilde.
4. Agreguen al reporte cuántas palabras tiene el texto final.
