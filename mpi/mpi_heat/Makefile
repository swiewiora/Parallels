# compiler c
CCOMP = /usr/lib64/openmpi/bin/mpicc

# linker
LINK = /usr/lib64/openmpi/bin/mpicc

MPIRUN = /usr/lib64/openmpi/bin/mpiexec 

# optimization settings
# version for debugging
# OPT = -g -DDEBUG -p
# version optimized for time measurement
# OPT = -O3 -fopenmp -p

# libraries
LIB = -lm

# commands and dependencies

heat: heat.o
	$(LINK) $(OPT) heat.o -o heat $(LIB)

heat.o: heat.c
	$(CCOMP) -c $(OPT) heat.c $(INC)

run:
	$(MPIRUN) -np 8 ./heat

clean:
	rm -f *.o
