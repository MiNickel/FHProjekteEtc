#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//#include <iostream>
//using namespace std;


enum Foo {
    consoleOut = 1,
    fileOut = 2
};

int getFileSize(char* path){
    int fd = open(path, O_RDONLY);
    struct stat fileStat;
    if(fstat(fd, &fileStat) < 0){
        return -1;
    }else{
        return fileStat.st_size;
    }
}

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
            char* out = "\n File closed \n";
            write(STDOUT_FILENO, out, sizeof(char)*strlen(out));
           }else{
            char* err = "Couldn't close file \n";
            write(STDERR_FILENO, err, sizeof(char)*strlen(err));
           }
        }

    return buffer;
}

void printText(enum Foo foo, char* path, char*pathNew, int size){
    if(foo == 1){
        char* buffer = (char*) malloc(size*sizeof(char));
        buffer = readFile(path, size);

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
        write(STDOUT_FILENO, text, size);
        write(STDOUT_FILENO, "\n", 2);
    } else {
        int offSet = 10;
        int fd = open(path, O_RDONLY);
            if(fd == -1){
                char* err = "File can't be opened \n";
                write(STDERR_FILENO, err, sizeof(char)*strlen(err));
            }

        int retSeek = lseek(fd, -11, SEEK_END);
            if(retSeek == -1){
                char* err = "Couldn't execute the seek-function on the file \n";
                write(STDERR_FILENO, err, sizeof(char)*strlen(err));
            }

        char* textNew =(char*) malloc(offSet*sizeof(char));
        int ret = read(fd, textNew, offSet);
            if(ret <= 0){
                char* err = "Couldn't read file \n";
                write(STDERR_FILENO, err, sizeof(char)*strlen(err));
            }

        int fdNew = open(pathNew, O_CREAT | O_WRONLY , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
            if(fdNew == -1){
                char* err = "File can't be opened \n";
                write(STDERR_FILENO, err, sizeof(char)*strlen(err));
            }

        int retSeekNew = lseek(fdNew, offSet, SEEK_SET);
            if(retSeekNew == -1){
                char* err = "Couldn't execute the seekfunction on the file \n";
                write(STDERR_FILENO, err, sizeof(char)*strlen(err));
            }

        write(fdNew, textNew, sizeof(char)*strlen(textNew));


        //write(STDOUT_FILENO, textNew, sizeof(char)*strlen(textNew));

        int closed = close(fd);
            if(closed != 0){
                char* err = "Couldn't close file \n";
                write(STDERR_FILENO, err, sizeof(char)*strlen(err));
            }

        int closedNew = close(fdNew);
            if(closedNew != 0){
                char* err = "Couldn't close file \n";
                write(STDERR_FILENO, err, sizeof(char)*strlen(err));
            }
    }

}

void printFile(char* path, int size){
    int fd = open(path, O_RDONLY, size);
        if(fd == -1){
            char* err = "File can't be opened \n";
            write(STDERR_FILENO, err, sizeof(char)*strlen(err));
        }
    char* fileCont = (char*) malloc(size * sizeof(char));
    int bytes = read(fd, fileCont, size);
        if(bytes <= 0){
            char* err = "Couldn't read file \n";
            write(STDERR_FILENO, err, sizeof(char)*strlen(err));
        }
    write(STDOUT_FILENO, fileCont, sizeof(fileCont)*strlen(fileCont));
}

int main(int argc, char *argv[]){

    char *path = argv[1];
    char *pathNew = argv[2];
    int size = getFileSize(path);
    printText(fileOut, path, pathNew, size);
    printFile(pathNew, size);
    printText(consoleOut, path, pathNew, size);

    //printText(consoleOut, pathNew, path, size);

}
