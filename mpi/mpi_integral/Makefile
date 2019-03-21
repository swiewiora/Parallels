# compiler c
CCOMP = /usr/lib64/openmpi/bin/mpicc

# linker
LINK = /usr/lib64/openmpi/bin/mpicc

# MPI executor
MPI_run = /usr/lib64/openmpi/bin/mpiexec

# optimisation settings
# version for debugging
# OPT = -g -DDEBUG -p
# version optimized for time measurement
OPT = -O3 -fopenmp 

# headers
#INC = -I../measure_time

# libraries
#LIB = -L../measure_time -lm
LIB = -lm

#commands and dependencies
all: MPI_integral run 

MPI_integral: MPI_integral.o measure_time.o
	$(LINK) $(OPT) MPI_integral.o measure_time.o -o MPI_integral $(LIB)

MPI_integral.o: MPI_integral.c  measure_time.h
	$(CCOMP) -c $(OPT) MPI_integral.c $(INC)

measure_time.o: measure_time.c measure_time.h
	$(CCOMP) -c $(OPT) measure_time.c

run: MPI_integral
	$(MPI_run) -np 1 MPI_integral

clean:
	rm -f *.o
