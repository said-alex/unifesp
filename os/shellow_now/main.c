#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TOTAL_CMD_FLOW 5

typedef struct ShellInput {
  char*  flow;
  char** currentArgs;
  char** nextArgs;
} ShellInput;

enum CMD_FLOWS { SEQ, AND, OR, BG, PP };

const char* FLOW_TOKENS[TOTAL_CMD_FLOW] = { ";", "&&", "||", "&", "|" };

int isFlowToken(const char* token) {
  return !(
    strcmp(token, FLOW_TOKENS[SEQ]) &&
    strcmp(token, FLOW_TOKENS[AND]) &&
    strcmp(token, FLOW_TOKENS[OR])  &&
    strcmp(token, FLOW_TOKENS[BG])  &&
    strcmp(token, FLOW_TOKENS[PP])
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

int isSequentialToken(const char* token) {
  return token && !strcmp(token, FLOW_TOKENS[SEQ]);
}

int isAndToken(const char* token) {
  return token && !strcmp(token, FLOW_TOKENS[AND]);
}

int isOrToken(const char* token) {
  return token && !strcmp(token, FLOW_TOKENS[OR]);
}

int isBackgroundToken(const char* token) {
  return token && !strcmp(token, FLOW_TOKENS[BG]);
}

int isPipeToken(const char* token) {
  return token && !strcmp(token, FLOW_TOKENS[PP]);
}

void exitWithMsg(char* msg, int exit_status) { // Não vamos precisar disso quando implementarmos o interpretador
  puts(msg);
  exit(exit_status);
}

int waitForChildStatus(pid_t pid) {
  int status;

  waitpid(pid, &status, 0);

  return status;
}

void setupFileDescriptor(int* fileDescriptor, int file) {
  dup2(fileDescriptor[file], file);
  close(fileDescriptor[file]);
  close(fileDescriptor[file ? 0 : 1]);
}

void handleChildProcess(ShellInput* input, int* fileDescriptor) {
  if (isPipeToken(input->flow)) setupFileDescriptor(fileDescriptor, STDOUT_FILENO);

  exit(execvp(input->currentArgs[0], input->currentArgs));
}

void handleMainProcess(pid_t pid, ShellInput* input, int* fileDescriptor) {
  if (isBackgroundToken(input->flow)) return;

  if (isPipeToken(input->flow)) {
    setupFileDescriptor(fileDescriptor, STDIN_FILENO);
    return;
  }

  int status = waitForChildStatus(pid);

  if (isSequentialToken(input->flow)) return;

  if (status) while (isAndToken(input->flow)) updateShellInputState(input);
  else while (isOrToken(input->flow)) updateShellInputState(input);
}

int main(int argsCount, char** args) {
  if (argsCount <= 1)
    exitWithMsg("Nenhum comando foi passado.", EXIT_FAILURE);

  ShellInput input;
  initializeShellInputState(&input, ++args);

  int fileDescriptor[2];

  while (input.nextArgs) {
    updateShellInputState(&input);

    if (isPipeToken(input.flow) && (pipe(fileDescriptor) < 0))
      exitWithMsg("pipe() falhou inesperadamente.", EXIT_FAILURE);

    pid_t pid = fork();

    if (pid == 0) handleChildProcess(&input, fileDescriptor);
    else if (pid > 0) handleMainProcess(pid, &input, fileDescriptor);
    else exitWithMsg("fork() falhou inesperadamente.", EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
