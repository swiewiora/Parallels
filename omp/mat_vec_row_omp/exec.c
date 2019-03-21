#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include "measure_time.h"

//#define DIMENSION 7936
//#define SIZE 62980096
//#define DIMENSION 1024
//#define SIZE 1048576
//#define DIMENSION 10000
//#define SIZE 100000000

//#define DIMENSION 19200
//#define SIZE 368640000

//#define DIMENSION 19000
//#define SIZE 368200000

//#define DIMENSION 15270
//#define SIZE 360000000

#define DIMENSION 19000
#define SIZE 368640000

void mat_vec(double* a, double* x, double* y, int n, int nt);

main ()
{
  static double x[DIMENSION],y[DIMENSION],z[DIMENSION];
  double *a;
  double t1;
  int n,nt,i,j;
  const int ione=1;
  const double done=1.0;
  const double dzero=0.0;

  a = (double *) malloc(SIZE*sizeof(double));

  for(i=0;i<SIZE;i++) a[i]=0.00000001*i;
  for(i=0;i<DIMENSION;i++) x[i]=0.0001*(DIMENSION-i);

  n=DIMENSION;

  nt=0;
  printf("Input number of threads: "); scanf("%d",&nt);

  printf("\nBeginning of procedure matrix-vector\n\n");

  
  init_time();
  t1 = omp_get_wtime();
  mat_vec(a,x,y,n,nt);
  t1 = omp_get_wtime() - t1;
  print_time();
  

  printf("\nEnd of procedure matrix-vector\n");
  printf("\texecution time: %lf, Gflop/s: %lf, GB/s> %lf\n",  
	 t1, 2.0e-9*SIZE/t1, (1.0+1.0/n)*8.0e-9*SIZE/t1);

  printf("\nBeginning of validation procedures\n");

  init_time();
  t1 = omp_get_wtime();
#pragma omp parallel for num_threads(nt) firstprivate(n) private(j) 
  for(i=0;i<n;i++){
    double t=0.0;
    int ni = n*i;
    for(j=0;j<n;j++){
      t+=a[ni+j]*x[j];
    }
    z[i]=t;
  }
  t1 = omp_get_wtime() - t1;
  print_time();

  printf("\nEnd of procedure matrix-vector\n");
  printf("\texecution time: %lf, Gflop/s: %lf, GB/s> %lf\n",  
	 t1, 2.0e-9*SIZE/t1, (1.0+1.0/n)*8.0e-9*SIZE/t1);

  for(i=0;i<DIMENSION;i++){
    if(fabs(y[i]-z[i])>1.e-9*z[i]) printf("Error!\n");
  }
}
