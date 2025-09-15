#include <stdio.h>
#include <unistd.h>   // fork(), getpid()
#include <sys/types.h>
#include <sys/wait.h> // wait()
#include <signal.h>

// NO FUNCIONA - CONSULTAR

void handler_hijo(int sig){
  printf("pong\n");
  kill(getppid(), SIGUSR2);
}

void handler_padre(int sig){
  // do nothing
}

int main(void){
  pid_t pid = fork();

  if(pid < 0){
    perror("fork");
    return 1;
  }

  else if(pid == 0){ // HIJO
    printf("Soy el hijo con PID: %d y el PID de mi padre es: %d\n", getpid(), getppid());

    signal(SIGUSR1, handler_hijo);

    while(1) pause(); // se queda esperando la señal

  } else { // PADRE
    printf("Soy el padre. PID del hijo: %d\n", pid);

    signal(SIGUSR2, handler_padre);

    int seguir = 1;
    while(seguir){
      for(int i=0; i<3; i++){
        printf("ping\n");
        kill(pid, SIGUSR1); // manda la señal al hijo para que imprima "pong"
        pause();            // esperar a que el hijo mande su señal de "acknowledge"
      }

      printf("seguir? : [1:yes/0:no]");
      scanf("%d", &seguir);
    }

    // matar al hijo
    kill(pid, SIGTERM);
    wait(NULL);
  }

  return 0;
}

