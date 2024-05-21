#include "menuInGame.h"
#include "fonction.h"
#include "menu.h"

void nouvellePartie(){
    srand(time(NULL));
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

    int cpt=0;
    while(1){
        Travel(player,world,&cpt);
    }
}

void chargerPartie(){
    printf("en construction\n");
}

void menu(){
    printf("Nouvelle partie : 1\n");
    printf("Charger une partie : 2\n");
    printf("Quitter : 0\n");
    int choice;
    scanf("%d",&choice);
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
