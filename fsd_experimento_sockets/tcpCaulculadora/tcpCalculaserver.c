/* Lab01
* FSD - Server TCP
* Programa para receber uma operacao numerica para do cliente e enviar o resultado da operacao.
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
#define QLEN 5/*tamanho da fila de clientes*/

int calcula(char *_a, char *_b, char *op);

int main (int argc, char *argv[]) {

  struct sockaddr_in endCli;
  struct sockaddr_in endServ;
  int sd, novo_sd, alen;
  char msg[MAX_MSG];
  char res[MAX_MSG];
  char a[MAX_MSG], b[MAX_MSG], op[2];
  int n, rc, i;

  //Valida os Argumentos
  if(argc < 3) {
    printf("uso: %s <ip_serv> <porta_serv>\n",argv[0]);
    exit(1);
  }

  /*Limpa os dados do Servidor*/
  memset((char*) &endServ, 0, sizeof(endServ));

  /*Dados do Servidor*/
  endServ.sin_family = AF_INET;
  endServ.sin_addr.s_addr = inet_addr(argv[1]); /*IP*/
  endServ.sin_port = htons(atoi(argv[2])); /*Porta*/

  /*Criaçao do Socket*/
  sd = socket(AF_INET, SOCK_STREAM, 0); /*socket(Familia, tipo, protocolo)*/
  if (sd < 0) {
    fprintf(stderr, "Falha ao criar socket!\n");
    exit(1);
  }

  /*Conexão do Socket a porta IP*/
  if(bind(sd, (struct sockaddr *) &endServ, sizeof(endServ)) < 0) {
    fprintf(stderr,"Ligacao Falhou!\n");
    exit(1);
  }

  /*Ouve na porta*/
  if (listen(sd, QLEN) < 0) {
    fprintf(stderr,"Falhou ouvindo porta!\n");
    exit(1);
  }

  printf("Servidor ouvindo no IP %s, na porta %s ...\n\n", argv[1], argv[2]);

  /*Conexão com o cliente*/
  alen = sizeof(endCli);
  novo_sd = accept(sd, (struct sockaddr *) &endCli, &alen);
  if (novo_sd < 0) {
    fprintf(stdout, "Falha na conexao\n");
  	exit(1);
  }
  fprintf(stdout, "Cliente %s: %u conectado.\n", inet_ntoa(endCli.sin_addr), ntohs(endCli.sin_port));

  /*Recebe mensagem*/
  memset(&a, 0x0, sizeof(a));
  n = recv(novo_sd, &a, sizeof(a), 0);
  fprintf(stdout, "Mensagem: %s\n", a);

  memset(&op, 0x0, sizeof(op));
  n = recv(novo_sd, &op, sizeof(op), 0);
  fprintf(stdout, "Mensagem: %s\n", op);

  memset(&b, 0x0, sizeof(b));
  n = recv(novo_sd, &b, sizeof(b), 0);
  fprintf(stdout, "Mensagem: %s\n", b);

  /*Envia Resultado*/
  sprintf(msg, "%d", calcula(a, b, op));
  rc = send(novo_sd, msg, strlen(msg) + 1, 0);
  if(rc<0) {
   printf("nao foi possivel enviar dados");
   close(sd);
   exit(1);
  }

  close(novo_sd);
  close(sd);

  return 0;
}

int calcula(char *_a, char *_b, char *op) {

  int a = atoi(_a);
  int b = atoi(_b);

  switch (op[0]) {
    case '+':
      return a+b;
    case '-':
      return a-b;
    case '*':
      return a*b;
    case '/':
      return a/b;
  }
}
