#include <stdio.h>
#include <stdlib.h>
#include "menuInGame.h"
void clearScreen() {
    // Cette fonction dépend du système d'exploitation
    // Sur Windows, utilisez "cls"
    // Sur Unix/Linux/Mac, utilisez "clear"
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void saveGame(){
	printf("ici ça save de malade\n");
	exit(0);
}

void leaveGame(){
	exit(0);
}
void menuInGame(){
    clearScreen();
    printf("=========================================\n");
    printf("|            Menu En jeu                |\n");
    printf("=========================================\n");
    printf("| 1. Sauvegarder                        |\n");
    printf("| 2. Quitter                            |\n");
    printf("=========================================\n");
    printf("Veuillez choisir une option : ");

	int choice;
	scanf("%d", &choice);
	switch (choice) {
		case 1 :
			saveGame();
			break;
		default :
			exit(0);

	}
}
