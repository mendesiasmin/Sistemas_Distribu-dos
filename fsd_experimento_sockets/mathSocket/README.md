# FSD - Trabalho 1, TCP
>  Alunos: Artur Bersan Iasmin Mendes

>  Matrículas: 14/0041940 e 14/0016813

## Introdução

Um sistema distribuídos se define por um sistema que interliga diversos nós de um processamento de tal forma que um processo seja exucutado pelo nó mais disponível. Esse experimento se define por uma introdução ao sistema distribuídos dando uma passagem de parâmetros, envolvendo módulos cliente e servidor conectados por sockets UDP e TCP em que um cliente irá fazer uma requisição de uma operação matemática entre dois numeros e o servidor irá receber essa requisição e responderá com o resultado da operação para o cliente.

## Descrição da solução

A solução do problema será dividida em duas partes, a solução UDP e a solução TCP

### Solução UDP

A solução via protocolo UDP, consegue receber diversas conexões e os dados são operados individualmente. Caso dois clientes enviem ao mesmo tempo pode acontecer que um processo interrompa o outro. Por isso o protocolo UDP é considerado não seguro, pois pode haver perda de pacotes.

### Solução TCP

A solução via protocolo TCP, consegue receber apenas uma conexão por vez. Quando mais de um cliente solicita uma conexão com o servidor na mesma porta, ele só será atendido quando a conexão estabelecida anteriomente seja encerrada.

## Detalhes do trabalho

As demais informações de uso do código, compilação e entre outras informações do trabalho estão nas pastas de cada protocolo.
