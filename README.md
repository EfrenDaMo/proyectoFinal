# Proyecto Final: El Ahorcado

Uno recreacion del juego conocido como **"El Ahorcado"** en la terminal utilizando C.

## Tabla de contenidos
[Que es "El ahorcado"](#que-es-el-ahorcado)

[Como lo desarrollamos](#como-lo-desarrollamos)

- [Manejo de archivos](#manejo-de-archivos)

- [Procesamiento de la frase](#el-procesamiento-de-la-frase)

- [Manejo de archivos](#manejo-de-la-logica-del-juego)

- [Manejo de archivos](#impresion-de-la-interfaz)

[Documentación](#documentación)

## Que es "El ahorcado"

El ahorcado es un juego que puede ser jugado por dos o más jugadores. Donde se establece una palabra o frase por un jugador, y los demas jugadores deben de adivinarla una letra a la vez. 

Si la letra adivinada es correcta se escribe donde aparece en la frase o palabra. Si la letra adivinada es incorrecta se empieza formando el cuerpo del muñeco. Empezando con la cabeza, sugiendo con el cuerpo, despues sus dos brazos y al ultimo las piernas.

Esto se repite hasta que los jugadores hayan adivinado la palabra o frase, o hasta que se haya acompletado el muñeco colgado. Donde los jugadores ganan o pierden respectivamente.

## Como lo desarrollamos

En nuestro caso se nos pidieron cierta condiciones con la cuales debiamos de cumplir

- Leer las palabras de un archivo
- Utilizar como minimo 3 funciones

Ha base de esos decidimos repartir la funcionalidad del codigo en varias partes.

- El manejo de los archivos
- El procesamiento de la frase
- El manejo de la logica del juego
- La impresion de la interfaz

### Manejo de archivos

Para llevar acabo el manejo de los archivos fue algo bastante facil. Simplemente pasamos la selección del archivo por un menu usando una instruccion switch...case, con un caso correspondiente a cada categoria.

### El procesamiento de la frase

Empezamos leyendo una linea aleatoria del documento que pertenece a la categoria seleccionada.

Siguiente a base de la linea leida del documento, utilizamos una cadena de caractares de forma semi-dinamica, con el uso de las funciones **malloc()** y **realloc()**, para asegurarnos que se pueda regresar la frase de forma correcta y sin caractares de sobra.

Siguiente utilizamos el mismo metodo para extraer de la frase exactemente los caractares alfabeticos sin repetir, para formar una lista de letras esperadas. Por ultimo organizamos la lista con el metodo de burbuja para facilitar la comparacion entre dos listas.

Este mismo metodo lo aplicamos para la pista de la frase.

### Manejo de la logica del juego

Utilizando una serie de variables llevamos el control facil de la logica del juego, las variables mas importantes en este caso siendo:

- La cuenta de errores
- La letra introducida
- Lista de letras correctas
- Lista de letras incorrectas

#### La cuenta de errores

Esta lleva cuenta le los errores cometidos por el jugador y termina el juego en el caso que el jugador rebase los 5 errores. Tambien se usa para la interfaz.

#### La letra introducida

Esta se usa para tomar control de las letras registradas por el usuario al adivinar. Esta letra se compara con la lista de letras en la frase, si esta se encuentra dentro de la lista se registra en una lista con las demas letras correctas. Si no se encuentra se registra en una lista con las demas letras incorrectas.

#### Lista de letras correctas

Esta contiene todas las letras que el jugador haya adivinado de forma correcta. Esta se maneja como una cadena semi-dinamica aplicando las funciones de **malloc()** y **realloc()**. 

Esta se organiza con el metodo de burbuja y se compara con la lista de las letras de la frase, para determinar si el usuario a adivinado correctamente la frase, al final de cada ciclo del juego.

Esta tambien se usa para la interfaz, y para prohibir que el usuario de adivine la misma letra mas de una vez.

#### Lista de letras incorrectas

Esta contiene todas las letras que el jugador haya adivinado de forma incorrecta. Esta se maneja como una cadena semi-dinamica aplicando las funciones de **malloc()** y **realloc()**.

Esta se utiliza en su mayoria para la interfaz, tambien para prohibir al usuario de adivinar la misma letra mas de una vez.

### Impresion de la interfaz

Esta se maneja en 3 partes principales:

- La parte superior
- La parte central
- La parte inferior

Cada una de estas partes son manejadas por serie de variables que determinan como se debe de imprimir la interfaz y que debe de llevar.

#### La parte superior

Esta contiene un poco de informacion basica fundamental para el usuario, como lo es la categoria de la frase, la pista para la frase y la guia.

En su mayoria las primeras dos se dan a entender por si mismas, estas le dan una idea al usuario para poder adivinar mejor la frase. Estas no cambian, almenos que se vuelva a iniciar el juego.

La que puede ser un poco mas confusa es la guia, pero no es nada mas que una frase pequeña diciendole al jugador si lo que adivino fue correcto o incorrecto, si la letra ya fue adivinada, o si el jugador ha perdido o ganado.

#### La parte central

Esta parte contiene la parte fundamental del juego, siendo el muñeco, los errores, las letras faltantes y la frase por adivinar.

El muñeco es manejado por la cantidad de errores que ha acomulado el usuario empezando del 0 y llegando hasta 6, donde le muñeco es colgado al momento que pierde el jugador. Ademas de eso si el jugador gana el muñeco es bajado de la **horca** y se encunetra a un lado de ella. 

Los errores y las letras faltantes son consideradas un solo elemento. Estas son algo explicatorias por sus nombres. Se manejar al igual que el muñeco con la variable de cuenta de errores y con la diferencia que hay entre la lista de letras de la frase y la lista de letras adivinadas correctamente.

La frase por adivinar es algo similar ya que se imprimen primero todos los caractares no alfabetico (con algunas excepciones, algun caracter con accento se reconoce como no alfabetico), al mismo tiempo si la letra no ha sido adivinada se imprime un **"_"** en su lugar. Si la letra ya fue adivinada, se imprime como normal. En el caso de que el jugador pierda la frase es revelada debajo de este elemento.

#### La parte inferior

Esta parte solo contiene dos elementos. El banco de letras y el registro de entrada del usuario. Aunque se puede explicar por su nombre, el banco del letras contiene algo de funcionalidad, ya que se actualiza cada ciclo para indicar si la letra avidinada fue correcta, remplazandola con un **"1"** o si fueron incorrectas, remplazandola con un **"0"**.
