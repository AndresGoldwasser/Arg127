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
  
  /*CONTROL ERROR*/
  if(!tabla || ip > iu){
    return ERR;
  }

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
  ret = merge(tabla, ip, iu, im);
  if(ret==ERR){
    return ERR;
  }
  count += ret;

  return count;

}

int merge(int* tabla, int ip, int iu, int imedio){
  int *aux;
  int count=0;
  int i,j,k;

  /*CONTROL ERROR*/
  if(!tabla || ip > imedio || imedio > iu){
    return ERR;
  }

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
    count++;
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

  return count;

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

int median(int *tabla, int ip, int iu,int *pos){
  if(!tabla||iu<ip||!pos) return ERR;

  *pos=ip;
  return 0;
}

int partition(int* tabla, int ip, int iu,int *pos){
  int val,auxval1,auxval2,i,count,check;

  if(!tabla||iu<ip||!pos) return ERR;

  check=median(tabla,ip,iu,pos);
  if(check==ERR)
    return ERR;
  
  count=0;

  val=tabla[*pos];

  auxval1=tabla[ip];
  tabla[*pos]=auxval1;
  tabla[ip]=val;

  *pos=ip;

  for(i=(*pos)+1;i<=iu;i++){
    if(tabla[i]<val){
      (*pos)++;

      auxval1=tabla[i];
      auxval2=tabla[*pos];
      tabla[i]=auxval2;
      tabla[*pos]=auxval1;
    }
    count++;
  }
  
  auxval1=tabla[ip];
  auxval2=tabla[*pos];
  tabla[ip]=auxval2;
  tabla[*pos]=auxval1;

  return count;
}

int quicksort(int* tabla, int ip, int iu){
  int pos,count;

  if(!tabla||iu<ip) return ERR;

  count=0;

  if(ip==iu) 
    return 0;
  else{
    count=partition(tabla,ip,iu,&pos);
    if(ip<pos-1){
      count=quicksort(tabla,ip,pos-1);
    }
    if (pos+1<iu){
      count=quicksort(tabla,pos+1,iu);
    }
  }

  return count;
}

int median_avg(int *tabla, int ip, int iu, int *pos){
  if (!tabla||iu<ip||!pos) return ERR;

  *pos=((iu+ip)/2);

  return 0;
}

int median_stat(int *tabla, int ip, int iu, int *pos){
  int i,j,k;
  if (!tabla||iu<ip||!pos) return ERR;

  i=tabla[ip];
  j=tabla[iu];
  k=tabla[(ip+iu)/2];

  if((i<j && i>k) || (i>j && i<k)){
    return ip;
  }
  if((j<i && j>k) || (j>i && j<k)){
    return iu;
  }
  if((k<j && k>i) || (k>j && k<i)){
    return (ip+iu)/2;
  }

  return ERR;

}
