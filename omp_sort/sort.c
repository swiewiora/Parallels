/************************************************************************
File sort.c, content:

  main        - testing sorting algorithms 
  generate    - generates numerical sequence with random values
  check       - checks if numerical sequence is sorted in ascending order
 *************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>
#include"sort_procedures.h"

/*** Declaring inner helper functions ***/

/*---------------------------------------------------------
  generate    - generates numerical sequence with random values
----------------------------------------------------------*/
void generate(
  double* A,    /* array */
  int n         /* size */
  );

/*---------------------------------------------------------
  check    -  checks if numerical sequence is sorted in ascending order
----------------------------------------------------------*/
int check(
  double* A,    /* array */
  int n         /* size */
  );

/*---------------------------------------------------------
  compare - compares two elements of array
----------------------------------------------------------*/
int compare( /* returns: -1 - x < y */
	      /*                0 - x = y */
	      /*                1 - x > y */
  double* x,  /* number to compare */
  double* y   /* number to compare */
  );


/*---------------------------------------------------------
  getdaytime - clock time
---------------------------------------------------------*/
double getdaytime();

/*---------------------------------------------------------
  getcputime - CPU time 
---------------------------------------------------------*/
double getcputime();

void merge_sort_openmp(
  double* A,   
  int p,      
  int r,
  int poziom      
);

/*** Definitions of procedures ***/

/*---------------------------------------------------------
  main - testing sorting algorithms 
----------------------------------------------------------*/
int main(int argc, char **argv)
{

/* local variables */
  double *A;     /* array to be sorted */
  int n;         /* array size */
  int i, info;   /* auxiliary variables */
  double time;   /* used to measure execution time */

/*++++++++++++++++ executable statements ++++++++++++++++*/

  printf("Input array size: \n");
  scanf("%d",&n);
  A = (double *)malloc((n+1)*sizeof(double));

  //generate(A,n);

  //time = getdaytime();

  //insertion_sort(A,1,n);

  //printf("duration of insertion sort: %lf\n",getdaytime()-time);

  //info=check(A,n);

  //if(info>=0) printf("result OK\n");
  //else printf("result is wrong!\n");

  generate(A,n);

  //for(i=1;i<=n;i++){
  //  printf("%10.5lf",A[i]);
  //}

  time = getdaytime();

  //qsort( &A[1], n, sizeof(double), compare);
  qsort((void *) &A[1], (size_t) n, (size_t) sizeof(double), 
        (int (*)(const void*,const void*))compare);

  printf("duration of system sorting: %lf\n",getdaytime()-time);

  info=check(A,n);

  if(info>=0) printf("result OK\n");
  else printf("result is wrong!\n");

  generate(A,n);

  time = getdaytime();

  merge_sort(A,1,n);

  printf("duration of merge sort: %lf\n",getdaytime()-time);

  info=check(A,n);

  if(info>=0) printf("result OK\n");
  else printf("result is wrong!\n");

  generate(A,n);

  time = getdaytime();

  quick_sort(A,1,n);

  printf("duration of quick sort: %lf\n",getdaytime()-time);

  info=check(A,n);

  if(info>=0) printf("result OK\n");
  else printf("result is wrong!\n");

  generate(A,n);

  time = getdaytime();

#pragma omp parallel
  {
#pragma omp single
    { 
      merge_sort_openmp(A,1,n,0);
    }
  }

  printf("duration of parallel merge sort: %lf\n",
	 getdaytime()-time);

  info=check(A,n);

  if(info>=0) printf("result OK\n");
  else printf("result is wrong!\n");

  generate(A,n);

  time = getdaytime();

#pragma omp parallel
  {
#pragma omp single
    { 
      merge_sort_openmp_2(A,1,n,0);
    }
  }

  printf("duration of parallel merge sort (final): %lf\n",
	 getdaytime()-time);

  info=check(A,n);

  if(info>=0) printf("result OK\n");
  else printf("result is wrong!\n");

  generate(A,n);

  time = getdaytime();

  merge_sort_openmp_4(A,1,n);

  printf("duration of parallel merge sort (nested): %lf\n",
  	 getdaytime()-time);

  info=check(A,n);

  if(info>=0) printf("result OK\n");
  else printf("result is wrong!\n");

  free(A);

  return(0);
}


/*---------------------------------------------------------
  generate    - generates numerical sequence with random values
----------------------------------------------------------*/
void generate(
  double* A,    /* array */
  int n         /* size */
  )
{

  int i;
  double sum;

/*++++++++++++++++ executable statements ++++++++++++++++*/

  sum=0.0;
  for(i=1;i<=n;i++){

    A[i]=drand48();
    sum += A[i];
    //printf("%10.5lf",A[i]);

  }

  //printf("average %lf\n", sum/n);

  return;
}

/*---------------------------------------------------------
  check    -  checks if numerical sequence is sorted in ascending order
----------------------------------------------------------*/
int check(
  double* A,    /* array */
  int n         /* size */
  )
{

  int i;

/*++++++++++++++++ executable statements ++++++++++++++++*/

  for(i=2;i<=n;i++){
    if(A[i]<A[i-1]) return(-1);
  }

  return(0);
}

/*---------------------------------------------------------
  compare - compares two elements of array
----------------------------------------------------------*/
int compare( /* returns: -1 - x < y */
        /*                0 - x = y */
        /*                1 - x > y */
  double* x,  /* number to compare */
  double* y   /* number to compare */
  )
{

  if(*x<*y) return(-1);
  else if(*x>*y) return(1);
  else return(0);

}

/* static variables for time measurements */
static struct rusage rp,rk;
static struct timeval tp,tk;
static struct timezone tzp;

/*---------------------------------------------------------
getdaytime - to return number of wall clock seconds from 
	time measurement initialization
---------------------------------------------------------*/
double getdaytime()
{ 
  
  double daytime;
  
  gettimeofday(&tk, &tzp);
  
  daytime=(tk.tv_usec-tp.tv_usec)/1e6+tk.tv_sec-tp.tv_sec;
  
  return(daytime);
}

/*---------------------------------------------------------
getcputime - to return number of cpu seconds from 
	time measurement initialization
---------------------------------------------------------*/
double getcputime()
{ 
  
  double cputime;
  
  getrusage(RUSAGE_SELF, &rk);
  
  cputime = (rk.ru_utime.tv_usec-rp.ru_utime.tv_usec)/1e6;
  cputime += rk.ru_utime.tv_sec-rp.ru_utime.tv_sec;
  
  return(cputime);
}
