#include "menuInGame.h"
#include "fonction.h"
#include "menu.h"
void nouvellePartie(){
    srand(time(NULL));
    printf("\033c");
    int NumberOfRoom = GenerateNumberOfRoom();
    int nbdoor = NumberOfRoom -1;
    printf("Nombre de salle dans la partie : %d\n", NumberOfRoom);
    Room* World = malloc(sizeof(Room)*NumberOfRoom);
    Room room;
    room = CreateFirstRoom(&nbdoor);
    World[0] = room;
    Player player;
    player = BuildPlayer();
    player.room=&World[0];
    int x = 0;
    int y = 0;
    GetMiddle(&x,&y,room);
    //printf("Le milieu de la salle est [%d][%d]\n", y, x);
    room.Tab2D[y][x]=player.skin;
    player.Position.x=x;
    player.Position.y=y;
    int cpt=0;
    PrintfRoom(&player);
    
    do{
        Travel(&player,&World,&cpt);
        PrintfRoom(&player);

    }while (cpt<NumberOfRoom);
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