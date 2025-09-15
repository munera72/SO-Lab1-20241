#include <stdio.h>
#include <stdlib.h>

int control(int argc, char *argv[]);
int readfile(char *filename, char **contentArray, int lineCount, int maxLineLength);
int writefile(char *filename, char **content, int lineCount);
int countlines(char *filename, int *maxLineLength);
int printContentReversed(char **content, int lineCount);
int readAndPrintConsole();


int main(int argc, char *arcv[]){
    // printf("This is the amount of arguments %d\n", argc);
    // printf("The arguments are as follows:\n");
    
    // for (int i = 0; i < argc; i++) {
    //     printf("Argument %d: %s\n", i, arcv[i]);
    // }

    
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
        printf("entered in if\n");
    }

    switch (argc)
    {
    case 3:
        // printf("Reading file %s\n", argv[1]);
        readfile(argv[1], contentArray, lineCount, maxLineLength);
        // printf("The file has been read\n");
        writefile(argv[2], contentArray, lineCount);
        break;
    case 2:
        // printf("Reading file %s\n", argv[1]);
        readfile(argv[1], contentArray, lineCount, maxLineLength);
        // printf("The file has been read\n");
        printContentReversed(contentArray, lineCount);
        break;
    case 1:
        readAndPrintConsole();
        break;
    default:
        break;
    }


    return 0;
}

int readfile(char *filename, char **contentArray, int lineCount, int maxLineLength){
    FILE *fp = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    size_t read;

    printf("starting to read file)\n");
  
    for (int i = 0; i < lineCount; i++) {
        // printf("Loop %d\n", i);
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

    printf("Finished reading file\n");

    fclose(fp);

    printf("Closed file\n");


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

int printContentReversed(char **content, int lineCount){
    for (int i = 0; i < lineCount; i++) {
        printf("%s", content[lineCount - 1 - i]);
    }
    return 0;
}

int readAndPrintConsole(){
    char * line;
    int amount;
    printf("Enter the amount of lines: ");
    scanf("%d", &amount);
    char **array = malloc(amount * sizeof(char *));
    for (int i = amount ; i >=0; i--){
        size_t len = 0;
        array[i] = malloc(sizeof(char*));
        getline(&line, &len, stdin);
        sprintf(array[i], "%s", line);
    }
    printf("Inversed Lines: \n");
     for (int i = 0; i < amount; i++) {
    printf("%s", array[i]);}

    return 0;
}

int countlines(char *filename, int *maxLineLength) {
    FILE *fileContent = fopen(filename, "r");
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

    fclose(fileContent);
    return count;
}
