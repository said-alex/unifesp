#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_input.h"

#define INPUT_MSG "[juntos&shellowNow]=>$ "
#define BUFFER_SIZE 256

char** getInputArgs();
void freeInputArgs(char**);

int main () {
  char** inputArgs = NULL;
  int isToRun = 1;
  pid_t pid;

  while (isToRun) {
    printf(INPUT_MSG);
    inputArgs = getInputArgs();
    pid = fork();

    if (pid == 0) return processShellInput(inputArgs);
    else if (pid > 0) waitpid(pid, NULL, 0);
    else {
      puts("fork() falhou inesperadamente.");
      return EXIT_FAILURE;
    }

    freeInputArgs(inputArgs);
  }

  return 0;
}

char** getInputArgs() {
  int i = 0, j = 0, flag = 1;
  char** inputArgs = NULL;
  char buffer[BUFFER_SIZE];

  bzero(buffer, BUFFER_SIZE);

  while (flag && (buffer[j] = getchar())) {
    if (buffer[j] == ' ' || buffer[j] == '\n') {
      inputArgs = (char**)realloc(inputArgs, ((i + 1) * sizeof(char*)));
      inputArgs[i] = (char*)malloc((j + 1) * sizeof(char));

      if (buffer[j] == '\n') flag = 0;

      buffer[j] = '\0';

      strcpy(inputArgs[i], buffer);

      i++;
      j = -1;
    }

    j++;
  }

  inputArgs = (char**)realloc(inputArgs, ((i + 1) * sizeof(char*)));
  inputArgs[i] = NULL;

  return inputArgs;
}

void freeInputArgs(char** inputArgs) {
  int i;
  for (i = 0; inputArgs[i]; i++) free(inputArgs[i]);
  if (inputArgs) free(inputArgs);
}
