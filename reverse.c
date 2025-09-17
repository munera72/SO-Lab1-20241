#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int control(int argc, char *argv[]);
int readfile(char *filename, char **contentArray, int lineCount, int maxLineLength);
int writefile(char *filename, char **content, int lineCount);
int countlines(char *filename, int *maxLineLength);
int printContentReversed(char **content, int lineCount);
int readConsoleAndReverseInput(char **contentArray, int *lineCount);


int main(int argc, char *arcv[]){   
    return control(argc, arcv);
}

int control(int argc, char *argv[]){

    char **contentArray;
    int lineCount = 0;
    int maxLineLength = 0;

    if (argc > 1 && argc < 4)
    {
        maxLineLength = 0;
        lineCount = countlines(argv[1], &maxLineLength);
        contentArray = malloc(lineCount * sizeof(char*));
    }

    switch (argc)
    {
    case 3:
        if (strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "El archivo de entrada y salida deben diferir\n");
        exit(1);
        }
        readfile(argv[1], contentArray, lineCount, maxLineLength);
        writefile(argv[2], contentArray, lineCount);
        break;
    case 2:
        readfile(argv[1], contentArray, lineCount, maxLineLength);
        printContentReversed(contentArray, lineCount);
        break;
    case 1:
        readConsoleAndReverseInput(contentArray, &lineCount);
        break;
    default:
        break;
    }
    free(contentArray);

    return 0;
}

int readfile(char *filename, char **contentArray, int lineCount, int maxLineLength){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", filename);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    for (int i = 0; i < lineCount; i++) {
        contentArray[i] = malloc((len + 1) * sizeof(char) * maxLineLength);
        read = getline(&line, &len, fp);

        if (line[read-1] != '\n')
        {
            line[read] = '\n';
            line[read+1] = '\0';
            read += 1;
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

    if (fp == NULL) {
        fprintf(stderr, "Error opening file for writing");
        return 1;
    }
    for (int i = lineCount - 1; i >= 0; i--) {
        fprintf(fp, "%s", content[i]);
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

int readConsoleAndReverseInput(char **contentArray, int *lineCount){
    char *line;
    printf("¿Cuántas líneas desea ingresar?: ");
    scanf("%d", lineCount);
    contentArray = malloc(*lineCount * sizeof(char *));
    
    for (int i = *lineCount ; i >=0; i--){
        size_t len = 0;
        contentArray[i] = malloc(sizeof(char*));
        getline(&line, &len, stdin);
        sprintf(contentArray[i], "%s", line);
    }
    printf("\nEl contenido ingresado invertido es: \n");
     for (int i = 0; i < *lineCount; i++) {
    fprintf(stdout, contentArray[i]);}

    return 0;
}

int countlines(char *filename, int *maxLineLength) {
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
        if (read > *maxLineLength) {
            *maxLineLength = read;
        }
        count++;
    }

    if (line) {
        free(line);
    }

    fclose(fileContent);
    return count;
}
