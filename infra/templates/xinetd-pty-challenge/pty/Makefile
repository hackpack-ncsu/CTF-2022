# (This entire directory subtree ripped from the source code 
# published with Advanced Programming in the UNIX Environment, 2nd Ed.)
#-----------------------------------------------------------------------

# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

LDDIR=-L./lib
TEMPFILES=core core.* *.o temp.* *.out typescript*
PROGS =	pty

all:		pty

loop.o:		loop.c

driver.o:	driver.c

main.o:		main.c

pty:		main.o loop.o driver.o libapue
		gcc -static -o pty main.o loop.o driver.o $(LDDIR) -lapue

libapue:
	(cd lib/; make)

clean:
	rm -f ${PROGS} ${TEMPFILES} *.o
