#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void control(int argc, char *argv[]);
void readfile(char *filename, char **contentArray, int lineCount);
void readfilefrompointer(FILE *fp, char **contentArray, int lineCount);
void writefile(char *filename, char **content, int lineCount);
int countlines(char *filename);
void printContentReversed(char **content, int lineCount);
FILE *readConsoleAndCreateTempFile(int *lineCount);


int main(int argc, char *arcv[]){   
    control(argc, arcv);
    return 0;
}

void control(int argc, char *argv[]){

    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    char **contentArray;
    int lineCount = 0;

    if (argc == 2 || argc == 3)
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
        contentArray = malloc(lineCount * sizeof(char*));
        if (contentArray == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        readfilefrompointer(tempFile, contentArray, lineCount);
        printContentReversed(contentArray, lineCount);
        fclose(tempFile);
        break;
    default:
        break;
    }
    free(contentArray);
    return;
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

    return;
}

void readfile(char *filename, char **contentArray, int lineCount){
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
    
    return;
}

void writefile(char *filename, char **content, int lineCount){
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
    return;
}

void printContentReversed(char **content, int lineCount){
    printf("\nContenido en orden inverso:\n");
    for (int i = lineCount-1; i >= 0; i--) {
        printf("%s", content[i]);
    }
    return;
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
