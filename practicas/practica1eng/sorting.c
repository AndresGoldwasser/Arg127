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
#include <stdlib.h>

int merge(int* tabla, int ip, int iu, int imedio);
int icopytable(int* or, int* des, int ip, int iu);

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
    if(minnin==ERR)
      break;
    temp1=array[minnin];
    temp2=array[i];
    array[i]=temp1;
    array[minnin]=temp2;
  }

  if(minnin==ERR)
    return ERR;

  return cont;
}

int SelectSortInv(int* array, int ip, int iu)
{
  int i,maxam,temp1,temp2,cont;
  if(!array||iu<ip) return ERR;

  cont=0;
  for(i=ip;i<iu;i++){
    maxam=max(array, i, iu, &cont);
    if(maxam==ERR)
      break;
    temp1=array[maxam];
    temp2=array[i];
    array[i]=temp1;
    array[maxam]=temp2;
  }

  if(maxam==ERR)
    return ERR;

  return cont;
}

int min(int* array, int ip, int iu, int *count)
{
  int aux,i;

  if(!array||iu<ip||!count) return ERR;

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

  if(!array||iu<ip||!count) return ERR;

  aux=ip;
  for(i=ip+1;i<=iu;i++){
    if(array[aux]<array[i]){
      aux=i;
    }
    (*count)++;
  }

  return aux;
}

int mergesort(int* tabla, int ip, int iu)
{
  int im, st;
  
  /*BASE CASE*/
  if(ip == iu){
    return OK;
  }

  /*GENERAL CASE*/
  im = (ip+iu)/2;

  st = mergesort(tabla, ip, im);
  if(st==ERR){
    return ERR;
  }
  
  st = mergesort(tabla, im+1, iu);
  if(st==ERR){
    return ERR;
  }

  return merge(tabla, ip, iu, im);

}

int merge(int* tabla, int ip, int iu, int imedio){
  int *aux;
  int i,j,k;

  aux = (int*) malloc((iu-ip+1)*sizeof(int));
  if(aux==NULL){
    return ERR;
  }

  for(i=ip, j=imedio+1, k=0 ; i<imedio+1 && j<iu+1 ;k++){
    if(tabla[i] < tabla[j]){
      aux[k] = tabla[i];
      i++;
    }
    else{
      aux[k] = tabla[j];
      j++;
    }
  }

  while(i<imedio+1){
    aux[k] = tabla[i];
    i++;
    k++;
  }

  while(j<iu+1){
    aux[k] = tabla[j];
    j++;
    k++;
  }

  if (icopytable(aux, tabla, ip, iu) == ERR){
    free(aux);
    return ERR;
  }

  free(aux);
  return OK;

}

int icopytable(int* or, int* des, int ip, int iu){
  
  int i, j;

  for(i=0,j=ip ; j<iu+1 ; i++, j++){
    des[j] = or[i];
  }

  return OK;
}
