/********************************/
/* Lab.Redes 2 udpClient.c      */
/********************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* memset() */
#include <sys/time.h> /* select() */
#include <stdlib.h> /*#*/
#define MAX_MSG 100

int main(int argc, char *argv[]) {
  int sd, rc,n, i, tam_Serv;
  struct sockaddr_in ladoCli;   /* dados do cliente local   */
  struct sockaddr_in ladoServ; 	/* dados do servidor remoto */
  
  char   msg[MAX_MSG];
/* confere o numero de argumentos passados para o programa */
  if(argc<3)  {
    printf("uso correto: %s <ip_do_servidor> <porta_do_servidor> <dado1> ... <dadoN> \n", argv[0]);
    exit(1);  }

/* Preenchendo as informacoes de identificacao do remoto */
  ladoServ.sin_family 	   = AF_INET;
  ladoServ.sin_addr.s_addr = inet_addr(argv[1]);
  ladoServ.sin_port 	   = htons(atoi(argv[2]));

/* Preenchendo as informacoes de identificacao do cliente */
  ladoCli.sin_family 	 = AF_INET;
  ladoCli.sin_addr.s_addr= htonl(INADDR_ANY);
  ladoCli.sin_port 	     = htons(0); /* usa porta livre entre (1024-5000)*/

/* Criando um socket. Nesse momento a variavel       */
/* sd contem apenas dados sobre familia e protocolo  */

  sd = socket(AF_INET,SOCK_DGRAM,0);
  if(sd<0) {
    printf("%s: nao pode abrir o socket \n",argv[0]);
    exit(1); }

/* Relacionando o socket sd com a estrutura ladoCli /*
/* Depois do bind, sd faz referencia a protocolo local, ip local e porta local */
  rc = bind(sd, (struct sockaddr *) &ladoCli, sizeof(ladoCli));
  if(rc<0) {
    printf("%s: nao pode fazer um bind da porta\n", argv[0]);
    exit(1); }
  printf("{UDP, IP_Cli: %s, Porta_Cli: %u, IP_R: %s, Porta_R: %s}\n", inet_ntoa(ladoCli.sin_addr), ntohs(ladoCli.sin_port), argv[1], argv[2]);

  /* Enviando um pacote para cada parametro informado */
  for(i=3;i<argc;i++) {
    rc = sendto(sd, argv[i], strlen(argv[i]), 0,(struct sockaddr *) &ladoServ, sizeof(ladoServ));
    if(rc<0) {
      printf("%s: nao pode enviar dados %d \n",argv[0],i-1);
      close(sd);
      exit(1); }
    printf("Enviando parametro %d: %s\n", i-2, argv[i]);
  } /* fim do for (laco) */


  while(1) {

    /* inicia o buffer */
    memset(msg,0x0,MAX_MSG);
    tam_Serv = sizeof(ladoServ);
    /* recebe a mensagem  */
    n = recvfrom(sd, msg, MAX_MSG, 0, (struct sockaddr *) &ladoServ, &tam_Serv);
    if(n<0) {
      printf("%s: nao pode receber dados \n",argv[0]);
      continue;}

    /* imprime a mensagem recebida na tela do usuario */
    printf(" IP_R: %s, Porta_R: %u} => %s\n",inet_ntoa(ladoServ.sin_addr), ntohs(ladoServ.sin_port), msg);

  } /* fim do while */


  return 1;
} /* fim do programa */
