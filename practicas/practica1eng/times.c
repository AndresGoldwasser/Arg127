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
  int i, begin, end;
  struct timespec start, stop;
  double array_time[N];
  double array_perms[N];
  int** perms = NULL;
  ptime->N = N;
  ptime->n_elems = n_perms;

  perms = (int**)malloc(N*sizeof(int*));
  perms = generate_permutations(n_perms, N);

  for(i=0 ; i < N ; i ++){

    if (clock_gettime( CLOCK_REALTIME, &start) == -1 ){
      return ERR;
    }

    metodo(perms[i], 0, n_perms - 1);

    if (clock_gettime( CLOCK_REALTIME, &end) == -1 ){
      return ERR;
    }
    array_times[i] = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec ) / BILLION;
  }

  /*Calcular media*/
  ptime->average_ob = media(array, N);
  ptime->max_ob = 
  ptime->min_ob = array[min(array, 0, N - 1)]; 

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


