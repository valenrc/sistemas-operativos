#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

typedef struct msgpck{
  char msg[100];
  pid_t pid;
} msg_paquete;

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
    if(fgets(msg, sizeof(msg), stdin) == NULL) break; // uso fgets en lugar de scanf
    // le saco el "\n" del final
    size_t len = strlen(msg);
    if(len > 0 && msg[len-1] == '\n') msg[len-1] = '\0';

    msg_paquete msgp = {.pid = pid};
    strcpy(msgp.msg, msg);

    if(write(server_socket, &msgp, sizeof(msgp)) == -1){
      perror("WRITE ERROR");
      exit(EXIT_FAILURE);
    }

    if(strcmp(msg, exit_msg) == 0) break;
  }

  close(server_socket);
  exit(0);
}