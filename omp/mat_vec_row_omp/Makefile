# compiler c
CCOMP = gcc

# linker
LOADER = gcc

# optimization settings
# version for debugging
# OPT = -g -DDEBUG -p
# version optimized for time measurement
# OPT = -O3 -fopenmp -p
OPT = -O3  -fopenmp -m64
#OPT = -O2 -parallel -opt-mem-bandwidth1

# headers
#INC = -I../common/measure_time

# libraries
#LIB = -L../common/measure_time -lm
#LIB = -L/opt/intel//mkl/8.1/lib/em64t -lmkl_em64t
#LIB = -L/opt/intel//mkl/8.1/lib/32 -lmkl_ia32
#LIB = -L/opt/intel/mkl/10.1.0.015/lib/em64t/ -lmkl -lguide -lpthread

# zaleznosci i komendy
exec: exec.o mat_vec.o measure_time.o
	$(LOADER) $(OPT) exec.o mat_vec.o measure_time.o -o exec $(LIB)

exec.o: exec.c measure_time.h
	$(CCOMP) -c $(OPT) exec.c $(INC)

mat_vec.o: mat_vec.c
	$(CCOMP) -c $(OPT) mat_vec.c

measure_time.o: measure_time.c measure_time.h
	$(CCOMP) -c $(OPT) measure_time.c

clean:
	rm -f *.o
