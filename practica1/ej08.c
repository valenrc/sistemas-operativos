#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char const *argv[]) {
    int dato = 0;
    pid_t pid = fork();

    // Si no hay error, pid vale 0 para el hijo
    // y el valor del process id del hijo para el padre
    if (pid == -1) {
        exit(EXIT_FAILURE); // Si es -1, hubo un error
    } else if (pid == 0) {
        for (int i = 0; i < 3; i++) {
            dato++;
            printf("Dato hijo: %d\n", dato);
        }
    } else {
        for (int i = 0; i < 3; i++) {
            printf("Dato padre: %d\n", dato);
        }
    }

    exit(EXIT_SUCCESS); // Cada uno finaliza su proceso
}

/*
La variable dato va a ser siempre 0 para el padre, mientras que para el hijo se va a incrementar tres veces. Lo que pasa es que el hijo va a tener valor de pid = 0 y va a ejecutar el for dentro de su rama el cual incrementa la variable antes de imprimirla. El padre ejecuta la ultima rama del if la cual no incrementa su variable.
*/