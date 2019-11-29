# Tarea 14 - Algoritmos para encontrar la envolvente convexa

Oscar Esaú Peralta Rosales



## Objetivo

- Implementar el algoritmo de Jarvis march para un conjunto de puntos. Presentar: Gráfica de puntos incluyendo su envolvente convexa; archivo conteniendo los puntos pertenecientes a la envolvente y mostrar por pantalla el tiempo de ejecución.
- Implementar el algoritmo de Graham, para envolver los objetos dentro de una imagen de entrada. Presentar: Archivo conteniendo los puntos pertenecientes a la envolvente, imagen de salida incluyendo su envolvente convexa y mostrar por pantalla el tiempo de ejecución
- Generar una discusión sobre las diferencias entre ambos algoritmos de CH.

## Envolvente convexa

Sea un conjunto de puntos $X$ en un espacio, aquel subconjunto de $X$ con cardinalidad mínima que contenga a todos los puntos de $X$ en su representación espacial se le conoce como envolvente convexa.

<img src="/home/esaup/Documentos/CIMAT/Programación y Algoritmos 1/Algorithms-I/Homeworks/tarea 14/Reporte.assets/download.png" alt="Combinatorial Geometry – My Two Cents" style="zoom:25%;" />

### Algoritmos

#### Jarvis’s March

Se basa en el cálculo de los ángulos formados por un punto pivote de $X$ el cual debe pertenecer al borde contra todos los demás. Se encuentra el primer punto pivote; aquel con las coordenadas en $x$ o en $y$ más pequeña o grande (en $2D$).  Luego se procede a calcular los ángulos formados con los demás puntos y aquel punto que forme el ángulo más chico es tomado como nuestro nuevo pivote. El procedimiento se repite hasta llegar encontrar que el nuevo pivote es el pivote inicial.

Para una implementación mas sencilla, se usa el producto cruz formado por una triada de puntos, se se conserva el orden en el que se hacen las operaciones podemos usar los signos de dicho producto para saber si un punto está dentro del polígono o forma parte de la envoltura.

```pseudocode
points[] <- Vector de puntos iniciales
hull[] <- Vector de que contendra los puntos de la envolvente convexa

pivot <- Encontrar algún punto más alejado en X o Y


```

Nótese que es difil

## Implementación y Resultados

Se implementaron 5 clases distintas:

- **Clase *Activation***: Clase abstracta que contiene las definiciones para la evaluación de las funciones de activación.
- **Clase *F_Cost***: Clase abstracta que contiene las definiciones para la evaluación de las funciones de costo.
- **Clase *Perceptron***: Abstracción para la entidad Perceptrón
- **Clase *Layer***: Abstracción para para la entidad capa, está compuesta por varios objetos tipo *Perceptron*.
- **Clase *MLP***: Abstracción para la entidad de la red de Perceptrones Multicapa, esta compuesta por varios objetos tipo *Layer*.





## Conclusiones



