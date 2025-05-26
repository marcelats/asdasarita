# Makefile para SimPack
#

PROG = modelo

#INCLUDE = /root/eclipseWorkspace/ASDA/exec/simpack/func/event/include
INCLUDE = /root/eclipseWorkspace/ASDA/exec/simpack/func/event/include
SRC = /root/eclipseWorkspace/ASDA/exec/simpack/func/event/src
#SRC = /home/mario/simpack/func/event/src
OBJ = $(SRC)/calendar.o $(SRC)/capifac.o $(SRC)/capifut.o $(SRC)/capiran.o \
      $(SRC)/estatus.o $(SRC)/event.o $(SRC)/facility.o $(SRC)/flist.o \
      $(SRC)/future.o $(SRC)/heap.o $(SRC)/leftist.o $(SRC)/linked.o $(SRC)/service.o \
      $(SRC)/token.o $(SRC)/util.o $(SRC)/vlist.o

CPP = g++
CPPFLAGS = -I$(INCLUDE) -Wno-deprecated

all : $(PROG)

$(PROG) : $(PROG).o $(OBJ)
	$(CPP) $(CPPFLAGS) -o $(PROG) $(PROG).o $(OBJ)

clean : $(SRC)/*.o $(PROG).o
	rm $(SRC)/*.o $(PROG).o
