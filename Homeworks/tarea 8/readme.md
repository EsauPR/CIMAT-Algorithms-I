# Algoritmo de Kosaraju para encontrar Componentes Fuertemente Connectados

## Compilación

```
gcc -Wall main.c
```

## Ejecución

```
./a.out < [input]
```

Ejemplo

```
./a.out < 1.in
```

## Entrada

Primera linea dos enteros positivos **N**, **A** <= 1000,  indicando número de nodos y aristas
**A** lineas con dos enteros **u**, **v** < **N** indicando una conexión de **u** a **v**

Ejemplo

```
12 13
0 1
1 3
3 2
2 1
3 4
4 5
5 7
7 6
6 4
8 9
9 10
10 11
11 9
```

## Salida

Número de componentes fuertemente conectadas y componente de cada nodo

Ejemplo:

```
NSCC: 5
Node 0 -> Componet: 3
Node 1 -> Componet: 4
Node 2 -> Componet: 4
Node 3 -> Componet: 4
Node 4 -> Componet: 5
Node 5 -> Componet: 5
Node 6 -> Componet: 5
Node 7 -> Componet: 5
Node 8 -> Componet: 1
Node 9 -> Componet: 2
Node 10 -> Componet: 2
Node 11 -> Componet: 2
```
