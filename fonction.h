#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXROOM 20
#define MAX_NAME_LENGTH 5

typedef struct {
    int x;
    int y;
} Coordinates;

typedef struct {
    Coordinates position;
    int DoorIndex;
    int NextRoomIndex;
} Door;

typedef struct {
    int l;
    int L;
    char** Tab2D;
    Door TabDoor[4];
    Door* TabConnectedDoor[4];
    int roomIndex;
} Room;

typedef struct {
    char Name[MAX_NAME_LENGTH];
    float Hp;
    float Atk;
    Coordinates Position;
    char skin;
    Room* room;
    float Exp;
} Player;

typedef struct {
    char skin;
    float Hp;
    float Atk;
    Coordinates Position;
} Mob;

Mob BuildMob();
Player BuildPlayer();
int GenerateNumberOfRoom();
Room CreateRoom();
Room CreateFirstRoom();
void PrintfRoom(Player* P1);
void GetMiddle(int* x, int* y, Room room);
Door findDoor(Player* P1);
void roomCreationInGame(Player* P1, Room** World, int cpt);
void doorInteraction(Player* P1, Room** World, int cpt);
void Travel(Player* P1, Room** World, int* cpt);

#endif
