#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#include "search_max_openmp.h"

#define WYMIAR 1000000
#define SIZE WYMIAR


main ()
{

  static double a[SIZE];
  int n,i,j;
  double a_max;
  double t1;

  for(i=0;i<SIZE;i++) a[i]=(0.00000001*i)*(SIZE-1-i);

  n = SIZE;


  t1=omp_get_wtime();
  a_max = search_max(a, 0, n-1);
  t1=omp_get_wtime()-t1;
  printf("maximal element %lf\n", a_max); 
  printf("time for sequential linear search: %lf\n", t1);

  t1=omp_get_wtime();
  a_max = search_max_openmp_simple(a, 0, n-1);
  t1=omp_get_wtime()-t1;
  printf("maximal element %lf\n", a_max); 
  printf("time for parallel linear search: %lf\n", t1);

  t1=omp_get_wtime();
  a_max = search_max_openmp_task(a, 0, n-1);
  t1=omp_get_wtime()-t1;
  printf("maximal element %lf\n", a_max); 
  printf("time for parallel linear search: %lf\n", t1);

  t1=omp_get_wtime();
  a_max = bin_search_max(a, 0, n-1);
  t1=omp_get_wtime()-t1;
  printf("maximal element %lf\n", a_max); 
  printf("time for sequential binary search: %lf\n", t1);

  t1=omp_get_wtime();
  a_max = bin_search_max_openmp(a, 0, n-1);
  t1=omp_get_wtime()-t1;
  printf("maximal element %lf\n", a_max); 
  printf("time for parallel binary search: %lf\n", t1);

}


