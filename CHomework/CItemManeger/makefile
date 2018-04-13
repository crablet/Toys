main.exe: main.o Menu.o Items.o
	gcc -o main.exe main.o Menu.o Items.o

Menu.o: Menu.c Menu.o
	gcc -c -w Menu.c

Items.o: Items.c Items.h
	gcc -c -w Items.c

main.o: main.c
	gcc -c main.c