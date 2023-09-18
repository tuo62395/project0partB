#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv){
    //less than 2 arguments = error
    if(argc < 3){
        puts("error: too few arguments");
        exit(EXIT_FAILURE);
    }
    //if there are more than 2 arguments, ONLY the last one should be a directory
    int noDir = 1;

    if(argc > 2){
        struct stat buffer;
        for (int i = 1; i < argc; i++){
            stat(argv[i], &buffer);
            if (S_ISDIR(buffer.st_mode) != 0){ //check if it's a directory
                noDir = 0;
                if (i < argc - 1){
                    puts("Invalid arguments: directories can only come last");
                    exit(EXIT_FAILURE);
                }
            } else {
                if (i == argc - 1 && argc > 3){
                    puts("Invalid arguments: last argument is not a directory");
                    exit(EXIT_FAILURE);
                }
            }
        }

    }

    //end of error checking

    //first, handling 2 arguments: sourceFile, destFile
    if(noDir){
        //open source file
        FILE *sourceFile = fopen(argv[1], "r");
        if (sourceFile == NULL){
            printf("Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        //open destination file
        FILE *destFile = fopen(argv[2], "w");
        if (destFile == NULL){
            printf("Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        //iterate through source file
        int c;
        while((c = fgetc(sourceFile)) != EOF){
            fprintf(destFile, "%c", c);
        }
        
        fclose(sourceFile);
        fclose(destFile);
    }

    
    return 0;
}