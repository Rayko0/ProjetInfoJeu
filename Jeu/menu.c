#include <stdio.h>
#include <stdlib.h>
#include "menuInGame.h"
#include "fonction.h"
#include "menu.h"

void nouvellePartie(){
    srand(time(NULL));
    printf("\033c");
    int NumberOfRoom = GenerateNumberOfRoom();
    int nbdoor = NumberOfRoom -1;
    printf("Nombre de salle dans la partie : %d\n", NumberOfRoom);
    World* world = CreateWorld(NumberOfRoom);

    Room* room = CreateFirstRoom(&nbdoor);
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
    //define the position of the room in the map (we always save the top left corner)
    room->position.x = x-room->size.x/2;
    room->position.y = y-room->size.y/2;
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
    clearScreen();
    int verif;
    printf("=========================================\n");
    printf("|            Menu Principal             |\n");
    printf("=========================================\n");
    printf("| 1. Nouvelle Partie                    |\n");
    printf("| 2. Charger Partie                     |\n");
    printf("| 3. Quitter                            |\n");
    printf("=========================================\n");
    printf("Veuillez choisir une option : ");
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
