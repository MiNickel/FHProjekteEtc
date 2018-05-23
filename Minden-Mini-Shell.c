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
    char *buf;
    buf=(char *)malloc(10*sizeof(char));
    buf=getlogin();
    printf("\n %s \n",buf);
}

void getDirectory() {
    char puffer[500];

   if (getcwd(puffer, sizeof(puffer)) != NULL)
       fprintf(stdout, "Aktuelles Verzeichnis %s\n", puffer);
   else
       fprintf(stderr, "Fehler");
   return 0;
}

int main() {
    getUserName();
    getDirectory();


}
