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

// Verifica se o token é um operador de fluxo de comando
int isFlowToken(const char* token) {
  return !(
    strcmp(token, FLOW_TOKENS[SEQ]) &&
    strcmp(token, FLOW_TOKENS[AND]) &&
    strcmp(token, FLOW_TOKENS[OR])  &&
    strcmp(token, FLOW_TOKENS[BG])  &&
    strcmp(token, FLOW_TOKENS[PP])
  );
}

// Inicializa o estado atual dos argumentos da struct de comandos
void initializeShellInputState(ShellInput* input, char** args) {
  input->flow = NULL;
  input->currentArgs = NULL;
  input->nextArgs = args;
}

// Atualiza o estado atual dos argumentos da struct de comandos
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

// Verifica se o token é o operador sequencial (;)
int isSequentialToken(const char* token) {
  return token && !strcmp(token, FLOW_TOKENS[SEQ]);
}

// Verifica se o token é o operador AND (&&)
int isAndToken(const char* token) {
  return token && !strcmp(token, FLOW_TOKENS[AND]);
}

// Verifica se o token é o operador OR (||)
int isOrToken(const char* token) {
  return token && !strcmp(token, FLOW_TOKENS[OR]);
}

// Verifica se o token é o operador de background (&)
int isBackgroundToken(const char* token) {
  return token && !strcmp(token, FLOW_TOKENS[BG]);
}

// Verifica se o token é o operador Pipe (|)
int isPipeToken(const char* token) {
  return token && !strcmp(token, FLOW_TOKENS[PP]);
}

// Obtém o status do processo filho
int getChildStatus(pid_t pid) {
  int status;

  waitpid(pid, &status, 0);

  return status;
}

// Configura o descritor de arquivo
void setupFileDescriptor(int* fileDescriptor, int file) {
  dup2(fileDescriptor[file], file);
  close(fileDescriptor[file]);
  close(fileDescriptor[file ? 0 : 1]);
}

// Lida com o processo filho executando o comando atual
void handleChildProcess(ShellInput* input, int* fileDescriptor) {
  if (isPipeToken(input->flow))
    setupFileDescriptor(fileDescriptor, STDOUT_FILENO);

  exit(execvp(input->currentArgs[0], input->currentArgs));
}

// Lida com o processo principal determinando o fluxo do comando
void handleMainProcess(pid_t pid, ShellInput* input, int* fileDescriptor) {
  if (isBackgroundToken(input->flow)) // Se o operador for '&', ignora o status do processo filho
    return;                           // e segue para o próximo.

  int status = getChildStatus(pid);

  if (isPipeToken(input->flow)) {                      // Se o operador for '|', configura o descritor de arquivos,
    setupFileDescriptor(fileDescriptor, STDIN_FILENO); // aguarda o processo filho e segue para o próximo.
    return;
  }

  if (isSequentialToken(input->flow)) // Se o operador for ';', aguarda o processo filho e segue para o próximo.
    return;

  if (status)                       // Se o status do ultimo processo não for bem sucedido
    while (isAndToken(input->flow)) // enquanto o operador for '&&',
      updateShellInputState(input); // pula o comando atual.
  else                              // Se não,
    while (isOrToken(input->flow))  // enquanto o operador for '||',
      updateShellInputState(input); // pula o comando atual.
}

// Processa o comando de entrada
int processShellInput(char** args) {
  ShellInput input;
  int fileDescriptor[2];
  pid_t pid;

  initializeShellInputState(&input, args);

  while (input.nextArgs) {
    updateShellInputState(&input);

    if (isPipeToken(input.flow) && (pipe(fileDescriptor) < 0)) {
      puts("pipe() falhou inesperadamente.");
      return EXIT_FAILURE;
    }

    pid = fork();

    if (pid == 0)
      handleChildProcess(&input, fileDescriptor);
    else if (pid > 0)
      handleMainProcess(pid, &input, fileDescriptor);
    else {
      puts("fork() falhou inesperadamente.");
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
