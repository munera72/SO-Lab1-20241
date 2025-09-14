#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//void control(int argc, char *argv[]);
int control(int argc, char *argv[]);
int readfile(char *filename, char **contentArray, int lineCount);
int writefile(char *filename, char **content, int lineCount);
int countLines(char *filename);


int main(int argc, char *arcv[]){
    printf("This is the amount of arguments %d\n", argc);
    printf("The arguments are as follows:\n");
    
    // char *content = malloc(100 * sizeof(char));
    // for (int i = 0; i < argc; i++) {
    //     printf("Argument %d: %s\n", i, arcv[i]);
    // }

    // control(argc, arcv);

    
    return control(argc, arcv);
}


int control(int argc, char *argv[]){
    
    int lineCount = countLines(argv[1]);
    char **contentArray = malloc(lineCount * sizeof(char*));

    switch (argc)
    {
    case 2:
        printf("Reading file %s\n", argv[1]);
        readfile(argv[1], contentArray, lineCount);
        printf("The file has been read\n");
        writefile("output.txt", contentArray, lineCount);
        break;
    default:
        break;
    }

    return 0;
}


int readfile(char *filename, char **contentArray, int lineCount){
    printf("The file %s has %d lines\n", filename, lineCount);
    FILE *fp = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;

    
    for (int i = 0; i < lineCount; i++) {
        contentArray[i] = malloc((len) * sizeof(char));
        getline(&line, &len, fp);
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
        fprintf(stderr, "Error opening file for writing");
        return 1;
    }
    for (int i = lineCount - 1; i >= 0; i--) {
        fprintf(fp, "%s", content[i]);
    }

    fclose(fp);
    return 0;
}


int countLines(char *filename) {
    FILE *fileContent = fopen(filename, "r");
    int count = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fileContent)) != -1) {
        count++;
    }

    fclose(fileContent);
    return count;
}
