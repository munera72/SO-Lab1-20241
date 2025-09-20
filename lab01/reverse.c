#include <stdio.h>
#include <stdlib.h>

char* openFile(const char *filename, long *file_size, FILE **fileText) {
    char *buffer; 

    // abrir archivo
    *fileText = fopen(filename, "r");
    if (*fileText == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", filename);
        exit(1);
    }  

    // Obtener tamaño
    fseek(*fileText, 0, SEEK_END); 
    *file_size = ftell(*fileText); 
    rewind(*fileText);

    // Reservar memoria
    buffer = malloc((*file_size + 1) * sizeof(char));
    if (buffer == NULL) {
        fclose(*fileText);
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    // Leer archivo en el buffer
    fread(buffer, sizeof(char), *file_size, *fileText);
    buffer[*file_size] = '\0';

    fclose(*fileText);

    return buffer;
}

void writeIntoFile(const char *buffer, long file_size, FILE *out) {
    // usar stdout si no espececifica archivo de salida
    FILE *dest = (out == NULL) ? stdout : out;

    long end = file_size;
    
    for (long i = file_size - 1; i >= 0; i--) {
        if (buffer[i] == '\n') {
            // imprimir desde el caracter después de '\n' hasta 'end'
            fwrite(&buffer[i + 1], 1, end - i - 1, dest);
            fputs("\n", dest);
            end = i; // actualizar el final al salto de línea actual
        }
    }
    // imprimo la primera linea que no tiene '\n' antes
    fwrite(buffer, 1, end, dest);
}

char* readAllFromStdin(long *size) {

    //archvo temporal para guardar la entrada
    FILE *tmp = tmpfile();
    if (!tmp) {
        fprintf(stderr, "no se pudo crear archivo temporal\n");
        exit(1);
    }

    int c;
    long length = 0;

    //ver si hay entrada y auntualizo el tamaño + guardo en archivo temporal
    while ((c = getchar()) != EOF) {
        fputc(c, tmp);
        length++;
    }

    if (length == 0) {
        fclose(tmp);
        *size = 0;
        return NULL;
    }

    // reservar memoria para el texto
    char *buffer = malloc(length);
    if (!buffer) {
        fprintf(stderr, "malloc failed\n");
        fclose(tmp);
        exit(1);
    }

    // volver al inicio del archivo
    rewind(tmp);

    fread(buffer, 1, length, tmp);
    fclose(tmp);

    *size = length;
    return buffer;
}

void compareStrings(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return;
        }
        str1++;
        str2++;
    }
    if (*str1 == *str2) {
        fprintf(stderr, "El archivo de entrada y salida deben diferir\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    
    long file_size;
    char *buffer;
    FILE *fileText; 
    FILE *outputPtr;

    if (argc == 1)
    {
        buffer = readAllFromStdin(&file_size);
        writeIntoFile(buffer, file_size, NULL);
        fprintf(stdout, "\n");
        exit(0);
    }
    else if (argc == 2) {
        buffer = openFile(argv[1], &file_size, &fileText);
        writeIntoFile(buffer, file_size, NULL);
        fprintf(stdout, "\n");
        exit(0);

    } else if (argc == 3)
    {   
        compareStrings(argv[1], argv[2]);
        buffer = openFile(argv[1], &file_size, &fileText);
        outputPtr = fopen(argv[2], "w");
        writeIntoFile(buffer, file_size, outputPtr);
        fclose(outputPtr);
        exit(0);
    }
    else if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
    
        exit(1);
    }
}