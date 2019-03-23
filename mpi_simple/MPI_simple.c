#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <unistd.h>
#include <limits.h>

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag, i; 
  MPI_Status status[3];
  
  char hostname[HOST_NAME_MAX];
	int length = HOST_NAME_MAX;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  gethostname(hostname, HOST_NAME_MAX);
  
  if(size>1){
    
    if( rank != 0 ){ 
    	dest=0; tag=0;
      MPI_Send (&length, 1, MPI_INT, 0, 1, MPI_COMM_WORLD); 
      MPI_Send (hostname, length+1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
      
    } else {
    
      for( i=1; i<size; i++ ) { 
				MPI_Recv (&length, 2, MPI_INT, i, 1, MPI_COMM_WORLD, &status[0]);
        char* rec_buf;
        rec_buf = (char *) malloc(length+1);
        MPI_Recv (rec_buf, length+1, MPI_CHAR, i, 1, MPI_COMM_WORLD, &status[1]);
        printf("Host: %s\n", rec_buf);
        free(rec_buf);
      }
    }
  }
  else{
		printf("Single process rank: %d (no messages)\n", rank);
  }

  
  MPI_Finalize(); 
  
  return(0);

}

