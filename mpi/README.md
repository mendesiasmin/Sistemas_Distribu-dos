# Laboratório 04 – Construindo aplicações distribuídas usando MPI

Universidade de Brasília <br>
Fundamentos de Sistemas Distribuídos <br>
Orientador: Fernando William Cruz <br>
01/2017 <br>

Alunos:

* Artur Bersan de Faria, 14/0016813
* Iasmin Santos Mendes, 14/0041940



## Sistema Operacional Utilizado                                                    
> Ubuntu Linux - x86_64 Kernel 3.13.0-32-generic

## Ambiente de Desenvolvimento                                                      

* VIM
* Atom
* Git
* MIPCH2


## Compilação e Execução
Para compilar, entre com o seguinte comando:
```
$ mpicc mpi_min_max.c -o prog -lm
```
É necessário a flga '-lm' por conta das funções matemáticas chamadas.

Em um terminal execute o seguinte comando
```
$ mpirun -np <numero de tasks> ./prog
```

#### Caso de Teste Válido                                                           
Um caso de teste válido é executar o seguinte input:

```
$ mpicc maiormenor_mpi.c -o maior -lm
$ mpirun -np 4 ./maior                              
```
