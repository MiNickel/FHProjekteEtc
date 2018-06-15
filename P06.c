#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>

#define NUMBER_OF_STRINGS 2
#define STRING_LENGTH 128

typedef struct {
    char *content;
    char *directory;
} Job;

Job *job1;
Job *job2;

Queue queue;

char filePath[] = "";
char data[NUMBER_OF_STRINGS][STRING_LENGTH];
char temp[NUMBER_OF_STRINGS][STRING_LENGTH];
char fileName[NUMBER_OF_STRINGS][STRING_LENGTH];

void* addToQueue(void *arg) {
    int i = 0;
    printf("Enter path: \n");
    scanf("%s", filePath);
    FILE *plist = NULL;
    DIR *directory;
    struct dirent *file;
    directory = opendir(filePath);
    while(file = readdir(directory)) {

        if (!strcmp(file->d_name, "."))
            continue;
        if (!strcmp(file->d_name, ".."))
            continue;

        char *compr = strrchr(file->d_name, '.');
        if (!strcmp(compr+1, "compr"))
            continue;


        strcpy(fileName[i], file->d_name);
        i++;


    }



    job1->directory = fileName[0];
    job1->content = data[0];
    job2->directory = fileName[1];
    job2->content = data[1];
    queue_insert(queue, job1);
    queue_insert(queue, job2);
    printf("%s \n", job1->directory);
    printf("%s \n", job2->directory);
    printf("%s \n", job1->content);
    printf("%s \n", job2->content);
}

int main() {
    int status = 0;
    pthread_t thread;
    queue = queue_create();
    job1 = (Job *) malloc(sizeof(Job));
    job2 = (Job *) malloc(sizeof(Job));
    status = pthread_create(&thread, NULL, addToQueue, NULL);
    status = pthread_join(thread, NULL);
    return 0;
}
