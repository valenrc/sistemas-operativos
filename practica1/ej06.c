#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// Implementar syscall que tenga el mismo funcionamiento que system(const char* arg) usando otras syscalls
// system ejecuta un comando de shell
// Otras syscalls
// exec(const char* arg) cambia el codigo de un proceso por otro
void system_falso(const char* arg){
  // creo un proceso hijo que cambie este codigo por exec
  // no puedo usar exec directamente xq obviamente desaparecería este programa
  pid_t pid = fork();

  if(pid == -1) printf("error");
  else
  if(pid == 0){
    // llamar a exec para cambiar el codigo por el codigo del comando a ejecutar
    // execl(path, filename, arg2, arg3, ...)
    execl("/bin/sh", "sh", "-c", arg, (char*)NULL); // sh -c comando (-c para que busque los argumentos en comando en lugar de standard input)
  }else{
    wait(NULL); // esperar a que se termine de ejecutar el comando
  }

  return;
}

int main(void){
  system_falso("ls -l");
  return 0;
}