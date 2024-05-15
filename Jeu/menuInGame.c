#include "menuInGame.h"
void saveGame(){
	printf("ici ça save de malade\n");
	exit(0);
}

void leaveGame(){
	exit(0);
}
void menuInGame(){
	printf("Sauvegarder et quitter : 1\n");
	printf("Quitter la partie : 0\n");
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