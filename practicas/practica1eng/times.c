/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <time.h>
#include "times.h"
#include "sorting.h"

#define BILLION  1E9

double media(double* array, int N){
  double suma=0;
  int i;

  if(!array||N<1) return ERR;

  for(i=0; i<N; i++){
    suma += array[i];
  }

  return suma / N;
} 

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{
  int i;
  clock_t start, stop;
  double *array_time;
  double *array_perms;
  int** perms = NULL;

  if(!ptime||n_perms<1||N<1) return ERR;

  ptime->N = N;
  ptime->n_elems = n_perms;

  array_time = (double*)malloc(n_perms*sizeof(double));
  if(!array_time)
    return ERR;
  array_perms = (double*)malloc(n_perms*sizeof(double));
  if(!array_perms){
    free(array_time);
    return ERR;
  }
  perms = generate_permutations(n_perms, N);
  if(!perms){
    free(array_time);
    free(array_perms);
    return ERR;
  }

  for(i=0 ; i < n_perms ; i ++){

    start = clock();

    array_perms[i] = metodo(perms[i], 0, N - 1);

    stop = clock();
    array_time[i] = (double) (stop - start) / CLOCKS_PER_SEC;
  }


  /*Calcular media*/
  ptime->time = media(array_time, n_perms);
  ptime->average_ob = media(array_perms, n_perms);
  ptime->max_ob = array_perms[maxa(array_perms, 0, n_perms - 1)]; 
  ptime->min_ob = array_perms[mina(array_perms, 0, n_perms - 1)];

  for(i=0;i<n_perms;i++){
    free(perms[i]);
  }
  free(perms);
  free(array_time);
  free(array_perms);

  return OK;

}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
  PTIME_AA time;
  int i, ind;
  short check;
  int mem=0;

  if(!file||n_perms<1||num_max<num_min||!method||incr<1) return ERR;
  
  check=OK;

  for(i=num_min ; i < num_max; i+=incr, mem++);

  time = (PTIME_AA)malloc(mem*sizeof(TIME_AA));

  for(i=num_min, ind=0; i < num_max && check==OK; i+=incr, ind++){
    check=average_sorting_time(method, n_perms, i, &time[ind]);
  }

  if(check==OK)
    check=save_time_table(file, time, mem);

  free(time);

  return check;
}
short average_search_time(pfunc_search method, pfunc_key_generator generator, char order, int N, int n_times, PTIME_AA ptime){
  PDICT dict;
  int i, *perm, *mem, pos;
  double *array_time, *array_ob;
  clock_t start, stop;

  if(!ptime||n_times<1||N<1) return ERR;

  dict=init_dictionary(N,order);
  if(dict==NULL)
    return ERR;

  array_time = (double*)malloc(n_times*sizeof(double));
  if(!array_time){
    free_dictionary(dict);
    return ERR;
  }
  array_ob = (double*)malloc(n_times*sizeof(double));
  if(!array_ob){
    free_dictionary(dict);
    free(array_time);
    return ERR;
  }

  perm=generate_perm(N);
  if(!perm){
    free_dictionary(dict);
    free(array_time);
    free(array_ob);
    return ERR;
  }

  if(massive_insertion_dictionary(dict,perm,N)==ERR){
    free(perm);
    free_dictionary(dict);
    free(array_time);
    free(array_ob);
    return ERR;
  }

  mem=(int*)malloc((N*n_times)*sizeof(int));
  if(!mem){
    free(perm);
    free_dictionary(dict);
    free(array_ob);
    free(array_time);
    return ERR;
  }

  generator(mem,n_times*N,N);

  for(i=0 ; i < N*n_times ; i ++){

    start = clock();

    array_ob[i] = method(dict->table,0,N,mem[i], &pos);

    stop = clock();
    array_time[i] = (double) (stop - start) / CLOCKS_PER_SEC;
  }

  ptime->n_elems=N*n_times;
  ptime->N=N;
  ptime->time = media(array_time, N*n_times);
  ptime->average_ob = media(array_ob, n_times*N);
  ptime->max_ob = array_ob[maxa(array_ob, 0, (n_times*N)-1)]; 
  ptime->min_ob = array_ob[mina(array_ob, 0, (n_times*N)-1)];

  free_dictionary(dict);
  free(array_ob);
  free(array_time);
  free(mem);
  free(perm);

  return OK;
} 

short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char* file, int num_min, int num_max, int incr, int n_times){
  PTIME_AA time;
  int i, ind;
  short check=OK;
  int mem=0;

  if(!file||n_times<1||num_max<num_min||!method||incr<1) return ERR;

  for(i=num_min ; i < num_max; i+=incr, mem++);

  time = (PTIME_AA)malloc(mem*sizeof(TIME_AA));

  for(i=num_min, ind=0; i <= num_max && check==OK; ind++, i+=incr){
    check=average_search_time(method, generator, order, i, n_times, &time[ind]);
  }

  if(check==OK)
    check=save_time_table(file, time, mem);

  free(time);

  return check;
}

int mina(double* array, int ip, int iu)
{
  int aux,i;

  if(!array||iu<ip) return ERR;

  aux=ip;
  for(i=ip+1;i<=iu;i++){
    if(array[aux]>array[i])
      aux=i;
  }

  return aux;
}

int maxa(double* array, int ip, int iu)
{
  int aux,i;

  if(!array||iu<ip) return ERR;

  aux=ip;
  for(i=ip+1;i<=iu;i++){
    if(array[aux]<array[i])
      aux=i;
  }

  return aux;
}
