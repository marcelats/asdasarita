QUEUING = ../../func/queuing/queuing.o
LIBS = -lcurses -ltermcap -lm
MATHLIB = -lm

markov: markov.c
	cc -o markov markov.c  $(QUEUING) $(LIBS)
clean:
	rm -f markov *.o


