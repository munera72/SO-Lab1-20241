#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int control(int argc, char *argv[]);
int readfile(char *filename, char **contentArray, int lineCount);
void readfilefrompointer(FILE *fp, char **contentArray, int lineCount);
int writefile(char *filename, char **content, int lineCount);
int countlines(char *filename);
int printContentReversed(char **content, int lineCount);
FILE *readConsoleAndCreateTempFile(int *lineCount);


int main(int argc, char *arcv[]){   
    return control(argc, arcv);
}

int control(int argc, char *argv[]){

    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    char **contentArray;
    int lineCount = 0;

    if (argc > 1 && argc < 4)
    {
        lineCount = countlines(argv[1]);
        contentArray = malloc(lineCount * sizeof(char*));
        if (contentArray == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
    }

    switch (argc)
    {
    case 3:
        if (strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "El archivo de entrada y salida deben diferir\n");
        exit(1);
        }
        readfile(argv[1], contentArray, lineCount);
        writefile(argv[2], contentArray, lineCount);
        break;
    case 2:
        readfile(argv[1], contentArray, lineCount);
        printContentReversed(contentArray, lineCount);
        break;
    case 1:
        FILE *tempFile = NULL;
        tempFile = readConsoleAndCreateTempFile(&lineCount);
        printf("Número de líneas leídas: %d\n", lineCount);
        contentArray = malloc(lineCount * sizeof(char*));
        if (contentArray == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        printf("Empezando a leer el archivo temporal...\n");
        readfilefrompointer(tempFile, contentArray, lineCount);
        printf("Empezando a leer el contenido \n");
        printContentReversed(contentArray, lineCount);
        fclose(tempFile);
        break;
    default:
        break;
    }
    free(contentArray);

    return 0;
}

void readfilefrompointer(FILE *fp, char **contentArray, int lineCount){
    if (fp == NULL)
    {
        fprintf(stderr, "error: file pointer is NULL\n");
        exit(1);
    }
    

    char *line = NULL;
    size_t len = 0;
    size_t read;

    fprintf(stdout, "Leyendo archivo temporal...\n");
    for (int i = 0; i < lineCount; i++) {
        read = getline(&line, &len, fp);
        if (line[read-1] != '\n')
        {
            line[read] = '\n';
            line[read+1] = '\0';
            read += 1;
        }

        contentArray[i] = malloc((len + 1) * sizeof(char) * read);
        if (contentArray[i] == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        
        sprintf(contentArray[i], "%s", line);
    }

    if (line) {
        free(line);
    }
}

int readfile(char *filename, char **contentArray, int lineCount){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", filename);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    for (int i = 0; i < lineCount; i++) {
        read = getline(&line, &len, fp);

        if (line[read-1] != '\n')
        {
            line[read] = '\n';
            line[read+1] = '\0';
            read += 1;
        }

        contentArray[i] = malloc((len + 1) * sizeof(char) * read);
        if (contentArray[i] == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        
        sprintf(contentArray[i], "%s", line);
    }

    fclose(fp);

    if (line) {
        free(line);
    }
    
    return 0;
}

int writefile(char *filename, char **content, int lineCount){
    FILE *fp = fopen(filename, "w+");
    if (fp == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", filename);
        exit(1);
    }

    for (int i = lineCount - 1; i >= 0; i--) {
        fprintf(fp, "%s", content[i]);
        free(content[i]);
    }

    fclose(fp);
    return 0;
}

int printContentReversed(char **content, int lineCount){
    for (int i = 0; i < lineCount; i++) {
        printf("%s", content[lineCount - 1 - i]);
    }
    return 0;
}

FILE *readConsoleAndCreateTempFile(int *lineCount){ 
    char *line = NULL;
    size_t len = 0;
    size_t read;

    FILE *tempfile = tmpfile();
    if (tempfile == NULL) {
        fprintf(stderr, "error: cannot create temporary file\n");
        exit(1);
    }

    printf("Ingrese las líneas de texto (Ctrl+D para finalizar):\n");

    while ((read = getline(&line, &len, stdin)) != -1) {
        fputs(line, tempfile);
        *lineCount = *lineCount + 1;
    }

    free(line);

    rewind(tempfile);

    return tempfile;
}

int countlines(char *filename) {
    FILE *fileContent = fopen(filename, "r");
        if (fileContent == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", filename);
        exit(1);
    }
    int count = 0;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    while ((read = getline(&line, &len, fileContent)) != -1) {
        count++;
    }

    if (line) {
        free(line);
    }

    fclose(fileContent);
    return count;
}
