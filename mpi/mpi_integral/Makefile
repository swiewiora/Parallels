# compiler c
CCOMP = /usr/lib64/openmpi/bin/mpicc

# linker
LINK = /usr/lib64/openmpi/bin/mpicc

# MPI executor
MPI_run = /usr/lib64/openmpi/bin/mpiexec

# optimization settings
# version for debugging
# OPT = -g -DDEBUG -p
# version optimized for time measurement
OPT = -O3 -fopenmp 

# libraries
LIB = -lm

#commands and dependencies
all: MPI_integral run 

MPI_integral: MPI_integral.o
	$(LINK) $(OPT) MPI_integral.o -o MPI_integral $(LIB)

MPI_integral.o: MPI_integral.c
	$(CCOMP) -c $(OPT) MPI_integral.c $(INC)

run: MPI_integral
	$(MPI_run) -np 1 MPI_integral

clean:
	rm -f *.o
