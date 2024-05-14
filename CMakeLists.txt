all: exec

fonction.o : fonction.c fonction.h
	gcc -c fonction.c -o fonction.o
		
main1.o : main1.c fonction.h
	gcc -c main1.c -o main1.o

exec : main1.o fonction.o
	gcc main1.o fonction.o -o exec

clean:
	rm -f *.o
	rm -f exec
