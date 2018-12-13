.SUFFIXES: .c

all:
	gcc listIPDNS.c -o listIPDNS -lm

clean:
	/bin/rm -f *.o *~ *.dat core listIPDNS
