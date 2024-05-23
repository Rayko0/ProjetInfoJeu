#include "menuInGame.h"
#include "fonction.h"
#include "menu.h"
#include <unistd.h>
#include <time.h>

void decrement_time(int *minutes) {
    if (*minutes > 0) {
        (*minutes)--;
    } else {
        // Temps écoulé
        *minutes = 0;
    }
}

void *timer_thread(void *arg) {
    int *minutes = (int *)arg;

    while (*minutes > 0) {
        sleep(60); // Attendre 1 minute
        decrement_time(minutes);
        printf("Time left: %d minutes\n", *minutes);
    }

    printf("Time's up!\n");
    return NULL;
}


void nouvellePartie(){
    srand(time(NULL));
    int time_remaining = 3;
    printf("\033c");
    int NumberOfRoom = GenerateNumberOfRoom();
    printf("Nombre de salle dans la partie : %d\n", NumberOfRoom);
    World* world = CreateWorld(NumberOfRoom);
    
    Room* room = CreateFirstRoom(world);
    //add the room to the array
    world->rooms[0] = room;
    
    Player* player;
    player = BuildPlayer();
    player->room= world->rooms[0]; 
    int x = 0, y =0;
    //find the coordinates of the player (define them in the middle of the map)
    GetMiddle(&x,&y,world->size);
    //change the player coordinates
    player->Position.x=x;
    player->Position.y=y;
    //copy the room in the map
    AddRoomToWorld(world, room);

    world->cnt;
    pthread_t timer_tid;
    pthread_create(&timer_tid, NULL, timer_thread, &time_remaining);
    while(1){
        Travel(player,world);
    }
}

void chargerPartie(){
    FILE *file = fopen("savegame.bin", "rb");
if (file == NULL) {
    perror("Erreur lors de l'ouverture du fichier");
    exit(1);
}

GameState loadedGameState;
size_t read = fread(&loadedGameState, sizeof(GameState), 1, file);
if (read != 1) {
    perror("Erreur lors de la lecture du fichier");
}
fclose(file);

// Utilisez les données chargées
printf("Position du joueur: (%d, %d)\n",loadedGameState.player.Position.x, loadedGameState.player.Position.y);
printf("Adresses player : %p / world : %p\n", &loadedGameState.player, &(loadedGameState.world));
int e;
scanf("%d",&e);
while(1){
        Travel(&(loadedGameState.player),&(loadedGameState.world));
    }

}

void menu(){
    int choice;
    int verif;

    do{
	printf("\033c");
    
	printf("\033[33m┌"
	"─────────────────────────"
	"┐\033[0m"
	"\n");
	printf("\033[33m│  Menu                   │\033[0m\n"
	"\033[33m│\033[0m  Nouvelle partie : 1    \033[33m│\033[0m\n"
	"\033[33m│\033[0m  Charger une partie : 2 \033[33m│\033[0m\n"
	"\033[33m│\033[0m  Quitter : 0            \033[33m│\033[0m\n");
	printf("\033[33m└"
	"─────────────────────────"
	"┘\033[0m"
	"\n\n");
	
	verif=scanf("%d", &choice);
        vide_buffer();

    } while (choice!=1 && choice!=0 && choice!=2 && verif !=-1);
    switch (choice) {
        case 1:
            nouvellePartie();
            break;
        case 2:
            chargerPartie();
            break;
        default:
            exit(0);
    }
}
