# AED - Algoritmos y Estructuras de Datos

Este repositorio contiene las implementaciones, trabajos prácticos y material de estudio de la materia Algoritmos y Estructuras de Datos.

## Estructura del Proyecto

* **`TPs/`**: Trabajos prácticos de la cursada.
    * **TP1, TP2, TP3**: Implementaciones en C con sus respectivos `makefile` y entornos en `Docker`.
    * **TP4**: Análisis de grafos y visualización utilizando Python y Jupyter Notebooks.
* **`Parciales previos / finales previos/`**: Recopilación de enunciados y resoluciones de exámenes de cuatrimestres anteriores.
* **`ejercicios/`**: Implementaciones de estructuras de datos y algoritmos fundamentales:
    * Pilas (Stacks) y Colas (Queues).
    * Grafos y Programación Dinámica.
    * Notación Polaca Inversa.
* **`arbol/`**: Tipos y recorridos de árboles.
* **`heap/`**: Implementaciones de Heap (up/down) y scripts de verificación.
* **`strings/`**: Ejercicios de manipulación de cadenas en C.
* **`tap/`**: Teoría de algoritmos y programación.

## Tecnologías Utilizadas

* **Lenguajes**: C, Python.
* **Herramientas**: Docker, Make, Jupyter Notebook.
* **Librerías Python**: Matplotlib, Pygraphviz (para visualización de grafos).

## Ejecución con Docker

Para los entornos de C que incluyen `Dockerfile`:

```bash
docker build -t aed-env .
docker run -it aed-env
```

## Compilación con Make

En los directorios con `makefile`:

```bash
make
./ejecutable
```
