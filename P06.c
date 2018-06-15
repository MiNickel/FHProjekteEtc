#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>

#define NUMBER_OF_STRINGS 3
#define STRING_LENGTH 50

typedef struct {
    char *content;
    char *directory;
} Job;

Job *job1;
Job *job2;

Queue queue;

char filePath[] = "";
char data[NUMBER_OF_STRINGS][STRING_LENGTH+1];
char fileName[NUMBER_OF_STRINGS][STRING_LENGTH+1];

void* addToQueue(void *arg) {
    int i = 0, x = 0;
    printf("Enter path: \n");
    scanf("%s", filePath);

    FILE *fp;
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

   /*     fp = fopen(fileName[i], "r");

        while(fgets(data[x], STRING_LENGTH, fp)) {
        /* get rid of ending \n from fgets
        data[x][strlen(data[x]) - 1] = '\0';
        x++;
    }  */

        /*   fp = fopen(file->d_name, "r");
           if (fp != NULL) {
               while(!feof(fp)) {
                   fscanf(fp, "%s", &data[wordCount]);
                   wordCount++;
               }
               puts("");
               for (x = 0; x < (wordCount -1); x++) {
                   puts(data[x]);
               }
               puts("");

           } else {
               puts("Kann nicht gelesen werden");
           }
           wordCount = 0; */
        i++;


    }



    job1->directory = fileName[0];
    job1->content = data[0];
    job2->directory = fileName[1];
    job2->content = data[0];
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
