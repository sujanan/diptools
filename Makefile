CC=gcc
CFLAG=-Wall -g

PROG=dip
LIBS=-lm

all: $(PROG)

dip: dip.o histogram.o
	$(CC) $(CFLAGS) -o dip dip.o histogram.o $(LIBS)

dip.o: stb_image.h dip.h

histogram.o: histogram.h dip.h

clean:
	rm -rf *.o $(PROG)
