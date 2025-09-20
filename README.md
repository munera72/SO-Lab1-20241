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

## Ejemplo

```bash
./reverse ejemplo.txt invertido.txt
```

Esto crea `invertido.txt` con el contenido de `ejemplo.txt` invertido.
