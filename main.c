#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXROOM 20


typedef struct { // Create the type Room
    int l; // Width of the room
    int L; // Length of the room
    char** Tab2D; // 2-dimensional table of the room
    char* Doors; // Coordinates of all the doors in the room
} Room;

int GenerateNumberOfRoom(){ // Generate a random number of room between 10 and MAXROOM in a pointer to an integer
    int a;
    a = rand() %11 + (MAXROOM-10);
    return a;
}

Room CreateRoom() { // Create the dimension of the room randomly
    int l, L;
    Room r;
    L = rand() % 8 + 3; // Generate a random length between 3 and 10
    l = rand() % 8 + 3; // Generate a random length between 3 and 10
    if (l - L > 2){ // Avoid corridor rooms
        L+=4;
    }
    else if (L - l > 2){
        l+=4;
    }

    r.l = l; // Store dimensions
    r.L = L;

    r.Tab2D = malloc(l * sizeof(char*));
    if (r.Tab2D == NULL) {
        printf("Erreur allocation de mémoire pour les coordonnées\n");
        exit(3);
    }

    for (int i = 0; i < l; i++) { // Allocation de mémoire pour le tableau 2D
        r.Tab2D[i] = malloc(L * sizeof(char));
        if (r.Tab2D[i] == NULL) {
            printf("Erreur allocation de mémoire pour les coordonnées\n");
            exit(1);
        }

        for (int j = 0; j < L; j++) {
            if (i == 0 && j == 0) {
                r.Tab2D[i][j] = '1';
            } else if (i == 0 && j == L - 1) {
                r.Tab2D[i][j] = '2';
            } else if (i == l - 1 && j == 0) {
                r.Tab2D[i][j] = '3';
            } else if (i == l - 1 && j == L - 1) {
                r.Tab2D[i][j] = '4';
            } else if (i == 0 || i == l - 1) {
                r.Tab2D[i][j] = '-';
            } else if (j == 0 || j == L - 1) {
                r.Tab2D[i][j] = '|';
            } else {
                r.Tab2D[i][j] = ' ';
            }
        }
    }
    return r;
}

Room CreateFirstRoom(){
    Room r;
    do {
        r = CreateRoom();
    } while (r.l % 2 == 0 || r.L % 2 ==0);
    return r;
}

void PrintfRoom(Room room){
    printf("Largeur %d\n",room.l);
    printf("Longueur : %d\n", room.L);
    for (int i = 0; i < room.l; i++) {
        for (int j = 0; j < room.L; j++) {
            printf("%c", room.Tab2D[i][j]);
        }
        printf("\n");
    }
}

void GetMiddle(int *x,int *y, Room room){

    *x=room.L/2;
    *y=room.l/2;
}

int main() {
    srand(time(NULL));
    int NumberOfRoom = GenerateNumberOfRoom();
    printf("Nombre de pièce dans la partie : %d\n", NumberOfRoom);
    Room* AllRoom= malloc(sizeof(Room)*NumberOfRoom);

    Room room;
    room=CreateFirstRoom();
    PrintfRoom(room);
    int x=0;
    int y=0;
    GetMiddle(&x,&y,room);
    printf("Le milieu de la salle est [%d][%d]\n", y, x);
    PrintfRoom(room);
    AllRoom[0]=room;
    room.Tab2D[y][x]='&';
    PrintfRoom(room);
    return 0;
}
