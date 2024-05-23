all: exec

menuInGame.o : menuInGame.c menuInGame.h
	gcc -c menuInGame.c -o menuInGame.o

fonction.o : fonction.c fonction.h menuInGame.h
	gcc -c fonction.c -o fonction.o
		
menu.o : menu.c menu.h fonction.h menuInGame.h
	gcc -c menu.c -o menu.o

main1.o : main1.c menu.h fonction.h menuInGame.h
	gcc -c main1.c -o main1.o

exec : main1.o menu.o fonction.o menuInGame.o  
	gcc main1.o menu.o fonction.o menuInGame.o -o exec -pthread

clean:
	rm -f *.o
	rm -f exec
