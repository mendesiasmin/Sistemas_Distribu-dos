# Lab04 – Construindo aplicações distribuídas usando MPI
>  Alunos: Artur Bersan e Iasmin Mendes

>  Matrículas: 14/0041940 e 14/0016813

## Introdução


## Descrição da solução

Para a solução de um único host, foi utilizado a função 'MPI_Init' que inicializa o ambiente MPI e sendo que um dos parâmetros indica a quantidade de tasks que irão ser utilizadas. Em seguida a função MPI_Comm_size determina o tamanho do grupo associado com o comunicador e é passado como parâmentro as constantes e o endereço de uma variável inteira que receberá por passagem de parâmentro a quantidade de tasks. Como o array de teste utilizado tem um tamanho divisível por 4, foi escolhido que o número de tasks a serem utilizadas deveriam ser divísivel por 4 para que não houvesse divisão não exata das atividades. A função MPI_Comm_rank determina a classificação do processo de chamada no comunicado, e caso o processo seja o MASRTER, ou seja, o pai inicializará a primeira porção do array, calculará o maior numero dessa porção, esperará para receber cada porção dos resultados dos processos filhos e logo depois, ele pega o minimo e maximo final com o MPI_Reduce. Caso seja um processo filho, ele receberá a task designinada pela taks master, calculará o maximo e minimo da porção e em seguida, manda o resultado para a task master.

## Sistema Operacional Utilizado                                                    
> Ubuntu Linux - x86_64 Kernel 3.13.0-32-generic

## Ambiente de Desenvolvimento                                                      
> Computadores pessoais. Utilizamos o Linux, mpi, git e vim.

## Instruções                                                                       
Há a necessidade de três terminais estárem em conexão com a mesma rede, sendo ela interna, podendo ser configurada com o `ifconfig`, ou em uma rede externa.

#### Compilando                                                                     
Para compilar, entre com o seguinte comando:
```
$ mpicc maiormenor_mpi.c -o maior -lm
```
É necessário a flga '-lm' por conta da função 'sqrt'

#### Utilização                                                                     
Em um terminal execute o seguinte comando
```
$ mpirun -np <numero de tasks> ./maior
```

#### Caso de Teste Válido                                                           
Um caso de teste válido é executar o seguinte input:

```
$ mpicc maiormenor_mpi.c -o maior -lm
$ mpirun -np 4 ./maior                              
```
