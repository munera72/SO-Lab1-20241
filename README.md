# Realizado por:
Santiago Correa Castillo y Emanuel Munera Pérez


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
## Funciones personalizadas

- `openFile`: Abre un archivo de texto, obtiene su tamaño, reserva memoria y lee todo su contenido en un buffer.
- `writeIntoFile`: Escribe el contenido invertido línea por línea en el archivo de salida o en la salida estándar.
- `readAllFromStdin`: Lee toda la entrada estándar y la almacena en memoria.
- `compareStrings`: Verifica que los nombres de los archivos de entrada y salida sean diferentes.
  
La solución completa se encuentra dentro de la carpeta `lab01`.
