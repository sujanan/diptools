CC=gcc
CFLAG=-Wall -g

PROG=dip
LIBS=-lm

all: $(PROG)

dip: dip.o
	$(CC) $(CFLAGS) -o dip dip.o $(LIBS)

dip.o: stb_image.h dip.h

clean:
	rm -rf *.o $(PROG)
