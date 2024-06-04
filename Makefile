objfiles = player.o animation.o stage.o key.o vector.o attack.o gametest.o playertype.o

gametest: $(objfiles)
	gcc -o gametest $(objfiles) `pkg-config --cflags --libs sdl2` -lm

%.o:	%.c
	gcc -o $*.o -c $*.c

clean:
	rm gametest $(objfiles)
