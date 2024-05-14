#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fonction.h"

#define MAXROOM 20
#define MAX_NAME_LENGTH 5

int main() {
    srand(time(NULL));
    printf("\033c");
    int NumberOfRoom = GenerateNumberOfRoom();
    printf("Nombre de salle dans la partie : %d\n", NumberOfRoom);
    Room* World = malloc(sizeof(Room)*NumberOfRoom);
    Room room;
    room = CreateFirstRoom();
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


    return 0;
}
