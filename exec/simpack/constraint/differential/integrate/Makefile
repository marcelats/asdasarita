LIBS = -lm

all: conte contrk lorenz silnikov vibration
conte: conte.c
	cc -o conte conte.c $(LIBS)
contrk: contrk.c
	cc -o contrk contrk.c $(LIBS)
lorenz: lorenz.c
	cc -o lorenz lorenz.c $(LIBS)
lotka: lotka.c
	cc -o lotka lotka.c $(LIBS)
silnikov: silnikov.c
	cc -o silnikov silnikov.c $(LIBS)
vibration: vibration.c
	cc -o vibration vibration.c  $(LIBS)

clean: 
	rm -f conte contrk lorenz silnikov vibration *.o
