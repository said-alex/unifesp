#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_TAM 1000
#define WRITE 1
#define READ 0

void filtroQtdPipesExecutar (char *str, char **margs, char **margs2, char **margs3);
void criarMatrizArgumentos (char *str, int numpipes, char **margs, char **margs2, char **margs3);
int executarComandos (int numpipes, char **margs, char **margs2, char **margs3);

int main () {
    char *margs[MAX_TAM] = {0}, *margs2[MAX_TAM] = {0}, *margs3[MAX_TAM] = {0}; 
    char str[MAX_TAM];

    while (1) {
        printf("#~ ");
        fgets(str, MAX_TAM, stdin);

        if (str == NULL)
            continue;

        //**FUNÇÃO ANALISA A STRING DE COMANDOS INSERIDA E EXECUTA DE ACORDO COM A QUANTIDADE DE PIPES**//
        filtroQtdPipesExecutar(str, margs, margs2, margs3);

        //**FAZ A LIMPEZA DOS FLUXOS DE E/S, LIMPA LOCAL DE MEMÓRIA DAS VARIÁVEIS**//
        fflush(NULL);
        memset(str, '\0', sizeof(str));
        memset(margs, '\0', sizeof(margs));
        memset(margs2, '\0', sizeof(margs2));
        memset(margs3, '\0', sizeof(margs3));
    }
    return 0;
}

void filtroQtdPipesExecutar (char *str, char **margs, char **margs2, char **margs3) {
    int numpipes = 0;
        
        //**CONTA QUANTIDADE DE PIPES NA STRING**//
        for (int i = 0; i < strlen(str); i++) {
            if ((int)str[i] == 124)
                numpipes++;
        }

        //**DE ACORDO COM A QUANTIDADE DE PIPES CHAMA A DEVIDA FUNCAO (MAX 2 PIPES)**/
        if (numpipes == 0) {
            //**CASO NAO TENHA PIPES APENAS CRIA UM MATRIZ COM OS ARGUMENTOS E EXECUTA**/
            criarMatrizArgumentos(str, numpipes, margs, NULL, NULL);
            executarComandos(numpipes, margs, NULL, NULL);
        }
        else if (numpipes == 1) {
            //**APENAS UM PIPE CRIA DUAS MATRIZES DE ARGUMENTOS PARA SEREM EXECUTADAS POR PROCESSOS PAI/FILHO**/
            criarMatrizArgumentos(str, numpipes, margs, margs2, NULL);
            executarComandos(numpipes, margs, margs2, NULL);
        }
        else if (numpipes == 2) {
            //**COM DOIS PIPES CRIA TRES MATRIZES DE ARGUMENTOS PARA SEREM EXECUTADAS POR PROCESSOS PAI/FILHO/FILHO**/
            criarMatrizArgumentos(str, numpipes, margs, margs2, margs3);
            executarComandos(numpipes, margs, margs2, margs3);
        }
        else {
            fprintf(stderr, "numero maximo de pipes = 2\n");
        }
}

void criarMatrizArgumentos (char *str, int numpipes, char **margs, char **margs2, char **margs3) {
    char *straux, *strauxdois;
    char limitador[] = " ";
    int numspaces = 0, sizestr = 0;

    //**CHECA A QUANTIDADE DE ESPACOS NA STRING E FAZ A MATRIZ BASEADO NO NUMERO DE ESPACOS**/
    if (numpipes == 0) {
        int i;
        for (i = 0; i < strlen(str); i++) {
            if ((int)str[i] == 32)
                numspaces++;
        }

        //**SEPARA A STRING POR ESPACOS**/
        for (i = 0; i < numspaces; i++) {  
            margs[i] = strsep(&str, " ");
        }
            margs[i] = strsep(&str, "\n");
    }
    else if (numpipes == 1) {
        straux = strsep(&str, "|");

        //**CRIA UMA MATRIZ DE ARGUMENTOS PARA O COMANDO ANTES DO PRIMEIRO PIPE**//
        int i;
        for (i = 0; i < strlen(straux); i++) {
            if ((int)straux[i] == 32)
                numspaces++;
        }

        for (i = 0; i <= numspaces; i++) {
            if (strlen(straux) < 1)
                break;
            margs[i] = strsep(&straux, limitador);
        }
        margs[i] = NULL;

        //**CRIA MATRIZ DE ARGUMENTOS PARA OS COMANDOS APOS O PRIMEIRO PIPE**//
        numspaces = 0;
        for (i = 0; i < strlen(str); i++) {
            if ((int)str[i] == 32)
                numspaces++;
        }

        i = 0;
        while ((int)str[i] == 32) {
            for (int j = 0; j < strlen(str); j++) {
                sizestr = strlen(str);
                if (j == (sizestr - 2)) {
                    str[j] = 0;
                    numspaces--;
                    break;
                }
                str[j] = str[j+1];
            }
        }
        
        for (i = 0; i <= numspaces; i++) { 
            if (strlen(str) < 1)
                break; 
            margs2[i] = strsep(&str, limitador);
        }
        margs2[i] = NULL;

    } 
    else if (numpipes == 2) {
        straux = strsep(&str, "|");

        //**CRIA MATRIZ DE ARGUMENTOS PARA OS COMANDOS ANTES DO PRIMEIRO PIPE**//
        int i;
        for (i = 0; i < strlen(straux); i++) {
            if ((int)straux[i] == 32)
                numspaces++;
        }

        for (i = 0; i <= numspaces; i++) {
            if (strlen(straux) < 1)
                break;
            margs[i] = strsep(&straux, limitador);
        }
        margs[i] = NULL;
        /**FIM DOS COMANDO DO INICIO**/



        /**CRIA MATRIZ DE ARGUMENTOS PARA OS COMANDO DEPOIS DO PRIMEIRO PIPE**/
        strauxdois = strsep(&str, "|");

        numspaces = 0;
        for (i = 0; i < strlen(strauxdois); i++) {
            if ((int)strauxdois[i] == 32)
                numspaces++;
        }

        i = 0;
        while ((int)strauxdois[i] == 32) {

            for (int j = 0; j < strlen(strauxdois); j++) {
                sizestr = strlen(strauxdois);
                if (j == (sizestr - 1)) {
                    strauxdois[j] = 0;
                    numspaces--;
                    break;
                }
                strauxdois[j] = strauxdois[j+1];
            }
        }
        
        for (i = 0; i <= numspaces; i++) { 
            if (strlen(strauxdois) < 1)
                break; 
            margs2[i] = strsep(&strauxdois, limitador);
        }
        margs2[i] = NULL;
        /**FIM DOS COMANDOS DO MEIO**/

        /**CRIA MATRIZ DE ARGUMENTOS PARA OS COMANDOS DEPOIS DO SEGUNDO PIPE**/
        numspaces = 0;
        for (i = 0; i < strlen(str); i++) {
            if ((int)str[i] == 32)
                numspaces++;
        }

        i = 0;
        while ((int)str[i] == 32) {
            for (int j = 0; j < strlen(str); j++) {
                sizestr = strlen(str);
                if (j == (sizestr - 2)) {
                    str[j] = 0;
                    numspaces--;
                    break;
                }
                str[j] = str[j+1];
            }
        }
        
        for (i = 0; i <= numspaces; i++) { 
            if (strlen(str) < 1)
                break; 
            margs3[i] = strsep(&str, limitador);
        }
        margs3[i] = NULL;
        /**FIM DOS COMANDO DA PARTE FINAL**/
    }

}

int executarComandos (int numpipes, char **margs, char **margs2, char **margs3) {

    //**SEM PIPES INSTANCIA UM PROCESSO FILHO E PASSA A MATRIZ 1 PARA A FUNCAO EXECVP QUE EXECUTA OS COMANDOS**/
    if (numpipes == 0) {
        pid_t pid;

        pid = fork();  

        if (pid == 0) { 
            execvp(margs[0], margs);
        } 
        else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } 
        else {
            perror("fork{}");
            return -1;
        }
    }

    //**APENAS UM PIPE INSTANCIA UM PROCESSO FILHO E PASSA A MATRIZ 1 PARA A FUNCAO EXECVP QUE EXECUTA OS COMANDOS**/
    //**APOS RODAR OS PRIMEIROS COMANDOS INSTANCIA UM NOVO PROCESSO FILHO E PASSA A SAIDA DO COMANDO ANTERIOS JUNTO COM OS NOVOS COMANDOS**/
    else if (numpipes == 1) {
        int fd[2];

        pid_t pid, pid2;

        if (pipe(fd) < 0) { 
            perror("pipe()");
            return -1;
        }

        pid = fork();

        //**fd[READ] -> DESCRITOR DE LEITURA**//
        //**fd[WRITE] -> DESCRITOR DE ESCRITA**//
        if (pid == 0) {
            dup2(fd[WRITE], STDOUT_FILENO);
            close(fd[READ]);
            close(fd[WRITE]);
            execvp(margs[0], margs);
        } else {
            int status;
            pid2 = fork();

            if (pid2 == 0) {
                dup2(fd[READ], STDIN_FILENO);
                close(fd[WRITE]);
                close(fd[READ]);
                execvp(margs2[0], margs2);
            }
            else {
                close(fd[READ]);
                close(fd[WRITE]);
                waitpid(pid2, &status, 0);
            }

            return 0;
        }
    }

    //**PARA 2 PIPES OU MAIS O PROCESSO E SIMILAR, INSTACIA PROCESSO FILHO PASSA OS COMANDOS PARA A EXECVP PEGA O RETORNO E PASSA PARA O PROXIMO PROCESSO**/
    //**E ASSIM POR DIANTE ATE QUE CHEGUE AO ULTIMO PROCESSO, E ASSIM A SAIDA E DADA NA SAIDA PADRAO**/
    else if (numpipes == 2) {
        int fd[2], ch_fd[2];
        pid_t pid, pid2, pid3;

        //**RETORNO DA FUNÇÃO PIPE < 0 REPRESENTA ERRO**//
        if (pipe(fd) < 0) {
            perror("pipe()");
            return -1;
        }

        if (pipe(ch_fd) < 0) { 
            perror("pipe(ch_fd)");
            return -1;
        }

        pid = fork();
        if (pid == 0) {
            close(fd[READ]);
            dup2(fd[WRITE], STDOUT_FILENO);
            close(fd[WRITE]);
            execvp(margs[0], margs);
        } else {
            int status;
            close(fd[1]);

            pid2 = fork();

            if (pid2 == 0) { 
                dup2(fd[READ], STDIN_FILENO);
                close(ch_fd[READ]);
                close(fd[READ]);
                dup2(ch_fd[WRITE], STDOUT_FILENO);
                close(ch_fd[WRITE]);
                execvp(margs2[0], margs2);
            } else {
                close(fd[READ]);
                close(ch_fd[WRITE]);
                pid3 = fork();
                if (pid3 == 0) {
                    dup2(ch_fd[READ], STDIN_FILENO);
                    close(ch_fd[WRITE]);
                    execvp(margs3[0], margs3);
                }
            }
            close(ch_fd[READ]);

            waitpid(pid, &status, 0);
            waitpid(pid2, &status, 0);
            waitpid(pid3, &status, 0);
            return 0;
        }
    }

    else {
        fprintf(stderr, "erro na quantidade de pipes\n");
    }
    return 0;   
}