# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "mpi.h"

int main ( int argc, char *argv[] );
void heat_part ( int n, int p, int id, double x_min, double x_max );

/******************************************************************************/

int main ( int argc, char *argv[] )
{
  double a = 0.0; // left side of the compartment
  double b = 1.0; // right side of the compartment
  int i;  
  int id; // rank
  int n;  // number of points of each node
  int p;  // size
  double x_max;
  double x_min;

  MPI_Init ( &argc, &argv );

  MPI_Comm_rank ( MPI_COMM_WORLD, &id );

  MPI_Comm_size ( MPI_COMM_WORLD, &p );

  n = 12; // number of points for each node
  i = 0;  // initial moment of time

  // coordinate of the left point for node 'id'
  x_min = ( ( double )( p * n + 1 - id * n - i ) * a   
          + ( double )(             id * n + i ) * b ) 
          / ( double ) ( p * n + 1              );

  i = n + 1;

  // coordinate of the right point for node 'id'
  x_max = ( ( double )( p * n + 1 - id * n - i ) * a   
          + ( double )(             id * n + i ) * b ) 
          / ( double )( p * n + 1              );

  heat_part ( n, p, id, x_min, x_max ); // calculations for a single node

  //MPI_Barrier( MPI_COMM_WORLD );

  MPI_Finalize ( );

  return;
}

/******************************************************************************/
// calculations for a single node - subarea
/******************************************************************************/
void heat_part ( int n, int p, int id, double x_min, double x_max )
{
  double cfl;
  double *h;
  double *h_new;
  int i;
  int ierr;
  int j;
  int j_max;
  int j_min;
  double k;
  MPI_Status status;
  double t;
  double t_del;
  double t_max;
  double t_min;
  int tag;
  double wtime;
  double *x;
  double x_del;

  h = ( double * ) malloc ( ( n + 2 ) * sizeof ( double ) ); // results for t_i
  h_new = ( double * ) malloc ( ( n + 2 ) * sizeof ( double ) ); // results for t_i+1
  x = ( double * ) malloc ( ( n + 2 ) * sizeof ( double ) ); // coordinate

  k = 0.002 / ( double ) p; // thermal conductivity

  j_min = 0; // indexes of time steps - min max
  j_max = 100;
  t_min = 0.0; // moments of time - min i max
  t_max = 10.0;
  t_del = ( t_max - t_min ) / ( double ) ( j_max - j_min ); // time step Delta t

  x_del = ( x_max - x_min ) / ( double ) ( n + 1 ); // space between points
  for ( i = 0; i <= n + 1; i++ )
  {
    x[i] = ( ( double ) (         i ) * x_max   
           + ( double ) ( n + 1 - i ) * x_min ) 
           / ( double ) ( n + 1     );
  }

  // setting initial condition
  for ( i = 0; i <= n + 1; i++ )
  {
    h[i] = 95.0;
  }

  wtime = MPI_Wtime ( ); //beginning of time measurement

  for ( j = 1; j <= j_max; j++ )
  {

    // exchanging information with neighbour nodes
    tag = 1;

    if ( id < p - 1 )
    {
      MPI_Send ( &h[n], 1, MPI_DOUBLE, id+1, tag, MPI_COMM_WORLD );
    }

    if ( 0 < id )
    {
      MPI_Recv ( &h[0], 1, MPI_DOUBLE, id-1, tag, MPI_COMM_WORLD, &status );
    }

    tag = 2;

    if ( 0 < id )
    {
      MPI_Send ( &h[1], 1, MPI_DOUBLE, id-1, tag, MPI_COMM_WORLD );
    }

    if ( id < p - 1 )
    {
      MPI_Recv ( &h[n+1], 1, MPI_DOUBLE, id+1, tag, MPI_COMM_WORLD, &status );  
    }


    // implementation of differential formula
    for ( i = 1; i <= n; i++ )
    {
      h_new[i] = h[i] + t_del * ( 
        k * ( h[i-1] - 2.0 * h[i] + h[i+1] ) / x_del / x_del 
        + 2.0 * sin ( x[i] * t ) );
    }

    // new time step
    t = ( ( double ) ( j - j_min ) * t_max   
            + ( double ) ( j_max - j         ) * t_min ) 
            / ( double ) ( j_max     - j_min );

    // preparing for the next time step
    for ( i = 1; i < n + 1; i++ )
    {
      h[i] = h_new[i];
    }

    // boundary condition
    if ( 0 == id ) h[0] = 100.0 + 10.0 * sin ( t );
    if ( id == p - 1 ) h[n+1] = 75;

  }

  // final exchange of information with neighboring nodes
  tag = 11;
  
  if ( id < p - 1 ) {
    MPI_Send ( &h[n], 1, MPI_DOUBLE, id+1, tag, MPI_COMM_WORLD );
  }
  
  if ( 0 < id ) {
    MPI_Recv ( &h[0], 1, MPI_DOUBLE, id-1, tag, MPI_COMM_WORLD, &status );
  }
  
  tag = 12;
  
  if ( 0 < id ) {
    MPI_Send ( &h[1], 1, MPI_DOUBLE, id-1, tag, MPI_COMM_WORLD );
  }
  
  if ( id < p - 1 ) {
    MPI_Recv ( &h[n+1], 1, MPI_DOUBLE, id+1, tag, MPI_COMM_WORLD, &status );
  }
  
  wtime = MPI_Wtime ( ) - wtime;

  if ( id == 0 )
  {
    printf ( "\n" );
    printf ( "  Wall clock elapsed seconds = %f\n", wtime );
  }
  
  int number;


    if(id>0) {
    
    MPI_Recv ( &number, 1, MPI_INT, id-1, tag, MPI_COMM_WORLD, &status );   
  }

    // print results
  
  printf ( "%2d  T= %f\n", id, t );
  printf ( "%2d  X= ", id );
  for ( i = 0; i <= n + 1; i++ )
  {
    printf ( "%7.2f", x[i] );
  }
  printf ( "\n" );
  printf ( "%2d  H= ", id );
  for ( i = 0; i <= n + 1; i++ )
  {
    printf ( "%7.2f", h[i] );
  }
  printf ( "\n" );
  
    if(id<p-1) MPI_Send ( &number, 1, MPI_INT, id+1, tag, MPI_COMM_WORLD );

  free ( h );
  free ( h_new );
  free ( x );

  return;
}
