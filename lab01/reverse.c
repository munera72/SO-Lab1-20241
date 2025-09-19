#include <stdio.h>
#include <stdlib.h>

void writeIntoFile(const char *buffer, long file_size, FILE *out) {
    // Si no llega archivo, usar stdout
    FILE *dest = (out == NULL) ? stdout : out;

    long end = file_size;  // fin de la última línea
    
    for (long i = file_size - 1; i >= 0; i--) {
        if (buffer[i] == '\n') {
            // imprimir desde el caracter después de '\n' hasta 'end'
            fwrite(&buffer[i + 1], 1, end - i - 1, dest);
            fputs("\n", dest);
            end = i; // actualizar el final al salto de línea actual
        }
    }

    // imprimir la primera línea (que no tiene salto antes)
    fwrite(buffer, 1, end, dest);
}

char* openFile(const char *filename, long *file_size, FILE **fileText) {
    char *buffer; 

    *fileText = fopen(filename, "r");   // abrir archivo
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

char* readAllFromStdin(long *size) {
    char *buffer = NULL;
    long capacity = 0;
    long length = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (length >= capacity) {
            capacity = capacity ? capacity * 2 : 1024; // crecer dinámicamente
            char *tmp = realloc(buffer, capacity);
            if (!tmp) {
                free(buffer);
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }
            buffer = tmp;
        }
        buffer[length++] = (char)c;
    }

    if (length == 0) {
        return NULL; // no se leyó nada
    }

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