#include <stdio.h>
#include <unistd.h>   // fork(), getpid()
#include <sys/types.h>
#include <sys/wait.h> // wait()
#include <stdlib.h>
#include <signal.h>

int fd[2];

// ls -al | wc -l
int main(void){
  pipe(fd);

  pid_t pid = fork();

  if(pid == 0){ // HIJO: wc -l
    // redirigir fd[0] a stdin
    dup2(fd[0], STDIN_FILENO);  
    // cerrar los fd del pipe
    close(fd[1]);
    close(fd[0]);
    execlp("wc", "wc", "-l", NULL);
    // si vuelve aca es que hubo error
    exit(1);
  }else{
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);

    execlp("ls", "ls", "-al", NULL);
    // si vuelve aca es que hubo error
    exit(1);

  }
}

// hay un problema y es que el enunciado pide que sean dos subprocesos :/