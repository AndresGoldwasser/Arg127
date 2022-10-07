/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"

/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int SelectSort(int* array, int ip, int iu)
{
  int i,minnin,temp1,temp2,cont;
  if(!array||iu<ip) return ERR;

  cont=0;
  for(i=ip;i<iu;i++){
    minnin=min(array, i, iu, &cont);
    temp1=array[minnin];
    temp2=array[i];
    array[i]=temp1;
    array[minnin]=temp2;
  }

  return cont;
}

int SelectSortInv(int* array, int ip, int iu)
{
  int i,maxam,temp1,temp2,cont;
  if(!array||iu<ip) return ERR;

  cont=0;
  for(i=ip;i<iu;i++){
    maxam=max(array, i, iu, &cont);
    temp1=array[maxam];
    temp2=array[i];
    array[i]=temp1;
    array[maxam]=temp2;
  }

  return cont;
}

int min(int* array, int ip, int iu, int *count)
{
  int aux,i;
  aux=ip;
  for(i=ip+1;i<=iu;i++){
    if(array[aux]>array[i]){
      aux=i;
    }
    (*count)++;
  }

  return aux;
}

int max(int* array, int ip, int iu, int *count)
{
  int aux,i;
  aux=ip;
  for(i=ip+1;i<=iu;i++){
    if(array[aux]<array[i]){
      aux=i;
    }
    (*count)++;
  }

  return aux;
}