#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXROOM 20

typedef struct { // Create the type Room
    int Dimension[2]; // Dimension l and L of the room
    char** Tab2D; // tableau 2d de la salle
    char* Doors; // Coordinates of all the doors in the room
} Room;

void MallocNumberOfRoom(int** NumberOfRoom){ // Allocates memory for pointer to NumberOfRoom
    *NumberOfRoom = malloc(sizeof(int));
    if (*NumberOfRoom == NULL){ // Check that the NumberOfRoom memory is not empty
        printf("Erreur allocation de mémoire nombre de salles\n");
        exit(1);
    }
}

void GenerateNumberOfRoom(int* p){ // Generate a random number of room between 10 and MAXROOM in a pointer to an integer
    *p = rand() % (MAXROOM+1) + 10;
}



void CreateRoom(Room* r) { // Create the dimension of the room randomly
    int l, L;
    L = rand() % 8 + 3; // Generate a random length between 3 and 10
    l = rand() % 8 + 3; // Generate a random length between 3 and 10
    printf("Longueur : %d\n", L);
    printf("Largeur : %d\n", l);

    r->Dimension[0] = l; // Store dimensions
    r->Dimension[1] = L;

    r->Tab2D = malloc(l * sizeof(char*));
    if (r->Tab2D == NULL) {
        printf("Erreur allocation de mémoire pour les coordonnées\n");
        exit(3);
    }

    for (int i = 0; i < l; i++) { // Allocation de mémoire pour le tableau 2D
        r->Tab2D[i] = malloc(L * sizeof(char));
        if (r->Tab2D[i] == NULL) {
            printf("Erreur allocation de mémoire pour les coordonnées\n");
            exit(1);
        }

        for (int j = 0; j < L; j++) {
            if (i == 0 && j == 0) {
                r->Tab2D[i][j] = '1';
            } else if (i == 0 && j == L - 1) {
                r->Tab2D[i][j] = '2';
            } else if (i == l - 1 && j == 0) {
                r->Tab2D[i][j] = '3';
            } else if (i == l - 1 && j == L - 1) {
                r->Tab2D[i][j] = '4';
            } else if (i == 0 || i == l - 1) {
                r->Tab2D[i][j] = '-';
            } else if (j == 0 || j == L - 1) {
                r->Tab2D[i][j] = '|';
            } else {
                r->Tab2D[i][j] = ' ';
            }
        }
    }
}

void PrintfRoom(Room room){
    for (int i = 0; i < room.Dimension[0]; i++) {
        for (int j = 0; j < room.Dimension[1]; j++) {
            printf("%c", room.Tab2D[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));

    int* NumberOfRoom = NULL;
    MallocNumberOfRoom(&NumberOfRoom);
    GenerateNumberOfRoom(NumberOfRoom);
    printf("Nombre de pièce dans la partie : %d\n", *NumberOfRoom);

    Room room;
    CreateRoom(&room);
    PrintfRoom(room);

    free(NumberOfRoom);
    return 0;
}