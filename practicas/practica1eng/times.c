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

double media(int* array, int N){
  double suma=0;
  int i;

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
  ptime->N = N;
  ptime->n_elems = n_perms;

  array_time = (double*)malloc(N*sizeof(double));
  array_perms = (double*)malloc(N*sizeof(double));

  perms = (int**)malloc(N*sizeof(int*));
  perms = generate_permutations(n_perms, N);

  for(i=0 ; i < n_perms ; i ++){

    start = clock();

    array_perms[i] = metodo(perms[i], 0, n_perms - 1);

    stop = clock();
    array_time[i] = (stop - start) / CLOCKS_PER_SEC;
  }

  /*Calcular media*/
  ptime->time = media(array_time, N);
  ptime->average_ob = media(array_perms, N);
  ptime->max_ob = array_perms[max(array_perms, 0, N - 1)]; 
  ptime->min_ob = array_perms[mina(array_perms, 0, N - 1)];

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
  
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  /* your code */
}


