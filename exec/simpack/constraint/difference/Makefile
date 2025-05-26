LIBS = -lm

all: bifurc  log1a log1b log2
bifurc: bifurc.c
	cc -o bifurc bifurc.c $(LIBS)
log1a : log1a.c
	cc -o log1a log1a.c $(LIBS) 
log1b : log1b.c
	cc -o log1b log1b.c $(LIBS) 
log2 : log2.c
	cc -o log2 log2.c $(LIBS) 
clean:
	rm -f *.o bifurc diff1 log1 log2

