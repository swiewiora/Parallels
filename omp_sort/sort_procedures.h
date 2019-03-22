/*************************************************************************
File sort_procedres.h, headers of sorting procedures from file sort.c
*************************************************************************/
#ifndef _sort_
#define _sort_

/*---------------------------------------------------------
  insertion_sort - sorting of n-element array
    from A[1] do A[n] (requires allocating array of size n+1)
----------------------------------------------------------*/
extern void insertion_sort(
  double* A,    /* table to sort */
  int p,        /* in: initial array index */
  int k         /* in: final array index */
  );

/*---------------------------------------------------------
  merge_sort(A,p,r) - sorting part of array A from index p to q
----------------------------------------------------------*/
extern void merge_sort(
  double* A,    /* array with a fragment to be sorted tablica fragment ktorej ma zostac posortowany */
  int p,        /* initial index of the fragment to sort */
  int r         /* final index of the fragment to sort */
  );

/*---------------------------------------------------------
  quick_sort - sorting part of array A from index p to q
---------------------------------------------------------*/
extern void quick_sort(
  double* A,    /* array with a fragment to be sorted tablica fragment ktorej ma zostac posortowany */
  int p,        /* initial index of the fragment to sort */
  int r         /* final index of the fragment to sort */
  );

#endif