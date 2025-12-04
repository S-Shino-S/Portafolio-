# ADA 04
El propósito de esta práctica fue implementar una estructura de datos no lineal jerárquica: el Árbol Binario de Búsqueda (ABB). La actividad consistió en desarrollar un sistema para administrar expedientes académicos, utilizando la matrícula del estudiante como la llave (key) para ordenar los nodos del árbol.

El programa requirió una gestión avanzada de memoria, ya que cada nodo (Estudiante) contenía no solo los datos básicos, sino también un arreglo dinámico para sus calificaciones, lo que variaba de alumno a alumno. Se implementaron operaciones complejas más allá de la inserción y búsqueda básica, tales como la generación de reportes filtrados por promedio (lo cual implicaba recorrer todo el árbol), el conteo de nodos bajo cierto criterio, la impresión de niveles específicos y, finalmente, la visualización gráfica del árbol en formato ASCII en la consola.

Shutterstock

Reflexión Personal

¿Qué se aprendió? Esta actividad consolidó mi comprensión de la recursividad, ya que la mayoría de las funciones del árbol (insertar, buscar, imprimir) se resuelven de manera mucho más limpia invocándose a sí mismas. Aprendí a utilizar los diferentes tipos de recorridos (In-Order, Pre-Order, Post-Order); por ejemplo, entendí que el recorrido In-Order en un ABB siempre devuelve los datos ordenados ascendentemente (por matrícula en este caso). También practiqué el manejo de "estructuras dentro de estructuras" dinámicas al gestionar los arreglos de calificaciones dentro de los nodos.

Problemas y desafíos: El desafío técnico más grande fue, sin duda, la función de eliminar un nodo. Es el caso más complejo en los ABB, especialmente cuando el nodo a borrar tiene dos hijos, pues es necesario encontrar al sucesor inmediato (el menor del subárbol derecho) para reemplazarlo y reacomodar los punteros sin romper la estructura del árbol. Otro problema surgió con el reporte de "ordenar por promedio". Como el árbol estaba ordenado por matrícula, no podía aprovechar la estructura del ABB para esto; tuve que recorrer todos los nodos, extraerlos a una estructura auxiliar temporal y allí ordenarlos por calificación, lo cual me hizo reflexionar sobre las limitaciones de ordenamiento del árbol (solo ordena por una llave a la vez). Finalmente, lograr que la impresión ASCII se viera bien alineada por niveles fue un reto de lógica visual.
