/******************************************************************************
 *  Fundamentos de Sistemas Distribuidos
 *  Orientador Fernando William Cruz
 *
 *    Laboratorio 04 - MPI
 *
 *    Alunos:
 *      Artur Bersan de Faria, 14/0016813
 *      Iasmin Santos Mendes, 14/0041940
 *
 ****************************************************************************/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define  ARRAYSIZE	100000000
#define  MASTER		0

float  data[ARRAYSIZE];

int main (int argc, char *argv[])
{
  int   numtasks, taskid, rc, dest, offset, i, j, tag1, tag2, source, chunksize;
  float my_max_number, max_number;
  float my_min_number, min_number;
  float find_max(int myoffset, int chunk, int myid);
  float find_min(int myoffset, int chunk, int myid);
  MPI_Status status;

  /* Inicialização do Programa com MPI */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  if (numtasks % 4 != 0) {
    printf("Quitting. Number of MPI tasks must be divisible by 4.\n");
    MPI_Abort(MPI_COMM_WORLD, rc);
    exit(0);
  }

  /* Inicialização dos processos filhos */
  MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
  printf ("MPI task %d has started...\n", taskid);
  chunksize = (ARRAYSIZE / numtasks);
  tag2 = 1;
  tag1 = 2;

  /* Execução do processo pai */
  if (taskid == MASTER){

    /* Inicialização do vetor */
    max_number = 0;
    min_number = 0;

    for(i = 0; i < ARRAYSIZE; i++) {
      data[i] = pow((i - ARRAYSIZE/2),2);
      data[i] = sqrt(data[i]);
    }

    /* Passagens dos parâmetros do vetor referentes a cada tarefa  */
    offset = chunksize;
    for (dest = 1; dest < numtasks; dest++) {
      MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
      MPI_Send(&data[offset], chunksize, MPI_FLOAT, dest, tag2, MPI_COMM_WORLD);
      printf("Sent %d elements to task %d offset= %d\n",chunksize,dest,offset);
      offset = offset + chunksize;
    }

    /* Busca pelo meaximo e minimo na parte do vetor destinada ao processo Pai */
    offset = 0;
    my_max_number = find_max(offset, chunksize, taskid);
    my_min_number = find_min(offset, chunksize, taskid);

    /* Recebe o resultado de cada tarefa */
    for (i = 1; i < numtasks; i++) {
      source = i;
      MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status);
      MPI_Recv(&data[offset], chunksize, MPI_FLOAT, source, tag2,
                      MPI_COMM_WORLD, &status);
    }

    /* Calcula o mínimo e o máximo a partir dos valores enviados por cada função */
    MPI_Reduce(&my_max_number, &max_number, 1, MPI_FLOAT, MPI_MAX, MASTER, MPI_COMM_WORLD);
    MPI_Reduce(&my_min_number, &min_number, 1, MPI_FLOAT, MPI_MIN, MASTER, MPI_COMM_WORLD);


    printf("\n\nMax Value = %f\n", max_number);
    printf("Minimum Value = %f\n\n", min_number);

  }

  /* Execução do processo filho */
  if (taskid > MASTER) {

    /* Espera receber os parâmetros de entrada */
    source = MASTER;
    MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status);
    MPI_Recv(&data[offset], chunksize, MPI_FLOAT, source, tag2, MPI_COMM_WORLD, &status);

    /* Busca pelo meaximo e minimo na parte do vetor destinada ao processo filho em execucao */
    my_max_number = find_max(offset, chunksize, taskid);
    my_min_number = find_min(offset, chunksize, taskid);

    /* Envia os resultados para o pai */
    dest = MASTER;
    MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
    MPI_Send(&data[offset], chunksize, MPI_FLOAT, MASTER, tag2, MPI_COMM_WORLD);

    MPI_Reduce(&my_max_number, &max_number, 1, MPI_FLOAT, MPI_MAX, MASTER, MPI_COMM_WORLD);
    MPI_Reduce(&my_min_number, &min_number, 1, MPI_FLOAT, MPI_MIN, MASTER, MPI_COMM_WORLD);

  }

  MPI_Finalize();

}


/* Funcao para encontrar o valos maximo */
float find_max(int myoffset, int chunk, int myid) {

  int i;
  float my_max_number = 0;

  for(i = myoffset; i < myoffset + chunk; i++) {
    if(my_max_number < data[i]){
            my_max_number = data[i];
    }
  }

  printf("Task %d my_max_number = %f\n",myid,my_max_number);

  return(my_max_number);
}

/* Funcao para encontrar o valos minimo */
float find_min(int myoffset, int chunk, int myid) {

  int i;
  float my_min_number = 0;

  for(i = myoffset; i < myoffset + chunk; i++) {
    if(my_min_number > data[i]){
      my_min_number = data[i];
    }
  }
  printf("Task %d my_min_number = %f\n",myid,my_min_number);


  return(my_min_number);
}
