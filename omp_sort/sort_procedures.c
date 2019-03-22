/************************************************************************
File sort_procedures.c, content:

  sorting procedures:
    insertion_sort
    merge_sort
    quick_sort

*************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include"sort_procedures.h"

/*** Deklarations of internal helper functions ***/

/*---------------------------------------------------------
  merge - merges two sorted fragments into sorted array
----------------------------------------------------------*/
void merge (
  double* A,    /* in: array with 2 fragments to merge */
  int p,        /* in: initial index of the first fragment to merge */
  int q,        /* in: final index of the first fragment to merge */
  int r         /* in: final index of the 2nd fragment to merge */
  );

/*---------------------------------------------------------
  divide - divides 2 array A[p...q] into two arrays A[p...q], A[q+1...k]
    so that every element of the first part is smaller or equal to the element
    of the second part.
---------------------------------------------------------*/
int divide (    /* out: returns index q dividing the array A */
  double* A,    /* in: array with fragment to divide */
  int p,        /* in: beginning index of the fragment to divide */
  int k         /* in: final index of the fragment to divide */
  );


/*** Definitions of the sorting procedures and helper functions ***/

/*---------------------------------------------------------
  insertion_sort - sorting of n-element array
    from A[1] do A[n] (requires allocating array of size n+1)
----------------------------------------------------------*/
void insertion_sort (
  double* A,    /* table to sort */
  int p,        /* in: initial array index */
  int k         /* in: final array index */
  )
{

  int i,j,n;
  double t;

/*++++++++++++++++ executable statements ++++++++++++++++*/

  /* array size */
  n=(p-k+1);

  /* for each i-element of array (el. p...i-1 are already sorted) */
  for (i = p + 1; i <= k; i++) {

    /* processing element i */
    t = A [i];
    j = i - 1;
    /* ... and every element before it, starting from the nearest ... */
    /* ... until element lower than el. i */
    while (j >= p && A [j] > t){
      /* shift 1 forward element lower than el. i */
      A [j + 1] = A [j];
      j--;
    }

    /* insert el. i before the last bigger element */
    A [j + 1] = t;
  }

  return;
}

/*---------------------------------------------------------
  merge_sort(A,p,r) - sorting part of array A from index p to q
----------------------------------------------------------*/
void merge_sort (
  double* A,    /* array with a fragment to be sorted tablica fragment ktorej ma zostac posortowany */
  int p,        /* initial index of the fragment to sort */
  int r         /* final index of the fragment to sort */
  )
{

  int q;

/*++++++++++++++++ executable statements ++++++++++++++++*/

  /* if there are elements to sort */
  if (p < r) {
    //q=(int)(p+r)/2;
    /* find middle index of A */
    q = (p + r) / 2;
    /* sort separately left and right part */
    merge_sort (A, p, q);
    merge_sort (A, q + 1, r);
    /* merge sorted parts into sorted array */
    merge (A, p, q, r);

  }

  return;
}

/*---------------------------------------------------------
  merge - merges 2 sorted fragments into sorted array
	 warning!!! must be A[i] < 1 for each el. i
----------------------------------------------------------*/
void merge (
  double* A,    /* in: array with 2 fragments to merge */
  int p,        /* in: initial index of first fragment to merge */
  int q,        /* in: final index of first fragment to merge */
  int r         /* in:  final index of second fragment to merge */
  )
{

  int i, i1, i2;
  double *b1, *b2;

/*++++++++++++++++ executable statements ++++++++++++++++*/

  /* allocate memory for auxiliary arrays */
  b1 = (double *) malloc ( (q - p + 2 ) * sizeof (double) );
  b2 = (double *) malloc ( (r - q + 1 ) * sizeof (double) );

  /* assign sub-arrays A[p..q] i A[q+1..r] to b1 i b2 */
  for (i = 0; i <= q - p; i++)     b1 [i] = A [p + i];
  for (i = 0; i <= r - q - 1; i++) b2 [i] = A [q + 1 + i];

  /* insert guards; must be A [i] < 1 for each i */
  b1 [q - p + 1] = 1.0;
  b2 [r - q] = 1.0;

  i1 = 0;
  i2 = 0;

  /* for each free slot in fragment A[p..r] */
  for (i = 0; i <= r - p; i++) {
    /* if current element is lower than current element of b2 */
    if (b1 [i1] < b2 [i2]) {
      /* insert el. from b1 into corresponding place in array A and shift index of b1 */
      A [p + i] = b1 [i1];
      i1++;
    } else {
      /* similarly to b1, if b2 is smaller */
      A [p + i] = b2 [i2];
      i2++;
    }
  }

  /* free up memory */
  free (b1);
  free (b2);

  return;
}


/*---------------------------------------------------------
  quick_sort - sorting part of array A from index p to q
---------------------------------------------------------*/
void quick_sort (
  double* A,    /* array with a fragment to be sorted tablica fragment ktorej ma zostac posortowany */
  int p,        /* initial index of the fragment to sort */
  int r         /* final index of the fragment to sort */
  )
{

  int q;

/*++++++++++++++++ executable statements ++++++++++++++++*/

  /* if there're more elements to sort */
  if (p < r) { 
    /* divide arrays so that every el. of the left sub-array is 
    lower or equal to any element of right array */
    q = divide (A, p, r);

    //printf("division: %d - %d - %d\n",p,q,r);

    /* sort sub-arrays */
    quick_sort (A, p, q);
    quick_sort (A, q + 1, r);

  }

}


/*---------------------------------------------------------
  divide - divides 2 array A[p...q] into two arrays A[p...q], A[q+1...k]
    so that every element of the first part is smaller or equal to the element
    of the second part.
---------------------------------------------------------*/
int divide (    /* out: returns index q dividing the array A */
  double* A,    /* in: array with fragment to divide */
  int p,        /* in: beginning index of the fragment to divide */
  int k         /* in: final index of the fragment to divide */
  )
{

  int i, j, q;
  double t, s;

/*++++++++++++++++ executable statements ++++++++++++++++*/

  /* select element to sort */
  t = A [p];

  /* initialize indexes: i for searching left and j for right sub-array */
  i = p - 1;
  j = k + 1;

  /* inside infinite loop */
  for(;;){

    /* search arrays to the right until finding el. higher or equal to t */
    do j--; while (A [j] > t);
    /* search arrays to the left until finding el. lower or equal to t */
    do i++; while (A [i] < t);

    /* if there was no division - indexes are still too far away */
    if (i < j) {
      /* switch small and big element */
      s = A [j];
      A [j] = A [i];
      A [i] = s;

    }
    /* if all elements have been visited - indexes have met */
    else {
      return (j);
    }

  }
  
}
