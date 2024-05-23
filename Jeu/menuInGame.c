#include <stdio.h>
#include <stdlib.h>
#include "menuInGame.h"

void vide_buffer(){
    while (getchar()!='\n'){
    }
}

void saveGame(GameState GameState){
	FILE *file;
file = fopen("savegame.bin", "wb");
if (file == NULL) {
    perror("Erreur lors de l'ouverture du fichier");
    exit(1);
}
size_t written = fwrite(&GameState, sizeof(GameState), 1, file);
if (written != 1) {
    perror("Erreur lors de l'écriture dans le fichier");
}
fclose(file);
	exit(0);
}

void leaveGame(){
	exit(0);
}

void menuInGame(GameState GameState){

	int choice;
	int verif;
	do{
		printf("\033c");
    
    		printf("\033[33m┌"
    		"───────────────────"
    		"┐\033[0m"
    		"\n");
    		printf("\033[33m│  Menu en jeu      │\033[0m\n"
    		"\033[33m│\033[0m  Sauvergarder : 1 \033[33m│\033[0m\n"
    		"\033[33m│\033[0m  Quitter : 0      \033[33m│\033[0m\n");
    		printf("\033[33m└"
    		"───────────────────"
    		"┘\033[0m"
    		"\n\n");
		printf("Veuillez choisir une option : ");

		verif=scanf("%d", &choice);
        	vide_buffer();
	} while (choice!=1 && choice!=0 && verif !=-1);

	switch (choice) {
		case 1 :
			saveGame(GameState);
			break;
		default :
			exit(0);

	}
}
