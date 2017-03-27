/* Lab01
* FSD - Client TCP
* Programa para enviar uma operacao numerica para o servidor e imprimir o resultado recebido.
*
* Artur Bersan de Faria 14/0016813
* Iasmin Santos Mendes 14/0041940
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

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

  printf("\nObservacoes para correto funcionamento:\n");
  printf("- String de operacao A + B: com espaço antes e depois do sinal de operacao\n");
  printf("- Para a multiplicacao utilizar \\* ao inves de *.\n\n");

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
    printf("Enviando: %s\n", argv[i]);
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
