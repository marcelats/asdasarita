#  X Project Makefile
#
#  Brian Harrington
#  org: 6/ 2/90
#  ver: 12/01/91
#
#  modified 950728 by robert cubert as part of SimPack3 release
#  including Sim++ version 1.0: see Readme.

	     INCL= ../../../../queuing                   # to find queuing.h
          SOBJECT= ../../../../queuing/queuing.o
	COMPILER = cc -I$(INCL) -c -o
          LINKER = cc -o 

# Do NOT change compiler to gcc!  It will create code that compiles and links
# but runs incorrectly.

CC=     cc
RM=     /bin/rm -f
#HEADERS=        modeller.h

SLIBS=  -lcurses -ltermcap -lm


#
default: model

all: model examp1 examp2 examp3 big_test combined1
#
# Create simpack test programs
#

model: model.o
	$(LINKER) model model.o $(SOBJECT) $(SLIBS)

model.o: model.c
	$(COMPILER) model.o model.c

examp1: examp1.o
	$(LINKER) examp1 examp1.o $(SOBJECT) $(SLIBS)

examp1.o: examp1.c
	$(COMPILER) examp1.o examp1.c

examp2: examp2.o
	$(LINKER) examp2 examp2.o $(SOBJECT) $(SLIBS)

examp2.o: examp2.c
	$(COMPILER) examp2.o examp2.c

examp3: examp3.o
	$(LINKER) examp3 examp3.o $(SOBJECT) $(SLIBS)

examp3.o: examp3.c
	$(COMPILER) examp3.o examp3.c

big_test: big_test.o
	$(LINKER) big_test big_test.o $(SOBJECT) $(SLIBS)

big_test.o: big_test.c
	$(COMPILER) big_test.o big_test.c

combined1:  cont1.o combined1.o
	$(LINKER) combined1 cont1.o combined1.o $(SOBJECT) $(SLIBS)

combined1.o: combined1.c
	$(COMPILER) combined1.o combined1.c

cont1.o: cont1.c
	$(COMPILER) cont1.o cont1.c

clean:
	$(RM) *.o model examp1 examp2 examp3 big_test combined1


