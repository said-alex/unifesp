#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TOTAL_CMD_FLOW 4

typedef struct ShellInput {
  char*  flow;
  char** currentArgs;
  char** nextArgs;
} ShellInput;

enum CMD_FLOWS { SEQ, AND, OR, BG };

const char* FLOW_TOKENS[TOTAL_CMD_FLOW] = { ";", "&&", "||", "&" };

void exitWithMsg(char* msg, int exit_status) {
  puts(msg);
  exit(exit_status);
}

int isFlowToken(char* token) {
  return !(
    strcmp(token, FLOW_TOKENS[SEQ]) &&
    strcmp(token, FLOW_TOKENS[AND]) &&
    strcmp(token, FLOW_TOKENS[OR])  &&
    strcmp(token, FLOW_TOKENS[BG])
  );
}

void initializeShellInputState(ShellInput* input, char** args) {
  input->flow = NULL;
  input->currentArgs = NULL;
  input->nextArgs = args;
}

void updateShellInputState(ShellInput* input) {
  input->currentArgs = input->nextArgs;

  if (input->currentArgs) {
    char** argsAux = input->currentArgs;
    input->flow = NULL;
    input->nextArgs = NULL;

    while(argsAux && *argsAux) {
      if (isFlowToken(*argsAux)) {
        input->flow = *argsAux;
        *argsAux = NULL;
        input->nextArgs = argsAux + 1;
      } else {
        argsAux++;
      }
    }
  }
}

void handleChildProcess(pid_t pid, ShellInput* input) {
  if (input->flow && strcmp(input->flow, FLOW_TOKENS[BG])) return;

  int status;

  waitpid(pid, &status, 0);

  if (input->flow && strcmp(input->flow, FLOW_TOKENS[SEQ])) {
    if (status == 0)
      while (input->flow && !strcmp(input->flow, FLOW_TOKENS[OR]))
        updateShellInputState(input);
    else
      while (input->flow && !strcmp(input->flow, FLOW_TOKENS[AND]))
        updateShellInputState(input);
  }
}

int main(int argsCount, char** args) {
  if (argsCount <= 1)
    exitWithMsg("Nenhum comando foi passado.", EXIT_FAILURE);

  ShellInput input;

  initializeShellInputState(&input, ++args);

  while (input.nextArgs) {
    updateShellInputState(&input);

    pid_t pid = fork();

    if (pid == 0)
      exit(execvp(input.currentArgs[0], input.currentArgs));
    else if (pid > 0)
      handleChildProcess(pid, &input);
    else
      exitWithMsg("fork() falhou inesperadamente.", EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
