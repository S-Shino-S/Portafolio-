El objetivo de esta actividad fue desarrollar un analizador sintáctico (parser) capaz de interpretar y resolver expresiones matemáticas complejas. La tarea consistió en crear un programa de consola que funcionara mediante argumentos de línea de comandos para procesar archivos de texto.

El flujo del programa se dividió en dos fases algorítmicas:

Conversión de Notación: Transformar expresiones matemáticas estándar (infijas), como 2*(3+4), a Notación Polaca Inversa (postfija), como 2 3 4 + *, eliminando la necesidad de paréntesis para definir la jerarquía.

Evaluación: Calcular el resultado numérico procesando la cadena postfija generada.

El programa debía leer un archivo de entrada con múltiples expresiones delimitadas por punto y coma, y generar un archivo de salida que incluyera tanto la versión postfija de la expresión como su resultado final.

Reflexión Personal ¿Qué se aprendió? Esta actividad fue fundamental para comprender cómo los compiladores interpretan el código matemático. Aprendí a implementar y manipular la estructura de datos de Pila (Stack), la cual es esencial para el algoritmo de conversión (generalmente el Shunting Yard) y para la evaluación posterior. Entendí la lógica detrás de la jerarquía de operadores (precedencia) y cómo la notación postfija simplifica el cálculo computacional al linealizar la expresión.

Problemas y desafíos: Uno de los principales retos fue el manejo correcto de los paréntesis dentro de la pila para asegurar que las operaciones se ordenaran correctamente según su prioridad. También tuve dificultades iniciales al "tokenizar" la cadena de entrada; por ejemplo, distinguir entre números de varios dígitos (como "15") y dígitos individuales, así como manejar los espacios en blanco y el delimitador final. Finalmente, la gestión de entrada/salida de archivos (File I/O) a través de la terminal requirió un manejo cuidadoso de los flujos de datos para evitar errores de lectura.
