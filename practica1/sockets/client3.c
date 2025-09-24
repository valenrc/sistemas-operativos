#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <signal.h>

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

  pid_t pid_c = fork();

  if(pid_c == 0){
    // este se va a bloquear hasta que el server le mande un mensaje
    fflush(stdout); // para ver el print anterior
    msg_paquete msgp;
    while(1){
      if(read(server_socket, &msgp, sizeof(msgp)) == -1){
        printf("QUE CARAJOS!!!\n");
        perror("ERROR READ");
      }

      printf("[%d]: %s\n", msgp.pid, msgp.msg);
      fflush(stdout);
    }
  }else{
    // el padre se encarga de manejar la escritura al server
    while(1){
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

      if(strcmp(msg, exit_msg) == 0){
        kill(pid_c, SIGTERM); // matar al hijo
        break;
      }
    }
  }

  close(server_socket);
  exit(0);
}