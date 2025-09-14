#include <stdio.h>
#include <stdlib.h>


//void control(int argc, char *argv[]);
int control(int argc, char *argv[]);
int readfile(char *filename, char **contentArray, int lineCount, int maxLineLength);
int writefile(char *filename, char **content, int lineCount);
int countlines(char *filename, int *maxLineLength);


int main(int argc, char *arcv[]){
    printf("This is the amount of arguments %d\n", argc);
    printf("The arguments are as follows:\n");
    
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, arcv[i]);
    }

    
    return control(argc, arcv);
}


int control(int argc, char *argv[]){
    
    int maxLineLength = 0;
    int lineCount = countlines(argv[1], &maxLineLength);
    char **contentArray = malloc(lineCount * sizeof(char*));

    switch (argc)
    {
    case 2:
        printf("Reading file %s\n", argv[1]);
        readfile(argv[1], contentArray, lineCount, maxLineLength);
        printf("The file has been read\n");
        writefile("output.txt", contentArray, lineCount);
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
        printf("Loop %d\n", i);
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
