# compiler c
CCOMP = mpicc

# linker
LOADER = mpicc

MPI_run = mpiexec

# optimization settings
# version for debugging
OPT = -g -DDEBUG
# version optimized for time measurement
# OPT = -O3

# libraries
LIB = -lm

# commands and dependencies

#all: MPI_simple run 

run_simple: MPI_simple
	$(MPI_run) -np 10 MPI_simple
MPI_simple: MPI_simple.o
	$(LOADER) $(OPT) MPI_simple.o -o MPI_simple $(LIB)
MPI_simple.o: MPI_simple.c 
	$(CCOMP) -c $(OPT) MPI_simple.c

run_structure: MPI_simple
	$(MPI_run) -np 10 MPI_simple
MPI_structure: MPI_structure.o
	$(LOADER) $(OPT) MPI_structure.o -o MPI_structure $(LIB)
MPI_structure.o: MPI_structure.c 
	$(CCOMP) -c $(OPT) MPI_structure.c

run_relay: MPI_relay
	$(MPI_run) -np 10 MPI_relay
MPI_relay: MPI_relay.o
	$(LOADER) $(OPT) MPI_relay.o -o MPI_relay $(LIB)
MPI_relay.o: MPI_relay.c 
	$(CCOMP) -c $(OPT) MPI_relay.c

run_relay_closed: MPI_relay_closed
	$(MPI_run) -np 10 MPI_relay_closed
MPI_relay_closed: MPI_relay_closed.o
	$(LOADER) $(OPT) MPI_relay_closed.o -o MPI_relay_closed $(LIB)
MPI_relay_closed.o: MPI_relay_closed.c 
	$(CCOMP) -c $(OPT) MPI_relay_closed.c

clean:
	rm -f *.o
