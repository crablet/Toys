main.exe: main.o Menu.o Items.o
	gcc -o main.exe main.o Menu.o Items.o

Menu.o: Menu.c Menu.o
	gcc -c Menu.c

Items.o: Items.c Items.h
	gcc -c Items.c

main.o: main.c
	gcc -c main.c