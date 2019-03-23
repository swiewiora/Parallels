# compiler c
CCOMP = mpicc

# linker
LINK = mpicc

MPIRUN = mpiexec 

# optimization settings
# version for debugging
# OPT = -g -DDEBUG -p
# version optimized for time measurement
# OPT = -O3 -fopenmp -p

LIB = -lm

# commands and dependencies

pi: pi.o
	$(LINK) $(OPT) pi.o -o pi $(LIB)

pi.o: pi.c
	$(CCOMP) -c $(OPT) pi.c $(INC)

run:
	$(MPIRUN) -np 8 ./pi

clean:
	rm -f *.o
