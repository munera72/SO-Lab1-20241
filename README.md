# Realizado por:
Santiago Correa Castillo y Emanuel Munera Pérez

# Práctica 1 de laboratorio - Introducción al lenguaje C

> ## Objetivos
> * Aprender a codificar programas usando el lenguaje C a nivel básico e intermedio.
> * Aprender a usar las herramientas básicas para desarrollar aplicaciones en un ambiente de desarrollo linux.

# reverse.c - Descripción y Funcionamiento

Este programa, `reverse`, es una utilidad escrita en C que invierte el orden de las líneas de un archivo de texto o de la entrada estándar. El programa puede ser ejecutado de tres formas distintas:

- **Sin argumentos:** Lee líneas desde la entrada estándar (teclado) y las imprime en orden inverso en la pantalla.
- **Con un argumento:** Lee líneas desde el archivo especificado y las imprime en orden inverso en la pantalla.
- **Con dos argumentos:** Lee líneas desde el primer archivo y las escribe en orden inverso en el segundo archivo.

## Uso

```sh
./reverse
./reverse <input>
./reverse <input> <output>
```

## Funcionalidad

- **Lectura de líneas:** Utiliza la función `getline()` para leer líneas de cualquier longitud desde archivos o la entrada estándar.
- **Almacenamiento dinámico:** Almacena cada línea en un arreglo dinámico de cadenas, reservando memoria con `malloc()`.
- **Inversión de líneas:** Imprime o escribe las líneas en orden inverso al que fueron leídas.
- **Manejo de errores:** 
  - Si el archivo de entrada o salida no puede abrirse, muestra un mensaje de error y termina.
  - Si la memoria no puede ser reservada, muestra un mensaje de error y termina.
  - Si el archivo de entrada y salida son el mismo, muestra un mensaje de error y termina.
  - Si se pasan demasiados argumentos, muestra el mensaje de uso y termina.

## Funciones principales

- `main()`: Punto de entrada, gestiona los argumentos y llama a la función de control.
- `control()`: Determina el modo de operación según los argumentos y coordina la lectura, inversión y escritura/imprensión de líneas.
- `readfile()`, `readfilefrompointer()`: Leen líneas desde un archivo o desde un puntero a archivo.
- `writefile()`: Escribe las líneas invertidas en un archivo de salida.
- `printContentReversed()`: Imprime las líneas invertidas en pantalla.
- `readConsoleAndCreateTempFile()`: Lee líneas desde la entrada estándar y las almacena temporalmente.
- `countlines()`: Cuenta el número de líneas en un archivo.

## Ejemplo

Si el archivo `input.txt` contiene:

```
hello
this
is
a file
```

La ejecución `./reverse input.txt` mostrará:

```
a file
is
this
hello
```

## Notas

- El programa está diseñado para funcionar en sistemas Linux.
- Todos los mensajes de error se envían a la salida estándar de error (`stderr`).
- El código es robusto ante archivos y líneas de cualquier tamaño.

---
