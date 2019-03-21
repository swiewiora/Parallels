#include <stdlib.h>
#include<stdio.h>
#include<math.h>

#include <mpi.h>

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag, i; 
  double t1;
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  

  integral(rank, size);

  
  MPI_Finalize();
  
  return(0);

}

double f(double x){

  return( sin(x) );

}


int integral(int rank, int size){
  
  double a,b,c,integral,dx,x1,x2;
  int i,root,N,n_loc;
  double t_exec;
  
  if( rank == 0 ) {
    a=0; b=M_PI;
    //printf("Input: a,b,N:\n"); scanf("%lf %lf %d", &a, &b, &N);
    //printf("Input N:\n"); scanf("%d", &N);
    //N = 3628800; // 479001600;
    N = 11399900;

    t_exec = MPI_Wtime();
  }
  
  root=0; 
  MPI_Bcast( &N, 1, MPI_INT, root, MPI_COMM_WORLD );
  MPI_Bcast( &a, 1, MPI_DOUBLE, root, MPI_COMM_WORLD );
  MPI_Bcast( &b, 1, MPI_DOUBLE, root, MPI_COMM_WORLD );
  
  n_loc=ceil(N/size);   
  dx=(b-a)/N;   
  x1=a+rank*n_loc*dx;
  if(rank==size-1)   n_loc = N - n_loc*(size-1);
  
  c=0;
  for(i=0;i<n_loc;i++) {
    x2 = x1+dx;   
    c += 0.5*(f(x1)+f(x2))*dx;   
    x1=x2;
  }
  
  MPI_Reduce( &c, &integral, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD); 
  
  if( rank == 0 ) {
    t_exec = MPI_Wtime() - t_exec;
    printf("integral is: %20.15lf; time of execution %lf\n", integral, t_exec);
  }
  
  
}
