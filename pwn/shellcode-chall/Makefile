all: main debug

main: main.o
	gcc main.c -o packshell -fno-stack-protector -z execstack -Wl,-z,norelro

debug: main.c
	gcc main.c -o packshell_DEBUG -fno-stack-protector -z execstack -g -Wl,-z,norelro
