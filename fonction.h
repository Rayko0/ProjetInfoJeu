#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define MAXROOM 20
#define MAX_NAME_LENGTH 10
#define MAX_WORLD_SIZE 1024
#define CameraRangeX 15
#define CameraRangeY 40


void AddRoomToWorld(World* world, Room* room);
bool isSpaceFree(World* world, Coordinates pos, int k);
void AddDoorToRoom(World* world, Room* r, int ObDoor);
void AddRoomToWorld(World* world, Room* room);
World* CreateWorld(int NumberOfRoom);
Mob BuildMob();
Player* BuildPlayer();
int GenerateNumberOfRoom();
Room* CreateRoom(World* world);
Room* CreateFirstRoom(World* world);
void PrintMessage(char* message);
void PrintfRoom(Player* P1, World* world);
void GetMiddle(int* x, int* y, Coordinates room);
int findDoor(Player* P1, World * world);
void addToInventory(Player *P1, Room * room);
void roomCreationInGame(Player* P1, World* wrld);
void doorInteraction(Player* P1, World* World, int dir);
void combat(Player *player, Mob *mob,World* world);

void Travel(Player* P1, World* World);

#endif
