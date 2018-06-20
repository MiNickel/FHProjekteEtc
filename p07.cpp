#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
using namespace std;




char* readFile(char* path, int size){
    char* buffer =(char*) malloc(size * sizeof(char));
    int fd = open(path, O_RDONLY);
    if(fd == -1){
        cout << "Cannot open file" <<endl;
    }else{
        int ret = read(fd, buffer, size);
        if(ret > 0){
            buffer[ret] = 0x00;

       }else{
            cout<< "Couldn't read file" << endl;
       }
       int closed = close(fd);
       if(closed == 0){
            cout<<"File closed"<<endl;
       }else{
            cout<<"Couldn't close file" << endl;
       }
    }
    //cout << buffer;
    return buffer;
}

void printText(char* buffer){
    int length = strlen(buffer);
    int half = length/2;
    cout << half << endl;
    int i = half;
    while (i>=half && i<length){
        cout << buffer[i];
        i++;
    }
    int j = 0;
    while (j<half){
        cout << buffer[j];
        j++;
    }
}

int main(int argc, char *argv[]){
    char *path = "/home/jan/Schreibtisch/test.txt";
    int size = 2048;
    char *text =(char*) malloc(size * sizeof(char));
    text = readFile(path, size);
    cout << text;
    printText(text);
    free(text);
}
