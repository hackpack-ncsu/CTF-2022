main: main.o
	gcc main.o -o packshell -fno-stack-protector

debug: main.o
	gcc main.o -o packshell -fno-stack-protector -g

main_obj: main.c
	gcc -c main.c
