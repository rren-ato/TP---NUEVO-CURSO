# Ejercicio 01: Reporte de notas por alumno

`alumnos.csv` trae el código y el ciclo de cada alumno (`codigo,ciclo`), y
`notas.csv` trae el código de un alumno y una nota (`codigo,nota`). Un alumno
puede tener varias notas, y hay notas cuyo código no está en `alumnos.csv`.

1. Carga `alumnos.csv` en los arreglos paralelos `codigoAlumno[]` y `ciclo[]`,
   y `notas.csv` en `codigoNota[]` y `nota[]`.
2. Genera `ArchivosDeReportes/reporte.txt` con el listado de notas. Por cada
   nota, busca su código en `codigoAlumno[]` con búsqueda secuencial y, con la
   posición encontrada, imprime el código, el **ciclo del alumno** y la nota.
   Si el código no está registrado, la nota se marca como *Alumno no
   registrado*.
3. Al pie del reporte imprime un resumen:
   - cantidad de notas de alumnos registrados y de alumnos no registrados,
   - promedio de las notas de alumnos registrados,
   - nota más alta y nota más baja, con el código y el ciclo del alumno.

Resultados esperados, para comprobar: 13 notas de alumnos registrados y 2 de no
registrados, promedio 13.23, nota más alta 19.50 (alumno 20200117, ciclo 6) y
nota más baja 7.00 (alumno 20195521, ciclo 6).
