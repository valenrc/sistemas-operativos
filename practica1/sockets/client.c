#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(void){
  int server_socket;

  struct sockaddr_un server_addr;               // configurar la dirección del servidor. tiene que ser la misma que está en server.c
  server_addr.sun_family = AF_UNIX;
  strcpy(server_addr.sun_path, "unix_socket");

  printf("Conectando al servidor...\n");
  server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
  connect(server_socket, (struct sockaddr *) &server_socket, sizeof(server_socket));    // devuelve 0 si la conexión se realiza

  char ch = 'A';
  char ch2;
  write(server_socket, &ch, 1);  // escribe ch al server
  read(server_socket, &ch2, 1);   // se queda leyendo del server


  printf("Recibí %c del server\n", ch2);

  close(server_socket);

  exit(0);
}