// Implementar el inciso b del ejercicio 11 usando pipes en C. Determinar si el comportamiento del intercambio de mensajes obtenido es igual al especificado por las funciones bsend y breceive

#include <stdio.h>
#include <unistd.h>   // fork(), getpid()
#include <sys/types.h>
#include <sys/wait.h> // wait()
#include <stdlib.h>
#include <signal.h>

// Constantes 0 / 1 para READ / WRITE
enum { READ, WRITE };

// file descriptors para los tres pipes
int ph1[2];
int h1h2[2];
int h2p[2];

void handler_h1(){
  // cerrar los pipes que no usa
  close(ph1[WRITE]);
  close(h1h2[READ]);
  close(h2p[READ]); close(h2p[WRITE]);

  int num;
  while(read(ph1[READ], &num, sizeof(int))){ // espera hasta leer el numero que le pasa P
    num++;
    printf("H1 envía a H2 el valor %d\n", num);
    write(h1h2[WRITE], &num, sizeof(int)); // le pasa el resultado a H2
  }

  // cerrar los pipes que estaba usando
  close(ph1[READ]);
  close(h1h2[WRITE]);
  exit(0);
}

void handler_h2(){
  close(h1h2[WRITE]);
  close(h2p[READ]);
  close(ph1[READ]); close(ph1[WRITE]);

  int num;
  while(read(h1h2[READ], &num, sizeof(int))){ // espera hasta leer el numero que le pasa H1
    num++;
    printf("H2 envía a Padre el valor %d\n", num);
    write(h2p[WRITE], &num, sizeof(int)); // le pasa el resultado a P
  }

  // cerrar los pipes que estaba usando
  close(h1h2[READ]);
  close(h2p[WRITE]);
  exit(0);
}

int main(void){

  // crear los pipes
  pipe(ph1);
  pipe(h1h2);
  pipe(h2p);

  pid_t pid1 = fork();

  if(pid1 == 0) handler_h1();

  else{
    // crea otro hijo
    pid_t pid2 = fork();
    if(pid2 == 0) handler_h2();
    else{
      // codigo del padre
      // cerrar los pipes que no usa
      close(ph1[READ]);
      close(h1h2[READ]); close(h1h2[WRITE]);
      close(h2p[WRITE]);

      // enviar mensaje a H1
      int num = 0;
      while(num <= 50){
        printf("Padre envía a H1 el valor %d\n", num);
        write(ph1[WRITE], &num, sizeof(int));  // escribe en el pipe el numero correspondiente
        read(h2p[READ], &num, sizeof(int));  // espera a leer el resultado de H2
        num++;
      }

      // cerrar los pipes - manda EOF a los hijos
      close(ph1[WRITE]);
      close(h2p[READ]);

      waitpid(pid1, NULL, 0);
      waitpid(pid2, NULL, 0);
    }
  }
  return 0;
}