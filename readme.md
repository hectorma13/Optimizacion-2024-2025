# 📘 Proyecto: Optimización en Grafos  
## *Implementación de algoritmos para la resolución de problemas en grafos dirigidos y no dirigidos*

![C++](https://img.shields.io/badge/language-C%2B%2B-blue)
![GitHub license](https://img.shields.io/github/license/hector-m-alvarez/Optimizacion-en-Grafos)

Este proyecto implementa una serie de algoritmos clásicos de optimización sobre grafos, incluyendo:

- Búsqueda de componentes conexas y fuertemente conexas
- Árbol generador de mínimo coste mediante el algoritmo de **Sollin**
- Caminos mínimos entre todos los pares de nodos usando el algoritmo de **Floyd-Warshall**

---

## 📁 Estructura del Proyecto

```
.
├── main.cpp           # Programa principal con menú interactivo
├── grafo.h            # Declaración de la clase GRAFO
├── grafo.cpp          # Implementación de métodos de la clase GRAFO
└── README.md          # Documentación del proyecto
```

---

## 🧠 Funcionalidades Implementadas

### 1. **Carga de Grafo desde Fichero**

El programa permite cargar la estructura de un grafo desde un fichero de texto con el siguiente formato:
```
n m d
i j c
...
```
Donde:
- `n`: número de nodos
- `m`: número de aristas/arcs
- `d`: tipo de grafo (`0` no dirigido, `1` dirigido)
- `i`, `j`: nodos conectados
- `c`: coste del arco o arista

Ejemplo de contenido del fichero:
```
6 9 0
1 2 5
1 3 10
2 4 7
3 4 3
3 5 8
4 5 4
4 6 2
5 6 6
```

---

### 2. **Mostrar Información Básica del Grafo**

Muestra:
- Número de nodos
- Número de aristas
- Si es dirigido o no

---

### 3. **Mostrar Listas de Adyacencia / Sucesores / Predecesores**

Dependiendo del tipo de grafo:
- No dirigido: muestra la lista de adyacencia
- Dirigido: muestra sucesores y predecesores por separado

---

### 4. **Componentes Conexas (Grafos No Dirigidos)**

Usa el recorrido en profundidad (**DFS**) para encontrar todas las componentes conexas del grafo.

---

### 5. **Componentes Fuertemente Conexas (Grafos Dirigidos)**

Implementa el algoritmo basado en DFS doble para detectar componentes fuertemente conexas.

---

### 6. **Árbol Generador de Mínimo Coste con el Algoritmo de Sollin**

Construye un árbol generador de mínimo coste usando el algoritmo de Sollin (también conocido como Borůvka modificado).

- En cada iteración se selecciona la arista de menor coste que conecta cada componente con otra distinta.
- Se van fusionando componentes hasta obtener un único árbol o hasta que ya no sea posible conectar más componentes.

---

### 7. **Caminos Mínimos entre Todos los Pares con Floyd-Warshall**

Para grafos dirigidos con pesos enteros (positivos o negativos):

- Calcula la matriz de distancias mínimas entre todos los pares de nodos.
- Detecta ciclos de coste negativo.
- Utiliza programación dinámica para ir mejorando los caminos.

---

## 🔧 Requisitos del Sistema

- Compilador de C++ compatible con C++11 (recomendado `g++`)
- Sistema operativo: Windows, Linux o macOS
- Editor de código o IDE de tu elección

---

## 💻 Compilación y Ejecución

### Compilación

```bash
g++ -o main main.cpp grafo.cpp
```

### Ejecución

```bash
./main [nombre_del_fichero]
```

Ejemplo:

```bash
./main grafos/FWX.gr
```

> Si no se pasa ningún fichero como argumento, el programa pedirá el nombre del fichero al inicio.

---

## 🧪 Prácticas Realizadas

### Práctica 3: Componentes Conexas y Fuertemente Conexas

- Creación de listas de adyacencia/sucesores/predecesores
- Carga de datos desde fichero
- Gestión de memoria dinámica
- Menú interactivo
- Recorridos en profundidad (DFS)
- Postnumeración para detección de componentes fuertemente conexas
- Visualización interactiva de componentes

---

### Práctica 4: Algoritmo de Sollin

- Implementación del algoritmo para grafos no dirigidos
- Estrategia voraz para construir árboles generadores mínimos
- Uso de estructuras de datos auxiliares para gestión de componentes

---

### Práctica 5: Algoritmo de Floyd-Warshall

- Implementación del algoritmo para grafos dirigidos
- Detección de ciclos de coste negativo
- Mostrar matrices de distancia y predecesores paso a paso
- Reconstrucción de caminos mínimos

---

## 🎨 Interfaz

### Menú Principal

```
Optimiza!ción en Grafos, 2024-2025 HÉCTOR MARTÍN ÁLVAREZ
c. [c]argar grafo desde fichero
i. Mostrar [i]nformacion basica del grafo
s. Mostrar la lista de [s]ucesores del grafo
p. Mostrar la lista de [p]redecesores del grafo
o. Mostrar c[o]mponentes fuertemente conexas del grafo
f. Calcular caminos mínimos con el Algoritmo de [F]loyd-Warshall
q. Finalizar el programa
Introduce la letra de la accion a ejecutar  > 
```

### Salida del Algoritmo de Sollin

```
Algoritmo de Sollin para encontrar árbol generador de mínimo coste
--------------------------------------------------------------------
Componentes conexas iniciales:
Componente 1: {1}
Componente 2: {2}
Componente 3: {3}
...

    Arista (4,6) con peso 2 añadida al árbol

MODIFICACIÓN: Hay 7 componentes conexas después de la 1 iteración
```

### Salida del Algoritmo de Floyd-Warshall

```
Matrices finales:
Matriz de distancias D:
   1       2       3       4       5       6
1   0       5      10      12       8       9
2   5       0       7       7      11      13
3  10       7       0       3       4       5
4  12       7       3       0       4       2
5   8      11       4       4       0       6
6   9      13       5       2       6       0

Matriz de predecesores Pred:
   1       2       3       4       5       6
1   0       1       1       3       3       4
2   2       0       2       1       4       4
...
```
