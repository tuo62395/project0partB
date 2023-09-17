#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char **argv){
    //less than 2 arguments = error
    if(argc < 3){
        puts("error: too few arguments");
        exit(EXIT_FAILURE);
    }
    //if there are more than 2 arguments, ONLY the last one should be a directory

    if(argc > 3){
        struct stat buffer;
        for (int i = 1; i < argc; i++){
            stat(argv[i], &buffer);
            if (S_ISDIR(buffer.st_mode) != 0){ //check if it's a directory
                if (i < argc - 1){
                    puts("Invalid arguments: directories can only come last");
                    exit(EXIT_FAILURE);
                }
            } else {
                if (i == argc - 1){
                    puts("Invalid arguments: last argument is not a directory");
                    exit(EXIT_FAILURE);
                }
            }
        }

    }

    
    return 0;
}