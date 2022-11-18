/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/***************************************************/
/* Function: random_num Date:                      */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{ 
  int num;

  if(inf>sup) return ERR;

  num=(rand() % (sup-inf+1))+inf;

  return num;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int i, j, temp1, temp2, *perm;

  if(N<1) return NULL;

  perm=(int*)malloc(N*sizeof(int));
    if(!perm)
      return NULL;
  
  for (i=0;i<N;i++){
    perm[i]=i+1;
  }

  for (i=0;i<N;i++){
    j=random_num(i,N-1);
    temp1=perm[j];
    temp2=perm[i];
    perm[i]=temp1;
    perm[j]=temp2;
  }

  return perm;
}


/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int i, j, **perm_library;

  if (n_perms<1||N<1) return NULL;

  perm_library=(int**)malloc(n_perms*sizeof(int*));
  if(!perm_library)
    return NULL;
  
  for(i=0;i<n_perms;i++){
    perm_library[i]=generate_perm(N);
    if(perm_library[i]==NULL){
      for (j=0;j<i;j++){
        free(perm_library[j]);
      }
      free(perm_library);
      break;
    }
  }

  if(i!=n_perms){
    return NULL;
  }
  else {
    return perm_library;
  }
}
