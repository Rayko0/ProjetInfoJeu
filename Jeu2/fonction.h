#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXROOM 20
#define MAX_NAME_LENGTH 5
#define CameraRangeX 15
#define CameraRangeY 40


typedef struct {
    int x;
    int y;
} Coordinates;



typedef struct {
    Coordinates position;
    int DoorIndex;
    int RoomIndex;
    int NextRoomIndex;
} Door;

typedef struct {
    Coordinates size;
    Coordinates position;
    char*** Tab2D;
    Door TabDoor[4];
    Door* TabConnectedDoor[4];
    int RoomIndex;
} Room;

typedef struct {
    Coordinates size;
    char*** map;
    Room** rooms;
} World;

typedef struct {
    char Name[MAX_NAME_LENGTH];
    float Hp;
    float Atk;
    Coordinates Position;
    char* skin;
    Room* room;
    float Exp;
} Player;

typedef struct {
    char skin;
    float Hp;
    float Atk;
    Coordinates Position;
} Mob;

void AddRoomToWorld(World* world, Room* room);
World* CreateWorld(int NumberOfRoom);
Mob BuildMob();
Player* BuildPlayer();
int GenerateNumberOfRoom();
Room* CreateRoom(int cnt);
Room* CreateFirstRoom();
void PrintfRoom(Player* P1, World* world);
void GetMiddle(int* x, int* y, Coordinates room);
int findDoor(Player* P1);
void roomCreationInGame(Player* P1, World* wrld, int cpt);
void doorInteraction(Player* P1, World* World, int* cnt, int dir);
void Travel(Player* P1, World* World, int* cpt);

#endif
