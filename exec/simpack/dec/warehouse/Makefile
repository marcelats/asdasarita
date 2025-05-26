QUEUING = ../../func/queuing/queuing.o
LIBS = -lcurses -ltermcap -lm

warehouse: warehouse.c
	cc -o warehouse warehouse.c $(QUEUING) $(LIBS)
clean:
	rm -f warehouse *.o

