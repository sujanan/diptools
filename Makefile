CC=gcc
CFLAG=-Wall -g

PROG=diptool
LIBS=-lm

all: $(PROG)

diptool: diptool.o histogram.o
	$(CC) $(CFLAGS) -o diptool diptool.o histogram.o $(LIBS)

diptool.o: stb_image.h diptool.h

histogram.o: histogram.h diptool.h

clean:
	rm -rf *.o $(PROG)
