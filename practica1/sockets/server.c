#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(void){
  int server_socket;
  int client_socket;
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
  listen(server_socket, 2);

  printf("esperando conexión...\n");
  while(1){
    client_socket = accept(server_socket, (struct sockaddr *) &server_addr, slen);
  }

  exit(0);
}