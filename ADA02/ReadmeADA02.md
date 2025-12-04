# ADA 02 
Esta actividad se centró en la implementación de una simulación estocástica para modelar la atención al cliente en un banco. El objetivo técnico fue programar un sistema en lenguaje C que gestionara el flujo de usuarios a través de tres cajas de atención simultáneas.

El programa debía generar clientes de manera aleatoria, asignándoles una carga de trabajo (número de transacciones/tiempo) y dirigiéndolos a una de las tres colas disponibles. El núcleo del proyecto fue el desarrollo de un algoritmo que administrara el ciclo de vida del cliente: su llegada (enqueue), su tiempo de espera y su salida (dequeue) tras ser atendido. Finalmente, el sistema debía procesar los datos recolectados para presentar métricas de eficiencia, como el tiempo promedio de espera por cola y el caudal de clientes atendidos.

Reflexión Personal

¿Qué se aprendió? El aprendizaje más significativo fue la aplicación práctica de la estructura de datos lineal Cola (Queue) bajo el principio FIFO (First In, First Out). Comprendí cómo esta estructura es ideal para modelar sistemas de espera y procesos secuenciales.

Además, reforcé mis conocimientos en el uso de structs en C para encapsular información compleja (creando un tipo de dato abstracto "Cliente") y aprendí a manejar la generación de números pseudoaleatorios para simular eventos de la vida real (llegada de personas y duración de trámites).

Problemas y desafíos: El mayor reto fue la lógica de la simulación del "tiempo". Coordinar que las tres cajas funcionaran simultáneamente y descontaran el tiempo de transacción de cada cliente en cada ciclo del bucle fue complejo. También tuve algunos problemas iniciales con la gestión de memoria dinámica (punteros) al momento de encolar y desencolar, asegurándome de no perder referencias a los nodos. Por último, calcular los promedios requirió cuidado para evitar errores de división por cero en caso de que alguna caja no recibiera clientes aleatoriamente.
