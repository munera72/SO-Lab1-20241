# reverse.c

Este programa invierte el contenido de un archivo de texto.

## Uso

1. Compila el programa:
  ```bash
  gcc reverse.c -o reverse
  ```

2. Ejecuta el programa pasando el archivo de entrada y el archivo de salida:
  ```bash
  ./reverse archivo_entrada.txt archivo_salida.txt
  ```

El archivo `archivo_salida.txt` contendrá el contenido de `archivo_entrada.txt` pero en orden invertido.

## Funcionamiento

El programa lee el archivo de entrada, almacena su contenido en memoria y luego lo escribe en el archivo de salida en orden inverso. Si hay errores al abrir los archivos o al leer/escribir, se muestra un mensaje de error.

## Funciones principales

- `fopen`: Abre archivos para lectura y escritura.
- `fclose`: Cierra los archivos abiertos.
- `fseek`: Mueve el puntero de lectura/escritura dentro del archivo.
- `ftell`: Obtiene la posición actual del puntero en el archivo.
- `fread`: Lee datos del archivo de entrada.
- `fwrite`: Escribe datos en el archivo de salida.
- `malloc`/`free`: Reserva y libera memoria para almacenar el contenido del archivo.
- `perror`: Muestra mensajes de error si ocurre algún problema con los archivos.

## Ejemplo

```bash
./reverse ejemplo.txt invertido.txt
```

Esto crea `invertido.txt` con el contenido de `ejemplo.txt` invertido.
