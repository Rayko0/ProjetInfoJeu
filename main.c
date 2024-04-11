#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXROOM 20
#define MAX_NAME_LENGTH 5


typedef struct { // Create the type Room
    int l; // Width of the room
    int L; // Length of the room
    char** Tab2D; // 2-dimensional table of the room
    char* Doors; // Coordinates of all the doors in the room
} Room;

typedef struct{
    int x;
    int y;
}Coordinates;

typedef struct { // Create the type Player
    char Name[MAX_NAME_LENGTH];
    float Health;
    float Attack;
    float Exp;
    Coordinates Position;
    char skin;
} Player;

Player BuildPlayer(){
    Player P1;

    do {
        printf("Donnez votre pseudo :\n");
        scanf("%s", P1.Name);
        size_t len = strlen(P1.Name);
        if (P1.Name == NULL) {
            printf("Erreur lors de la saisie du pseudo.\n");
            exit(4);
        }
        if (len > 0 && P1.Name[len - 1] == '\n') {
            P1.Name[strlen(P1.Name) - 1] = '\0';
        }
        // Vérifier la longueur du pseudo
        if (len > MAX_NAME_LENGTH) {
            printf("Le pseudo ne peut pas dépasser %d caractères. Veuillez réessayer.\n", MAX_NAME_LENGTH);
        }
    } while (strlen(P1.Name) > MAX_NAME_LENGTH);

    P1.Health = 100;
    P1.Attack = 10;
    P1.Exp=0;
    P1.Position.x=0;
    P1.Position.y=0;
    P1.skin='^';

    return P1;
}

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

void Travel(Player* P1,Room room){
    int choice;
    printf("Quelle direction?\n Pour la gauche : 1\n Pour la droite : 2\n Pour en haut : 3\n Pour en bas : 4\n");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            if (room.Tab2D[P1->Position.y][P1->Position.x - 1] == ' '){
                room.Tab2D[P1->Position.y][P1->Position.x] = ' ';
                P1->Position.x --;

            }
            else if (room.Tab2D[P1->Position.y][P1->Position.x - 1] == '|'){}
            break;
        case 2:
            if (room.Tab2D[P1->Position.y][P1->Position.x + 1] == ' '){
                room.Tab2D[P1->Position.y][P1->Position.x] = ' ';
                P1->Position.x ++;

            }
            else if (room.Tab2D[P1->Position.y][P1->Position.x + 1] == '|'){}
            break;

        case 3:
            if (room.Tab2D[P1->Position.y+1][P1->Position.x] == ' '){
                room.Tab2D[P1->Position.y][P1->Position.x] = ' ';
                P1->Position.y ++;

            }
            else if (room.Tab2D[P1->Position.y+1][P1->Position.x] == '-'){}
            break;
        case 4:
            if (room.Tab2D[P1->Position.y-1][P1->Position.x] == ' '){
                room.Tab2D[P1->Position.y][P1->Position.x] = ' ';
                P1->Position.y --;

            }
            else if (room.Tab2D[P1->Position.y-1][P1->Position.x] == '-'){}
            break;
    }

}

int main() {
    srand(time(NULL));
    int NumberOfRoom = GenerateNumberOfRoom();
    printf("Nombre de pièce dans la partie : %d\n", NumberOfRoom);
    Room* AllRoom = malloc(sizeof(Room)*NumberOfRoom);
    Room room;
    Player player;
    room = CreateFirstRoom();
    int x = 0;
    int y = 0;
    GetMiddle(&x,&y,room);
    printf("Le milieu de la salle est [%d][%d]\n", y, x);
    AllRoom[0] = room;
    room.Tab2D[y][x]='P';
    PrintfRoom(room);
    player = BuildPlayer();
    player.Position.x=x;
    player.Position.y=y;
    PrintfRoom(room,player);
    Travel(&player, room);
    PrintfRoom(room,player);
    return 0;
}