#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <libgen.h> 
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define TAM 1000 

void  parseo(char *line, char **argv);

int main(void) {

    char  cad[TAM];             
    char  *argv[TAM]; 
    char  *gdir;
    char  *dir;
    char  *to;
    char buf[TAM];
    pid_t pid;
    int status;

    while (1) {                   

        printf("user@PC: ");    
        fgets(cad, 1000, stdin);

        // Si encontramos un salto de linea (se pulsa enter)
        if (cad[strlen(cad) - 1] == '\n')                                                           
            cad[strlen(cad) - 1] = '\0';    // lo marcamos como final de sentencia            

        parseo(cad, argv);


        // Exit para salir del shell
        if (!strcmp(argv[0], "exit")) exit(0);  

        if (!strcmp(argv[0], "cd")){

            gdir = getcwd(buf, sizeof(buf));
            dir = strcat(gdir, "/");
            to = strcat(dir, argv[1]);

            chdir(to);
	    continue;
            //printf("Acceso a la carpeta realizado\n");

        }            

        pid = fork();

        if (pid == 0) {   

            if (execvp(*argv, argv) < 0) {
                printf("%s: no se encontró la orden \n", argv[0]);
                exit(1);
            }
        }else {  

            waitpid(pid,&status,0);
        }   

    }
    return 0;
}

void  parseo(char *line, char **argv){

    while (*line != '\0') {       
        while (*line == ' ' || *line == '\t' || *line == '\n')

            *line++ = '\0';     
            *argv++ = line; 

        while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n') 
            line++;             
    } 
    *argv = '\0';             // marca de final
}
