/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order)
{
  PDICT dict;

	if(size<=0||(order!=1&&order!=0))
    return NULL;

  dict->size=size;
  dict->n_data=0;
  dict->order=order;
  dict->table=(int*)malloc(size*sizeof(int));
  if(dict->table==NULL)
    return NULL;

  return dict;
}

void free_dictionary(PDICT pdict)
{
/*ERROR CONTROL*/
  if(!pdict){
    return;
  }

  free(pdict->table);
  return;
}

int insert_dictionary(PDICT pdict, int key)
{
	int aux, j;
  
  /*ERROR CONTROL*/
  if(!pdict){
    return ERR;
  }
  
  /*ERROR CONTROL*/
  if(pdict->n_data == pdict->size){
    return ERR;
  }

  /*ARRAY ISNT SORTED*/
  if(pdict->order == NOT_SORTED){
    pdict->table[pdict->n_data] = key;
    pdict->n_data++;
  }

  /*ARRAY IS SORTED*/
  else if(pdict->order == SORTED){
    aux=pdict->table[pdict->n_data-1]; 
    j=pdict->n_data-2;
    while (j >= 0 && pdict->table[j]>aux){
      pdict->table[j+1]=pdict->table[j]; 
      j--;
    }
    pdict->table[j+1]=aux;
  }


int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys)
{
  int i,flag;

  if(pdict==NULL||keys==NULL||n_keys<=0) return ERR;

  for(i=0,flag=OK;i<n_keys&&flag==OK;i++){
    flag=insert_dictionary(pdict,keys[i]);
  }

  if(flag!=OK)
    return ERR;
  else
    return OK;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
	int ret;
  if(!pdict||!ppos||!method){
    return ERR;
  }

  ret = method(pdict->table, 0, pdict->n_data-1, key, ppos);
  
  return ret;
}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
	int i,count;
  if(!table) return ERR;
  
  if(L<F){
    *ppos=NOT_FOUND;
    return 0;
  }

  i=(L-F)/2;
  count=1;
  if(table[i]==key){
    *ppos=i;
    return count;
  }
  else if(table[i]>key){
    count+=bin_search(table,F,i-1,key,ppos);
  }
  else if(table[i]<key){
    count+=bin_search(table,i+1,L,key,ppos);
  }
  
  return count;
}

int lin_search(int *table,int F,int L,int key, int *ppos)
{
	int i, count=0, ret=ERR;
	
  /*CONTROL ERROR*/
  if(!table||!ppos||L<F){
    return ERR;
  }

  for(i=F;i<L;i++){
    count++;
    if(table[i] == key){
      *ppos = i;
      ret = OK;
      break;
    }
  }

  if(ret==OK){
    return count;
  }

  return ERR;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
	int i, count=0, ret=ERR, aux;
	
  /*CONTROL ERROR*/
  if(!table||!ppos||L<F){
    return ERR;
  }

  for(i=F;i<L;i++){
    count++;
    if(table[i] == key){

      /*SWAP*/
      aux = table[i-1] ;
      table[i-1] = table[i];
      table[i] = aux;

      *ppos = i-1;
      ret = OK;
      break;
    }
  }

  if(ret==OK){
    return count;
  }

  return ERR;
}


