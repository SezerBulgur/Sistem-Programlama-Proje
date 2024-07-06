all: compile link #execute
compile:
	gcc -c -I "./include" ./src/dllist.c -o ./lib/dllist.o
	gcc -c -I "./include" ./src/fields.c -o ./lib/fields.o
	gcc -c -I "./include" ./src/jval.c -o ./lib/jval.o
	gcc -c -I "./include" ./src/jrb.c -o ./lib/jrb.o
	gcc -c -I "./include" ./src/main.c -o ./lib/main.o
link:
	gcc ./lib/dllist.o ./lib/fields.o ./lib/jval.o ./lib/jrb.o ./lib/main.o -o program
#execute:
#	./program giris.dat