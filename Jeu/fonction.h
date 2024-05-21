#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXROOM 20
#define MAX_NAME_LENGTH 7
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
    Coordinates position;
    int DoorIndex;
    int RoomIndex;
    int NextRoomIndex;
} Door;

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
    Room** rooms;
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

void wait_seconds(double seconds);
void vide_buffer();
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
void combat(Player *player, Mob *mob,World* world);
void addToInventory(Player *P1, Room * room);
void Travel(Player* P1, World* World, int* cpt);

#endif
