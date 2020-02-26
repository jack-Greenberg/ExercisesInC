util.o: util.c util.h
	gcc -c util.c

trout.o: trout.c trout.h
	gcc -c trout.c

main.o: main.c trout.o util.o
	gcc -c main.c

trout: main.o
	gcc -o trout main.o trout.o util.o -Wall

clean:
	rm *.o trout
