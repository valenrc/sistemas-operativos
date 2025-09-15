#include <stdio.h>
#include <unistd.h>   // fork(), getpid()
#include <sys/types.h>
#include <sys/wait.h> // wait()

int main(void){
    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        return 1;
    }

    else if(pid == 0){
        printf("Soy el hijo con PID: %d y el PID de mi padre es: %d", getpid(), getppid());

        // -- codigo del hijo --
    } else {
        printf("Soy el padre. PID del hijo: %d", pid);
        wait(NULL); // esperar a que el hijo termine

        // -- codigo del padre
    }

    return 0;
}