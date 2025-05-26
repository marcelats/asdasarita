QUEUING = ../queuing/queuing.o
LIBS = -lcurses -ltermcap -lm

all:	block monorail1 monorail2 monorail3
block:  block.c
	cc -o block block.c $(LIBS)
monorail1:  monorail1.c
	cc -o monorail1 monorail1.c $(LIBS)
monorail2:  monorail2.c
	cc -o monorail2 monorail2.c $(LIBS)
monorail3:  monorail3.c
	cc -o monorail3 monorail3.c $(LIBS)
clean:	
	rm -f *.o monorail1 monorail2 monorail3 block
