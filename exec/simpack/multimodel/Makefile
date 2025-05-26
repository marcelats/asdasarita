QUEUING = ../func/queuing/queuing.o
LIBS = -lcurses -ltermcap -lm
MATHLIB = -lm

all: combined bwater
combined: combined.c
	cc -o combined combined.c $(QUEUING) $(LIBS)
bwater: bwater.c
	cc -o bwater bwater.c $(MATHLIB)
clean:	
	rm -f combined combined2 bwater *.o

