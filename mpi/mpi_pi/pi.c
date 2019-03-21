# include <stdio.h>
# include <math.h>
# include "mpi.h"


int main ( int argc, char *argv[] )
{
    int n, id, numprocs, i;
    double mypi, pi;
    mypi = 0;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);

    if (id == 0) {
        printf("Input accuracy: \n ");
        scanf("%d",&n);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int a = (id) * (n/numprocs + n%numprocs);
    int b = (id+1) * (n/numprocs + n%numprocs);

    printf("thread %d numprocs %d a = %d b = %d\n", id, numprocs, a, b);

    for(i=b; i >= a; i-=2)
        mypi -= 1. / ( ( 2 * i ) + 1 );

    for(i=b-1; i >= a; i-=2)
        mypi += 1. / ( ( 2 * i ) + 1 );

    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
               MPI_COMM_WORLD);
    if (id == 0)
        printf("pi = %.16lf, error: %.16lf\n",
               pi*4, fabs(pi*4 - M_PI));

    MPI_Finalize();
    return 0;
}
