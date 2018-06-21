#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
//using namespace std;


enum Foo {
    consoleOut = 1,
    fileOut = 2
};

char* readFile(char* path, int size){
    char* buffer =(char*) malloc(size * sizeof(char));
    int fd = open(path, O_RDONLY);
        if(fd == -1){
        char* err = "File can't be opened \n";
        write(STDERR_FILENO, err, sizeof(char)*strlen(err));
        }else{
            int ret = read(fd, buffer, size);
            if(ret > 0){
                buffer[ret] = 0x00;
           }else{
            char* err = "Couldn't read file \n";
            write(STDERR_FILENO, err, sizeof(char)*strlen(err));
           }
           int closed = close(fd);
           if(closed == 0){
            char* out = "File closed \n";
            write(STDOUT_FILENO, out, sizeof(char)*strlen(out));
           }else{
            char* err = "Couldn't close file \n";
            write(STDERR_FILENO, err, sizeof(char)*strlen(err));
           }
        }

    return buffer;
}

void printText(char* buffer, Foo foo){
    if(foo == 1){
        int length = strlen(buffer);
        int half = length/2;
        char *text= (char*) malloc(sizeof(buffer)*sizeof(char));
        int i = half;
        int k = 0;
        while (i>=half && i<length){
            text[k] = buffer[i];
            k++;
            i++;
        }
        int j = 0;
        while (j<half){
            text[k] = buffer[j];
            k++;
            j++;
        }
        write(STDOUT_FILENO, text, 1024);
    } else {
        char *path = "/home/jan/Schreibtisch/test2.txt";
        //mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
        int fd = open(path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        write(fd, buffer, sizeof(char)*strlen(buffer));
        close(fd);
    }
}

int main(int argc, char *argv[]){
    char *path = "/home/jan/Schreibtisch/test.txt";
    int size = 2048;
    char *text =(char*) malloc(size * sizeof(char));
    text = readFile(path, size);
    printText(text, consoleOut);
    printText(text, fileOut);
    free(text);
}
