# FSD - Trabalho 1, TCP
>  Alunos: Artur Bersan Iasmin Mendes

>  Matrículas: 14/0041940 e 14/0016813

## Sistema Operacional Utilizado
> Ubuntu Linux - x86_64 Kernel 3.13.0-32-generic

## Ambiente de Desenvolvimento
> Computadores pessoais. Utilizamos o Linux, sys/types, sys/socket, gcc, arpa/inet, git e vim.

## Instruções
Há a necessidade de dois terminais estárem em conexão com a mesma rede, sendo ela interna, podendo ser configurada com o `ifconfig`, ou em uma rede externa.

#### Compilando
Para compilar, entre com o seguinte comando:
```
 $ gcc -o client tcpCalculaclient.c 
 $ gcc -o server tcpCalculaserver.c 
```
Será gerado dois executáveis que deveram ser conectados em dois terminais distintos.
#### Utilização
Escolha um terminal que servirá como servidor e rode o binário da seguinte forma:
```
 $ ./server `ip_server` `porta_de_conexão`
```
O outro terminal deve servir como servidor e deverá receber o seguinte comando:
``` 
 $ ./client `ip_server` `porta_de_conexão` `numero A` `operação` `numero B`
```
Para utilizar a operação `*` deve ser utilizado `/*` por ser um caracter especial.
#### Caso de Teste Válido
Um caso de teste válido é executar o seguinte input:
```
$ ./server 192.168.22.2 9090
$ ./client 192.168.22.2 9090 2 + 3
```

## Limitações conhecidas
Os numeros são declarados como `int`, logo o sistema não resolve operações com números que passem do tamanho reservado para um inteiro e nem realiza operações com o tipo `float`
