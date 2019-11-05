# Tarea 11 - Visvalingam algorithm

- Lenguaje: C++
- Estandar: c++11
- Bibliotecas externas necesarias:
  - [Cairo](https://www.cairographics.org/)

## Compilación

```
$ g++ -Wall main.cpp  $(pkg-config --cflags --libs cairo)
```

## Ejecución

El ejecutable generado recibe dos parámetros.

- Nombre del archivo dónde se encuentran los puntos que definen la figura
- Nivel de compresión

Ejemplo
```
$ ./a.out oaxaca_points.txt 20
```
