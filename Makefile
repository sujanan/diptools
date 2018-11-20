CC=gcc
CFLAG=-Wall -g

PROG=diptool
LIBS=-lm

all: $(PROG)

diptool: diptool.o read.o
	$(CC) $(CFLAGS) -o diptool diptool.o read.o $(LIBS)

diptool.o: diptool.h

read.o: read.h diptool.h
image.o: image.h stb_image.h
histogram.o: histogram.h image.h

clean:
	rm -rf *.o $(PROG)
