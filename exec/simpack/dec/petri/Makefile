QUEUING = ../../func/queuing/queuing.o
LIBS = -lcurses -ltermcap -lm

petri: petri.c
	cc -o petri petri.c $(QUEUING) $(LIBS)
clean:
	rm -f petri *.o
