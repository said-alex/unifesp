#include<stdio.h>
#include<strings.h>
#include<string.h>
#include<stdlib.h>

//bibliotecas para o gerenciamento de processos e erros
#include<unistd.h>
#include<errno.h>

//bibliotecas para o waitpid
#include<sys/wait.h>
#include<sys/types.h>

#define STR_LEN 200
#define TOTAL_CMD_FLOW 5

const char* FLOW_TOKENS[TOTAL_CMD_FLOW] = { ";", "&&", "||", "&", "|" };

int ehOperador(const char* token) {
  return !(
    strcmp(token, ";")  &&
    strcmp(token, "&&") &&
    strcmp(token, "||") &&
    strcmp(token, "&")  &&
    strcmp(token, "|")
  );
}

int main(int argc, char **argv){
  pid_t pid;
	int fd[2];

	//Error handler para os pipes
	if(pipe(fd)<0){
		perror("pipe()");
		return -1;
	}

	// printf("argc: %d \n", argc);
	//verificando se houvue algum comando
    if(argc==1){ //argc: número de argumentos
        printf("Uso %s: <comando> <p_1><p_2>...<p_3>\n", argv[0]); //argv: matriz de arguumentos
        return 0;
    }

  char *estado;
  int i;

	if(argc > 2){
		for(i=0; i<argc; i++){
			if(!ehOperador(argv[i])){
        estado = argv[i];
			}
		}
	}

	if(!strcmp(estado, "|")) {
		char **cmd1 = NULL, **cmd2 = NULL;

		int status;

    argv++;
    cmd1 = argv;

    while(!ehOperador(*(++argv)));

    *argv = NULL;

    cmd2 = ++argv;

		pid = fork();

		if(pid == 0){
			dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
			close(fd[STDOUT_FILENO]);
			close(fd[STDOUT_FILENO ? 0 : 1]);
      exit(execvp(cmd1[0], cmd1));
		} else if (pid > 0) {
      dup2(fd[STDIN_FILENO], STDIN_FILENO);
			close(fd[STDIN_FILENO]);
			close(fd[STDIN_FILENO ? 0 : 1]);
      waitpid(-1, &status, 0);
			execvp(cmd2[0], cmd2);
    } else {
      return EXIT_FAILURE;
    }
	}
}
