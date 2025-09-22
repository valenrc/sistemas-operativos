#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

int client_socket;

void subrutina_server(){
  char term[] = "exit";
  char msg[100];

  while(strcmp(msg, term) != 0){
    if(client_socket == -1){
      perror("ERROR ACCEPT");
      exit(EXIT_FAILURE);
    }

    int client_pid;
    if(read(client_socket, &client_pid, sizeof(client_pid)) == -1){
      perror("ERROR READ 1");
      exit(EXIT_FAILURE);
    }
    if(read(client_socket, &msg, sizeof(msg)) == -1){
      perror("ERROR READ 2");
      exit(EXIT_FAILURE);
    }

    printf("Cliente con pid: %d - Mensaje: '%s'\n", client_pid, msg);
  }
  printf("El cliente terminó la conexión\n");
  close(client_socket);
  exit(0);
}

int main(void){
  int server_socket;
  struct sockaddr_un server_addr;
  struct sockaddr_un client_addr;
  int slen = sizeof(server_addr);
  int clen = sizeof(client_addr);

  // configurar la dirección del server
  server_addr.sun_family = AF_UNIX;
  strcpy(server_addr.sun_path, "unix_socket");
  unlink(server_addr.sun_path);

  // crear el socket, bind y listen
  server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
  bind(server_socket, (struct sockaddr *) &server_addr, slen);
  listen(server_socket, 5);

  char term[] = "exit";
  char msg[100];

  printf("esperando conexión...\n");
  // se bloquea esperando una conexión
  while(1){
    client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &clen);
    pid_t pid = fork();

    if(pid == 0){
      subrutina_server();
    }
  }
  exit(0);
}