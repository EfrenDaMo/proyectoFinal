# Proyecto Final: El Ahorcado

Uno recreación del juego conocido como **"El Ahorcado"** en la terminal utilizando C.

## Tabla de contenidos
[Que es "El ahorcado"](#que-es-el-ahorcado)

[Como lo desarrollamos](#como-lo-desarrollamos)

- [Manejo de archivos](#manejo-de-archivos)

- [Procesamiento de la frase](#el-procesamiento-de-la-frase)

- [Manejo de archivos](#manejo-de-la-lógica-del-juego)

- [Manejo de archivos](#impresión-de-la-interfaz)

## ¿Que es "El ahorcado"?

El ahorcado es un juego que puede ser jugado por dos o más jugadores. Donde se establece una palabra o frase por un jugador, y los demás jugadores deben de adivinarla una letra a la vez. 

Si la letra adivinada es correcta se escribe donde aparece en la frase o palabra. Si la letra adivinada es incorrecta se empieza formando el cuerpo del muñeco. Empezando con la cabeza, siguiendo con el cuerpo, después sus dos brazos y al último las piernas.

Esto se repite hasta que los jugadores hayan adivinado la palabra o frase, o hasta que se halla completado el muñeco colgado. Donde los jugadores ganan o pierden respectivamente.

## Como lo desarrollamos

En nuestro caso se nos pidieron ciertas condiciones con la cuales debíamos de cumplir

- Leer las palabras de un archivo
- Utilizar como mínimo 3 funciones

A base de esos decidimos repartir la funcionalidad del código en varias partes.

- El manejo de los archivos
- El procesamiento de la frase
- El manejo de la lógica del juego
- La impresión de la interfaz

### Manejo de archivos

Para llevar acabo el manejo de los archivos fue algo bastante fácil. Simplemente pasamos la selección del archivo por un menu usando una instrucción switch...case, con un caso correspondiente a cada categoría.

### El procesamiento de la frase

Empezamos leyendo una linea aleatoria del documento que pertenece a la categoría seleccionada.

Siguiente a base de la linea leída del documento, utilizamos una cadena de caracteres de forma semi-dinámica, con el uso de las funciones **malloc()** y **realloc()**, para asegurarnos que se pueda regresar la frase de forma correcta y sin caracteres de sobra.

Siguiente utilizamos el mismo método para extraer de la frase exactamente los caracteres alfabéticos sin repetir, para formar una lista de letras esperadas. Por ultimo organizamos la lista con el método de burbuja para facilitar la comparación entre dos listas.

Este mismo método lo aplicamos para la pista de la frase.

### Manejo de la lógica del juego

Utilizando una serie de variables llevamos el control fácil de la lógica del juego, las variables mas importantes en este caso siendo:

- La cuenta de errores
- La letra introducida
- Lista de letras correctas
- Lista de letras incorrectas

#### La cuenta de errores

Esta lleva cuenta le los errores cometidos por el jugador y termina el juego en el caso que el jugador rebase los 5 errores. También se usa para la interfaz.

#### La letra introducida

Esta se usa para tomar control de las letras registradas por el usuario al adivinar. Esta letra se compara con la lista de letras en la frase, si esta se encuentra dentro de la lista se registra en una lista con las demás letras correctas. Si no se encuentra se registra en una lista con las demás letras incorrectas.

#### Lista de letras correctas

Esta contiene todas las letras que el jugador haya adivinado de forma correcta. Esta se maneja como una cadena semi-dinámica aplicando las funciones de **malloc()** y **realloc()**. 

Esta se organiza con el método de burbuja y se compara con la lista de las letras de la frase, para determinar si el usuario a adivinado correctamente la frase, al final de cada ciclo del juego.

Esta también se usa para la interfaz, y para prohibir que el usuario de adivine la misma letra mas de una vez.

#### Lista de letras incorrectas

Esta contiene todas las letras que el jugador haya adivinado de forma incorrecta. Esta se maneja como una cadena semi-dinámica aplicando las funciones de **malloc()** y **realloc()**.

Esta se utiliza en su mayoría para la interfaz, también para prohibir al usuario de adivinar la misma letra mas de una vez.

### Impresión de la interfaz

Esta se maneja en 3 partes principales:

- La parte superior
- La parte central
- La parte inferior

Cada una de estas partes son manejadas por serie de variables que determinan como se debe de imprimir la interfaz y que debe de llevar.

#### La parte superior

Esta contiene un poco de información básica fundamental para el usuario, como lo es la categoría de la frase, la pista para la frase y la guía.

En su mayoría las primeras dos se dan a entender por si mismas, estas le dan una idea al usuario para poder adivinar mejor la frase. Estas no cambian, al menos que se vuelva a iniciar el juego.

La que puede ser un poco mas confusa es la guía, pero no es nada mas que una frase pequeña diciéndole al jugador si lo que adivino fue correcto o incorrecto, si la letra ya fue adivinada, o si el jugador ha perdido o ganado.

#### La parte central

Esta parte contiene la parte fundamental del juego, siendo el muñeco, los errores, las letras faltantes y la frase por adivinar.

El muñeco es manejado por la cantidad de errores que ha acumulado el usuario empezando del 0 y llegando hasta 6, donde le muñeco es colgado al momento que pierde el jugador. Ademas de eso si el jugador gana el muñeco es bajado de la **horca** y se encuentra a un lado de ella. 

Los errores y las letras faltantes son consideradas un solo elemento. Estas puede ser explicadas fácilmente por sus nombres. Se manejar al igual que el muñeco con la variable de cuenta de errores y con la diferencia que hay entre la lista de letras de la frase y la lista de letras adivinadas correctamente.

La frase por adivinar es algo similar ya que se imprimen primero todos los caracteres no alfabético (con algunas excepciones, algún carácter con acento se reconoce como no alfabético), al mismo tiempo si la letra no ha sido adivinada se imprime un **"_"** en su lugar. Si la letra ya fue adivinada, se imprime como normal. En el caso de que el jugador pierda la frase es revelada debajo de este elemento.

#### La parte inferior

Esta parte solo contiene dos elementos. El banco de letras y el registro de entrada del usuario. Aunque se puede explicar por su nombre, el banco del letras contiene algo de funcionalidad, ya que se actualiza cada ciclo para indicar si la letra adivinada fue correcta, reemplazándola con un **"1"** o si fueron incorrectas, reemplazándola con un **"0"**.
