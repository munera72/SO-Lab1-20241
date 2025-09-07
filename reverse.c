#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//void control(int argc, char *argv[]);
int readfile(char *filename);
int writefile(char *filename, char *content);

int main(int argc, char *arcv[]){
    printf("This is the amount of arguments %d\n", argc);
    printf("The arguments are as follows:\n");
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, arcv[i]);
    }

    // control(argc, arcv);

    return readfile(arcv[1]);
}


int readfile(char *filename){
    FILE *fp = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
        writefile("output.txt", line);
    }

    fclose(fp);
    if (line) {
        free(line);
    }
    return 0;
}

int writefile(char *filename, char *content){
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file for writing");
        return 1;
    }
    fprintf(fp, "%s\n", content);

    fclose(fp);
    return 0;
}
