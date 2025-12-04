# ADA 03
El objetivo central de esta práctica fue la implementación y manipulación de una estructura de datos dinámica avanzada: la Lista Doblemente Ligada. El proyecto consistió en desarrollar un sistema de gestión de películas que cargara información masiva desde un archivo externo (Movie.csv) hacia la memoria del programa.

A diferencia de las listas simples, debí programar nodos que mantuvieran referencias tanto al elemento siguiente como al anterior, permitiendo una navegación bidireccional. El sistema debía cumplir con operaciones CRUD completas (Crear, Leer, Actualizar, Borrar), destacando funciones de búsqueda flexible (por título o por actor, incluyendo coincidencias parciales), inserción de nodos en posiciones arbitrarias y eliminación segura de registros previa confirmación del usuario.

Reflexión Personal

¿Qué se aprendió? Aprendí a gestionar la memoria dinámica con mayor precisión, entendiendo la ventaja de las listas dobles para recorrer datos en ambas direcciones sin necesidad de reiniciar el ciclo desde la cabecera (head). Reforcé mis habilidades en el manejo de archivos (File I/O) y parsing de datos, ya que tuve que leer cadenas de texto separadas por comas y convertirlas en atributos de un objeto o struct. También aprendí algoritmos de búsqueda de subcadenas (string matching) para permitir que el usuario encuentre una película sin necesidad de escribir el nombre exacto.

Problemas y desafíos: El desafío técnico más grande fue la manipulación de punteros durante la inserción y eliminación. En una lista doble, si olvidas actualizar el puntero prev del nodo siguiente o el next del nodo anterior, la lista se rompe, lo que me causó varios errores de segmentación (segmentation faults) al principio. Otro problema fue la lectura del archivo CSV, ya que algunos títulos de películas contenían comas dentro del nombre, lo que confundía al separador de datos y requirió una lógica de lectura más robusta para no mezclar los atr
