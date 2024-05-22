#ifndef MENUINGAME_H
#define MENUINGAME_H
#include<stdio.h>
#include<stdlib.h>

#define MAXROOM 20
#define MAX_NAME_LENGTH 5
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
   char* skin;
} Item;

typedef struct {
    char* skin;
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
    char*** Tab2D;
    Door TabDoor[4];
    Door* TabConnectedDoor[4];
    int RoomIndex;
    Mob RoomMob;
    Item RoomItem;
} Room;

typedef struct {
    Coordinates size;
    char*** map;
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
    char* skin;
    Room* room;
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
