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


/*Private Functions*/
int min(int* array, int ip, int iu, int *count);
int max(int* array, int ip, int iu, int *count);
int merge(int* tabla, int ip, int iu, int imedio, int *count);
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

/***************************************************/
/* Function: SelectSortInv    Date:                */
/* Your comment                                    */
/***************************************************/
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

/***************************************************/
/* Function: MergeSort    Date:                    */
/* Your comment                                    */
/***************************************************/
int mergesort(int* tabla, int ip, int iu)
{
  int im=0, count=0, ret;
  
  /********BASE CASE********/
  if(ip == iu){
    return OK;
  }

  /********GENERAL CASE********/

  /*CALCULATES MEDIUM ELEMENT*/
  im = (ip+iu)/2;

  /*SORT FIRST HALF*/
  ret = mergesort(tabla, ip, im);
  if(ret==ERR){
    return ERR;
  }
  count += ret;
  
  /*SORT SECOND HALF*/
  ret = mergesort(tabla, im+1, iu);
  if(ret==ERR){
    return ERR;
  }
  count += ret;

  /*MERGE BOTH HALVES*/
  ret = merge(tabla, ip, iu, im, &count);
  if(ret==ERR){
    return ERR;
  }
  count += ret;

  return count;

}

int merge(int* tabla, int ip, int iu, int imedio, int *count){
  int *aux;
  int i,j,k;

  /*SAVES MEMORY FOR A SIZED TABLE*/
  aux = (int*) malloc((iu-ip+1)*sizeof(int));
  /*MEMORY CONTROL ERROR*/
  if(aux==NULL){
    return ERR;
  }

  /*FILLS THE NEW TABLE*/
  for(i=ip, j=imedio+1, k=0 ; i<imedio+1 && j<iu+1 ;k++){
    if(tabla[i] < tabla[j]){
      aux[k] = tabla[i];
      i++;
    }
    else{
      aux[k] = tabla[j];
      j++;
    }
    (*count)++;
  }

  /*ADDS THE REST OF THE ELEMENTS*/
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

  /*COPIES THE TABLE ON THE TABLE THAT WAS SENT*/
  if (icopytable(aux, tabla, ip, iu) == ERR){
    free(aux);
    return ERR;
  }

  /*FREES MEMORY*/
  free(aux);

  return OK;

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

/*AUX FUNCTION*/
/*COPIES THE TABLE 'OR' IN THE INDEX ('IP' TO 'IU') IN 'DES'*/
int icopytable(int* or, int* des, int ip, int iu){
  
  int i, j;

  for(i=0,j=ip ; j<iu+1 ; i++, j++){
    des[j] = or[i];
  }

  return OK;
}
