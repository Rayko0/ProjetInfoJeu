#ifndef MENUINGAME_H
#define MENUINGAME_H
#include<stdio.h>
#include<stdlib.h>

#define MAXROOM 20
#define MAX_NAME_LENGTH 10
#define MAX_WORLD_SIZE 1024
#define CameraRangeX 15
#define CameraRangeY 40


typedef struct {
    int x;
    int y;
} Coordinates;

typedef struct {
   Coordinates position;
   int exist;
   int Sword;
   int Heart;
   int Shield;
   int skin;
} Item;

typedef struct {
    int skin;
    int exist;
    float Hp;
    float Atk;
    float Esq;
    float Def;
    Coordinates Position;
} Mob;


typedef struct {
    Coordinates position;
    int DoorIndex;
    int RoomIndex;
    int NextRoomIndex;
} Door;

typedef struct {
    Coordinates size;
    Coordinates position;
    int** Tab2D;
    Door TabDoor[4];
    Door* TabConnectedDoor[4];
    int RoomIndex;
    Mob RoomMob;
    Item RoomItem;
} Room;

typedef struct {
    Coordinates size;
    int** map;
    int NbMax;
    int NbRooms;
    int NbDoors;
    Room** rooms;
    int cnt;
} World;

typedef struct {
    char Name[MAX_NAME_LENGTH];
    float Hp;
    float Atk;
    float Def;
    float Esq;
    Coordinates Position;
    int skin;
    int roomIndex;
    float Exp;
    Item Inventory[4];
    int KillCounter;
    int DeathCounter;
} Player;

typedef struct {
	Player player;
	World world;
	
} GameState;

void vide_buffer();
void saveGame(GameState GameState);
void menuInGame();
#endif
