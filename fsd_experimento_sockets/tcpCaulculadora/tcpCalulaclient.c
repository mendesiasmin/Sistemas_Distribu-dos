#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*memset*/
#include <netinet/in.h> /*sockaddr_in*/
// #include <sys/socket.h>
#include <arpa/inet.h> /* inet_addr */
#include <unistd.h> /*close*/

#define MAX_MSG 100

int main (int argc, char *argv[]) {

  struct sockaddr_in endCli;
  struct sockaddr_in endServ;
  int sd, rc, n, i;
  char msg[MAX_MSG];

  //Valida os Argumentos
  if(argc < 6 ) {
    printf("uso: %s <ip_serv> <porta_serv> <operando_1> <operador> <operando_2>\n",argv[0]);
    exit(1);
  }

  /*Dados do Servidor*/
  endServ.sin_family = AF_INET;
  endServ.sin_addr.s_addr = inet_addr(argv[1]);
  endServ.sin_port = htons(atoi(argv[2]));

  /*Dados do Cliente*/
  endCli.sin_family = AF_INET;
  endCli.sin_addr.s_addr = htonl(INADDR_ANY);
  endCli.sin_port = htons(0);

  /*Criando o socket*/
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd < 0) {
    printf("nao foi possivel abrir o socket");
    exit(1);
  }

  /*Liga o socket ao IP*/
  rc = bind(sd, (struct sockaddr *) &endCli, sizeof(endCli));
  if(rc < 0) {
    printf("nao foi possivel fazer o bind na porta TCP");
    exit(1);
  }

  /*Conecta o Cliente ao Servidor*/
  rc = connect(sd, (struct sockaddr *) &endServ, sizeof(endServ));
  if(rc < 0) {
     printf("nao foi possivel conectar");
     exit(1);
  }

  /*Envia Dado*/
  for(i = 3; i < 6; i++) {
    rc = send(sd, argv[i], strlen(argv[i]) + 1, 0);
    printf("Enviando: %s...\n", argv[i]);
    if(rc<0) {
      printf("nao foi possivel enviar dados");
      close(sd);
      exit(1);
    }
  }

  /*Recebe Resultado*/
  memset(&msg, 0x0, sizeof(msg));
  n = recv(sd, &msg, sizeof(msg), 0);
  fprintf(stdout, "Resultado: %s\n", msg);

  close(sd);
  return 0;
}
