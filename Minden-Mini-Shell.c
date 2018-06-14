#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define TOK_DELIM " \t\r\n\a"
#define NumberOfStrings 101


int cd(char **args);
int own_exit(char **args);
int set(char **args);
int echo(char **args);
int print(char **args);


char *builtin_str[] = {
  "cd",
  "set",
  "exit",
  "echo",
  "print"
};
char *envVar[NumberOfStrings] = { NULL }; 

int (*builtin_func[]) (char **) = {
  &cd,
  &set,
  &own_exit,
  &echo,
  &print
};

int num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}


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

char **split_line(char *line) {
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;
	
	if(!tokens) {
	fprintf(stderr, "Allocation error\n");
	exit(EXIT_FAILURE);
	}
	
	token = strtok(line, TOK_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;
		
		if (position >= bufsize) {
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

char *read_line() {
	char *line = NULL;
	ssize_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	return line;
	
}
int launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}
int cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int set(char **args)
{
  
  for (int i = 0; i < NumberOfStrings; i++) {
	if (envVar[i] == NULL) {
	   envVar[i] = args[1];
	   envVar[i+1] = args[2];
	   break;
	}
  break;
		
	
  }
for(int i = 0; i < NumberOfStrings;i++) {
	printf("%s", envVar[i]);
  }
  return 1;
}

int echo(char **args)
{
  for (int i = 0; i < NumberOfStrings; i++) {
	if(envVar[i] != NULL) {
		printf("%s", envVar[i]);
		if(envVar[i] == args[1]) {
			printf("%s", envVar[i+1]);
		}
	}
  }
  return 1;
}
int print(char **args)
{
  for(int i = 0; i < NumberOfStrings;i++) {
	printf("%s", builtin_str[i]);
  }
}

int own_exit(char **args)
{
  return 0;
}

int execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return launch(args);
}


void loop()
{
  char *line;
  char **args;
  int status;

  do {
    getUserName();
    getDirectory();
    printf("> ");
    line = read_line();
    args = split_line(line);
    status = execute(args);

    free(line);
    free(args);
  } while (status);
}


int main(int argc, char **argv) {


    
    loop();

    
    return EXIT_SUCCESS;
   
}
