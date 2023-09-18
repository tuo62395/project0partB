#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>

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

    //first, handling 2 arguments: sourceFile, destFile (no directories)
    if(noDir && argc == 3){
        //open source file
        int sourceFile;
        if ((sourceFile = open(argv[1], O_RDONLY)) == -1){
            puts("Error: failed to open file");
            exit(EXIT_FAILURE);
        }

        //open destination file
        int destFile;
        if ((destFile = open(argv[2], O_CREAT | O_WRONLY, 0777)) == -1){
            puts("Error: failed to open file");
            exit(EXIT_FAILURE);
        }
        
        //iterate through source file

        int bufferSize = 100;
        int *buffer[bufferSize];
        int bytesRead;

        while ((bytesRead = read(sourceFile, buffer, bufferSize)) != 0){
            write(destFile, buffer, bytesRead);

        }

        close(sourceFile);
        close(destFile);
        
        
    }

    //cases with directories at the end
    if(noDir == 0){
        //iterate through arguments
        for(int i = 1; i < argc - 1; i++){
            //open the source
            int sourceFile;
            if ((sourceFile = open(argv[i], O_RDONLY)) == -1){
                puts("Error: failed to open file");
                exit(EXIT_FAILURE);
            }

            //open the destination

            //building the destination path name
            char destPath[100];
            destPath[0] = '\0';
            strcat(destPath, argv[argc - 1]);
            strcat(destPath, "/");
            strcat(destPath, basename(argv[i]));
            printf("destination path is: %s\n", destPath);

            int destFile;
            if ((destFile = open(destPath, O_CREAT | O_WRONLY, 0777)) == -1){
                puts("Error: failed to open file");
                exit(EXIT_FAILURE);
            }

            //iterate through source file

            int bufferSize = 100;
            int *buffer[bufferSize];
            int bytesRead;

            while ((bytesRead = read(sourceFile, buffer, bufferSize)) != 0){
                write(destFile, buffer, bytesRead);

            }

            close(sourceFile);
            close(destFile);

        }
    }

    
    return 0;
}