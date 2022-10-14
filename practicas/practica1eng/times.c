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

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  int i;
  FILE *f;

  if(!file||!ptime||n_times<1) return ERR;

  f=fopen(file,"w");
  if(!f) return ERR;

  fprintf(f,"Tamaño\tTime\tAvr. OB\tMin OB\tMax OB\n");

  for(i=0;i<n_times;i++){
    fprintf(f,"%d\t%E\t%.0f\t%d\t%d\n",ptime[i].N,ptime[i].time,ptime[i].average_ob,ptime[i].min_ob,ptime[i].max_ob);
  }

  fclose(f);
  return OK;
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