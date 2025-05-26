LIBS       = -lcurses -ltermcap -lm
QUEUING = ../../func/queuing/queuing.o

all:		gas1 gas2
gas1:		gas1.c
		cc -o gas1 gas1.c ${LIBS}

gas2:		gas2.c
		cc -o gas2 gas2.c ${QUEUING} ${LIBS}
clean:		
		rm -rf gas1 gas2 *.o
