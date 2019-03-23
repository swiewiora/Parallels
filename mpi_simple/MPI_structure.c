#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

struct structure {
	int integer;
	double real;
	char word[4];
} data = {1, 3.14, "TEST"};

int main(int argc, char** argv) {
	
	
  MPI_Init(&argc, &argv);
  
  MPI_Status status;
  int size, package_size, position;
  char buffer[100], buffer_recv[100];
 
	MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &size);
	package_size = size;
	MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &size);
	package_size += size;
	MPI_Pack_size(4, MPI_CHAR, MPI_COMM_WORLD, &size);
	package_size += size;

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	if (world_rank == 0) {
    position = 0;
    MPI_Pack(&data.integer, 1, MPI_INT, buffer, package_size, &position, MPI_COMM_WORLD);
		MPI_Pack(&data.real, 1, MPI_DOUBLE, buffer, package_size, &position, MPI_COMM_WORLD);
		MPI_Pack(&data.word, 4, MPI_CHAR, buffer, package_size, &position, MPI_COMM_WORLD);
	}
	
  if (world_rank != 0) {
  	position = 0;
    MPI_Recv (buffer, 100, MPI_PACKED, world_rank - 1, 0, MPI_COMM_WORLD, &status);
    MPI_Unpack(buffer, 100, &position, &data.integer, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Unpack(buffer, 100, &position, &data.real, 1, MPI_DOUBLE, MPI_COMM_WORLD);
    MPI_Unpack(buffer, 100, &position, &data.word, 4, MPI_CHAR, MPI_COMM_WORLD);
    printf("Process %d received from process %d structure:\n", world_rank, world_rank - 1);
    printf("\tinteger number: %d\n\treal number: %.2lf\n\tword: %s\n", data.integer, data.real, data.word);
  }
  
  if (world_rank < world_size - 1) {
  MPI_Send(buffer, 100, MPI_PACKED, world_rank + 1, 0, MPI_COMM_WORLD);
  
  printf("Process %d sent to process %d structure:\n", world_rank,
           world_rank + 1);
  printf("\tinteger number: %d\n\treal number: %.2lf\n\tword: %s\n", data.integer, data.real, data.word);
  }
  
  MPI_Finalize();
  return;
}
