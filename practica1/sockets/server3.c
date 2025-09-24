#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/un.h>
#include <string.h>

#define MAX_CLIENTS 5
char term[] = "exit";

typedef struct msgpck{
  char msg[100];
  pid_t pid;
} msg_paquete;

int main(void){
  int server_socket;
  struct sockaddr_un server_addr;
  struct sockaddr_un client_addr;
  int slen = sizeof(server_addr);
  int clen = sizeof(client_addr);
  
  int client_sockets[MAX_CLIENTS] = {0};
  int client_socket;
  fd_set read_fds;
  int max_fd;
  msg_paquete msgp;

  // configurar la dirección del server
  server_addr.sun_family = AF_UNIX;
  strcpy(server_addr.sun_path, "unix_socket");
  unlink(server_addr.sun_path);

  // crear el socket, bind y listen
  server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
  bind(server_socket, (struct sockaddr *) &server_addr, slen);
  listen(server_socket, MAX_CLIENTS);

  printf("esperando conexión...\n");
  while(1){
    FD_ZERO(&read_fds);
    FD_SET(server_socket, &read_fds);
    max_fd = server_socket;

    // añadir los clientes conectados al fd_set
    for(int i=0; i<MAX_CLIENTS; i++){
      int fd = client_sockets[i];
      if(fd > 0){
        FD_SET(fd, &read_fds);
      }
      if(fd > max_fd) max_fd = fd;
    }

    // esperar por conexiones
    if(select(max_fd +1, &read_fds, 0, 0, 0) < 0){
      perror("SELECT ERROR");
      exit(1);
    }

    // esto es cuando hay actividad en el socket del server
    if(FD_ISSET(server_socket, &read_fds)){
      client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &clen);
      if(client_socket < 0){
        perror("ERROR ACCEPT");
        exit(1);
      }

      printf("Nueva conexión fd: %d\n", client_socket);

      // buscar lugar dentro del array para meter el nuevo fd
      for(int i=0; i<MAX_CLIENTS; i++){
        if(client_sockets[i] ==0){
          client_sockets[i] = client_socket;
          break;
        }
      }
    }

    // leer mensaje de cliente
    for(int i=0; i<MAX_CLIENTS; i++){
      int fd = client_sockets[i];

      if(FD_ISSET(fd, &read_fds)){
        if(read(fd, &msgp, sizeof(msgp)) < 0){
          perror("ERROR READ");
          exit(1);
        }

        if(strcmp(msgp.msg, term) == 0){
          printf("[%d] cerró la conexión\n", msgp.pid);
          close(fd);  // cerrar el fd del cliente
          client_sockets[i] = 0;
        }

        printf("[%d]: %s\n", msgp.pid, msgp.msg);


        // broadcast a los demas clientes
        for(int j=0; j<MAX_CLIENTS; j++){
          if(j == i) continue;
          int dest_fd = client_sockets[j];
          if(dest_fd > 0){
            if(write(dest_fd, &msgp, sizeof(msgp)) <0){
              perror("WRITE ERROR");
            }
          }
        }
        
      }
    }
  }
  close(server_socket);
  exit(0);
}