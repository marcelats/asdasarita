QUEUING = ../../../../queuing/queuing.o
   INCL = ../../../../queuing

gpss:	   	gen main	
gen:		lex.yy.c y.tab.c
main:		main.c 
		cc  -I$(INCL) -o ../gpfiles/gpss main.c $(QUEUING) -ll -lm -lcurses \
                    -ltermcap 
lex.yy.c: 	token.l
		lex token.l
y.tab.c:	parse.y 
		yacc parse.y
clean:	
		rm *.o gpss
