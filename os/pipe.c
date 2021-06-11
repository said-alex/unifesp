#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define STR_LEN 256
#define PROC_NAME(pid) (pid == 0 ? "Filho" : "Pai")
#define WRITE 1
#define READ 0

void close_unused_fd(int* write_fd, int* read_fd) {
  close(write_fd[1]);
  close(read_fd[0]);
}

void read_fd(int* fd, int pid) {
  char msg[STR_LEN];

  bzero(msg, STR_LEN);

  if (read(fd[0], msg, STR_LEN) > 0)
    printf("%s[%ld]=> Lendo: '%s'\n", PROC_NAME(pid), (long)getpid(), msg);
}

void write_fd(int* fd, char* msg, int pid) {
  printf("%s[%ld]=> Escrevendo...\n", PROC_NAME(pid), (long)getpid());

  write(fd[1], msg, strlen(msg));
}

void print_feedback(int pid) {
  printf("%s terminando em 5 segundos...\n", PROC_NAME(pid));
  sleep(5);
  printf("%s OK!\n", PROC_NAME(pid));
}

void wait_child_procs() {
  int status;

  waitpid(-1, &status, 0);
}

int main() {
  int fd[2];

  if (pipe(fd) < 0) {
    perror("pipe(fd)");
    return -1;
  }

  pid_t pid = fork();

  if (pid == 0) { // processo filho
    dup2(fd[WRITE], STDOUT_FILENO);
    close(fd[READ]);
    close(fd[WRITE]);
    char* margs[] = { "ls", "-la", NULL };
    execvp(margs[0], margs);
  } else if (pid > 0) { // processo pai
    dup2(fd[READ], STDIN_FILENO);
    close(fd[WRITE]);
    close(fd[READ]);
    int status;
    waitpid(-1, &status, 0);
    char* margs2[] = { "grep", "pipe", NULL };
    execvp(margs2[0], margs2);
  } else { // erro
    perror("fork()");

    return -1;
  }

  return 0;
}
