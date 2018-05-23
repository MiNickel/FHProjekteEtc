#ifdef __unix__
    #include <unistd.h>
#elif __WIN32__ || _MS_DOS_
    #include <dir.h>
#else
    #include <direct.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

void getUserName() {
   char *p=getenv("USER");
   printf("Aktueller User: %s\n",p);
}

void getDirectory() {
    char puffer[500];

   if (getcwd(puffer, sizeof(puffer)) != NULL)
       fprintf(stdout, "Aktuelles Verzeichnis: %s\n", puffer);
   else
       fprintf(stderr, "Fehler");
   
}

int main() {

    getUserName();
    getDirectory();
    char c;
    while((c=getc(stdin)) != EOF)
      putc(c,stdout);
    
    return 0;
   
}
