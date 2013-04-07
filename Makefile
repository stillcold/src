#exec : main.o
#	gcc -o exec main.o
#main.o : 0110-fprintf.c
#	gcc -o main.o -c 0110-fprintf.c
#clean : rm exec main.o
#
#include ./c/Makefile.config1
#include ./c/Makefile.config2
#include ./c/Makefile.common
#include ./c/Makefile.rules
#include ./c/Makefile
#cd c/
#	make
#all: ${PROGS}
#
#${PROGS} : FORCE
# below is what really matters.
.PHONY : all clean install
CSOURCEDIR = ./c/
all: FORCE
	cd ${CSOURCEDIR};\
	make
clean: FORCE
	cd ${CSOURCEDIR};\
	make clean

install: FORCE
	cd ${CSOURCEDIR};\
	make install
FORCE:
