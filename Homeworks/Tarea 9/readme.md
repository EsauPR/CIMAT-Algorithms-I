# Tarea 9

## Problema 1

### compilación
```bash
gcc -Wall task1.c
```

### Ejecución

```bash
./a.out < task1.in
```

### Archivo de entrada
Primera linea dos enteros *a* y *b*, *a* es el número de objetos y *b* el peso máximo de la mochila
*a* lineas con dos enteros cada una representado el el peso y valor respectivamente de cada objeto.

```
4 7
1 1
3 4
4 5
5 7
```

### Salida

El valor máximo total posible de llevar en la mochila


## Problema 2

### compilación
```bash
gcc -Wall task2.c
```

### Ejecución

```bash
./a.out < task2.in
```

### Archivo de entrada
N lineas con un entero y un string en ese orden represetando el número de carácteres del string y el string

Se lee hasta fin de archivo

```
15 anitalavalatina
6 agbdba
16 pdegtfasdrftgeep
12 PROGRAMARENC
```

### Salida

El tamaño del palindromo más grande y el palindromo formado


## Problema 3

### compilación
```bash
gcc -Wall task3.c
```

### Ejecución

```bash
./a.out < task3.in
```

### Archivo de entrada
N lineas con tres enteros cada una, el primero es el número *n* de partidos a ganar.
El segundo es el número de partidos ganados por Pumas.
El tercero con los partidos ganados por el América.

Se lee hasta fin de archivo

```
10 1 1
5 3 1
5 1 3
40 23 33
40 34 15
60 34 48
```

### Salida

La probabilidad de que gane Pumas
