#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

int main(void){
  int server_socket;
  int pid = getpid();

  struct sockaddr_un server_addr;               // configurar la dirección del servidor. tiene que ser la misma que está en server.c
  server_addr.sun_family = AF_UNIX;
  strcpy(server_addr.sun_path, "unix_socket");

  printf("Conectando al servidor...\n");
  server_socket = socket(AF_UNIX, SOCK_STREAM, 0);

  if(connect(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
    perror("ERROR CONEXION");
    exit(EXIT_FAILURE);
  }    // devuelve 0 si la conexión se realiza

  char msg[100];
  char exit_msg[] = "exit";

  while(1){
    //printf("Mensaje: ");
    scanf("%s", msg);
    if(write(server_socket, &pid, sizeof(pid)) == -1){
      perror("WRITE ERROR PID");
      exit(EXIT_FAILURE);
    }
    if(write(server_socket, &msg, sizeof(msg)) == -1){
      perror("WRITE ERROR MSG");
      exit(EXIT_FAILURE);
    }

    if(strcmp(msg, exit_msg) == 0) break;
  }

  close(server_socket);
  exit(0);
}