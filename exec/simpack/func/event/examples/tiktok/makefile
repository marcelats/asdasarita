#
# Sim++ version 1.0 is the property of Paul A. Fishwick and Robert M. Cubert.
# copyright (c) 1995; see license in the root directory of the distribution.
#
# makefile for examples/tiktok (formerly ticktock in clock directory)

	     PGM = tiktok

	    INCL = ../../include                # where to find sim++ *.h
	     OLB = ../../olb                    # where to find sim++ *.o

	COMPILER = g++ -I$(INCL) -c -o
	  LINKER = g++ -o


# enumerate sim++ object modules:

	 MAIN_1 = $(OLB)/event.o $(OLB)/facility.o $(OLB)/flist.o $(OLB)/future.o
	 MAIN_2 = $(OLB)/service.o $(OLB)/token.o $(OLB)/util.o $(OLB)/estatus.o
	 MAIN_OBJ = $(MAIN_1) $(MAIN_2)

	 CAPI_OBJ = $(OLB)/capifac.o $(OLB)/capifut.o $(OLB)/capiran.o

	 VLIST_1 = $(OLB)/vlist.o
	 VLIST_2 = $(OLB)/calendar.o $(OLB)/heap.o $(OLB)/linked.o $(OLB)/leftist.o
	 VLIST_OBJ = $(VLIST_1) $(VLIST_2)

# link


$(PGM): $(PGM).o $(MAIN_OBJ) $(CAPI_OBJ) $(VLIST_OBJ)
	@echo 'command line to link $(PGM) is too wide for screen, so state it'
	@echo 'below on several lines for your information:'
	@echo '  $(LINKER) $(PGM) $(PGM).o'
	@echo '  $(MAIN_1)'
	@echo '  $(MAIN_2)'
	@echo '  $(CAPI_OBJ)'
	@echo '  $(VLIST_1)'
	@echo '  $(VLIST_2)'
	@echo '  -lm'
	@echo ' '
	$(LINKER) $(PGM) $(PGM).o $(MAIN_OBJ) $(CAPI_OBJ) $(VLIST_OBJ) -lm
	@echo ' '

# compile $(PGM)

$(PGM).o: $(PGM).C
	@echo ' '
	@echo '/////////////////////////////////////////////////////////'
	@echo '//// Sim++ version 1.0 is the property of            ////'
	@echo '//// Paul A. Fishwick and Robert M. Cubert           ////'
	@echo '//// - - - - - - - - - - - - - - - - - - - - - - - - ////'
	@echo '//// copyright (c) 1995; see license in the root     ////'
	@echo '//// directory of the distribution.                  ////'
	@echo '/////////////////////////////////////////////////////////'
	@echo ' '
	@echo 'Compile $(PGM) example program:'
	$(COMPILER) $(PGM).o $(PGM).C
	@echo ' '

