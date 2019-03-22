NAME = sort

CC = gcc
LD = gcc
AR = ar -ru

CFL = -O -fopenmp
LDFL = -O -fopenmp
LIB = -L. -sort_lib
INC = -I.

sort: sort.o  merge_sort.o sort_lib.a
	$(LD) $(LDFL) -o $(NAME) sort.o merge_sort.o $(LIB)

sort.o: sort.c sort_procedures.h
	$(CC) $(CFL) -c sort.c $(INC)

sort_lib.a: sort_procedures.o
	$(AR) sort_lib.a sort_procedures.o

sort_procedures.o: sort_procedures.c sort_procedures.h
	$(CC) $(CFL) -c sort_procedures.c $(INC)

merge_sort.o: merge_sort.c 
	$(CC) $(CFL) -c merge_sort.c $(INC)

clean:
	rm *.o $(NAME)