#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <wchar.h>

#define MAXROOM 20
#define MAX_NAME_LENGTH 5

typedef struct{
    int x;
    int y;
} Coordinates;

typedef struct{
    Coordinates position; // Les coordonnées de la porte dans la salle
    int DoorIndex;
} Door;

typedef struct { // Create the type Room
    int l; // Width of the room
    int L; // Length of the room
    int** Tab2D; // 2-dimensional table of the room
    Door TabDoor[4]; //Door of the room: 0 is the north room, 1 = east, 2 = south, 3 = west
    Door * TabConnectedDoor[4]; // Still the same but each slot is for a door in another room
    int RoomIndex;
} Room;

typedef struct { // Create the type Player
    char Name[MAX_NAME_LENGTH];
    float Hp;
    float Atk;
    float Exp;
    Coordinates Position;
    char skin;
    Room * room;
} Player;

typedef struct{
    int skin;
    float Hp;
    float Atk;
    Coordinates Position;
}Mob;

Mob BuildMob(){
    Mob Mob;
    Mob.Hp=25;
    Mob.Atk=5;
    Mob.skin='*';
    return Mob;
}

Player BuildPlayer(){
    Player P1;

    do {
        printf("Donnez votre pseudo :\n");
        scanf("%s", P1.Name);
        size_t len = strlen(P1.Name);
        /*if (P1.Name == NULL) {
            printf("Erreur lors de la saisie du pseudo.\n");
            exit(4);
        }*/ //TODO:A mediter
        if (len > 0 && P1.Name[len - 1] == '\n') {
            P1.Name[strlen(P1.Name) - 1] = '\0';
        }
        // Vérifier la longueur du pseudo
        if (len > MAX_NAME_LENGTH) {
            printf("Le pseudo ne peut pas dépasser %d caractères. Veuillez réessayer.\n", MAX_NAME_LENGTH);
        }
    } while (strlen(P1.Name) > MAX_NAME_LENGTH);

    P1.Hp = 100;
    P1.Atk = 10;
    P1.Exp=0;
    P1.Position.x=0;
    P1.Position.y=0;
    P1.skin=2;

    return P1;
}

int GenerateNumberOfRoom(){ // Generate a random number of room between 10 and MAXROOM in a pointer to an integer
    int a;
    a = rand() %11 + (MAXROOM-10);
    return a;
}

Room CreateRoom() {
    int l, L;
    Room r;
    L = rand() % 22 + 3; // Générer une longueur aléatoire entre 3 et 10
    l = rand() % 22 + 3; // Générer une largeur aléatoire entre 3 et 10

    // Ajuster les dimensions si nécessaire pour éviter les salles de type couloir
    if (l - L > 2) {
        L += 4;
    } else if (L - l > 2) {
        l += 4;
    }

    r.l = l; // Stocker les dimensions
    r.L = L;

    // Allouer de la mémoire pour le tableau 2D
    r.Tab2D = malloc(l * sizeof(int*));
    if (r.Tab2D == NULL) {
        printf("Erreur allocation de mémoire pour les coordonnées\n");
        exit(3);
    }

    for (int i = 0; i < l; i++) {
        r.Tab2D[i] = malloc(L * sizeof(int));
        if (r.Tab2D[i] == NULL) {
            printf("Erreur allocation de mémoire pour les coordonnées\n");
            exit(1);
        }

        for (int j = 0; j < L; j++) {
            // Remplir le tableau 2D avec les caractères
            if (i == 0 || i == l - 1) {
                r.Tab2D[i][j] = 5;
            }
            else if (j == 0 || j == L - 1) {
                r.Tab2D[i][j] = 6;
            }
            
            else {
                r.Tab2D[i][j] = 0;
            }
        }
    }

    // Placer aléatoirement les portes sur chaque côté de la salle
    r.TabDoor[0].position.x = rand() % (L - 2) + 1;
    r.TabDoor[0].position.y = 0;

    r.TabDoor[2].position.x = rand() % (L - 2) + 1;
    r.TabDoor[2].position.y = l - 1;

    r.TabDoor[3].position.x = 0;
    r.TabDoor[3].position.y = rand() % (l - 2) + 1;

    r.TabDoor[1].position.x = L - 1;
    r.TabDoor[1].position.y = rand() % (l - 2) + 1;

    r.Tab2D[0][r.TabDoor[0].position.x] = '[';
    r.Tab2D[l - 1][r.TabDoor[2].position.x] = '[';
    r.Tab2D[r.TabDoor[3].position.y][0] = '[';
    r.Tab2D[r.TabDoor[1].position.y][L - 1] = '[';

    return r;
}

Room CreateFirstRoom(){
    Room r;
    do {
        r = CreateRoom();
    } while (r.l % 2 == 0 || r.L % 2 ==0);
    return r;
}

void PrintfRoom(Room r){
    //printf("Largeur %d\n",room.l);
    //printf("Longueur : %d\n", room.L);
    for (int i = 0; i < r.l; i++) {
        for (int j = 0; j < r.L; j++) {
            if (i == 0 || i == r.l - 1) {
                printf("\U0001F60A");
            }
            else if (j == 0 || j == r.L - 1) {
                printf("\U0001F31F");
                
         
            } 
            else if (r.Tab2D[i][j]==2) {
                printf("P ");
            }
            else {
                printf("  ");
            }
      
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
    do{
        printf("Quelle direction?\n Pour la gauche : 1\n Pour la droite : 2\n Pour en bas : 3\n Pour en haut : 4\n");
        scanf("%d", &choice);
    }while(choice<1 || choice>4);
    switch(choice){
        case 1:
            if (room.Tab2D[P1->Position.y][P1->Position.x - 1] == ' '){
                room.Tab2D[P1->Position.y][P1->Position.x] = ' ';
                P1->Position.x --;
                room.Tab2D[P1->Position.y][P1->Position.x]=P1->skin;

            }
            else if (room.Tab2D[P1->Position.y][P1->Position.x - 1] == '|'){}
            /*else if (room.Tab2D[P1->Position.y][P1->Position.x - 1] == '['){
                doorInteraction(CurrentRoom);
            }*/
            break;
        case 2:
            if (room.Tab2D[P1->Position.y][P1->Position.x + 1] == ' '){
                room.Tab2D[P1->Position.y][P1->Position.x] = ' ';
                P1->Position.x ++;
                room.Tab2D[P1->Position.y][P1->Position.x]=P1->skin;
            }
            else if (room.Tab2D[P1->Position.y][P1->Position.x + 1] == '|'){}
            /*else if (room.Tab2D[P1->Position.y][P1->Position.x + 1] == '['){
                doorInteraction(CurrentRoom);
            }*/
            break;

        case 3:
            if (room.Tab2D[P1->Position.y+1][P1->Position.x] == ' '){
                room.Tab2D[P1->Position.y][P1->Position.x] = ' ';
                P1->Position.y ++;
                room.Tab2D[P1->Position.y][P1->Position.x]=P1->skin;
            }
            else if (room.Tab2D[P1->Position.y+1][P1->Position.x] == '-'){}
            /*else if (room.Tab2D[P1->Position.y+1][P1->Position.x] == '['){
                doorInteraction(CurrentRoom);
            }*/
            break;
        case 4:
            if (room.Tab2D[P1->Position.y-1][P1->Position.x] == ' '){
                room.Tab2D[P1->Position.y][P1->Position.x] = ' ';
                P1->Position.y --;
                room.Tab2D[P1->Position.y][P1->Position.x]=P1->skin;
            }
            else if (room.Tab2D[P1->Position.y-1][P1->Position.x] == '-'){}
            /*else if (room.Tab2D[P1->Position.y-1][P1->Position.x] == '['){
                doorInteraction(CurrentRoom);
            }*/
            break;
    }

}

int main() {
    srand(time(NULL));
    int NumberOfRoom = GenerateNumberOfRoom();
    printf("Nombre de salle dans la partie : %d\n", NumberOfRoom);
    Room* World = malloc(sizeof(Room)*NumberOfRoom);
    Room room;
    room = CreateFirstRoom();
    Player player;
    player = BuildPlayer();
    int x = 0;
    int y = 0;
    GetMiddle(&x,&y,room);
    //printf("Le milieu de la salle est [%d][%d]\n", y, x);
    World[0] = room;
    room.Tab2D[y][x]=player.skin;
    player.Position.x=x;
    player.Position.y=y;
    PrintfRoom(room);
    Travel(&player, room);
    PrintfRoom(room);
    int stop=0;
    do{
        Travel(&player, room);
        PrintfRoom(room);
        do {
            printf("veux tu arreter ? 1oui et 0non");
            scanf("%d", &stop);
        } while (stop!=0 && stop!=1);
    } while (stop!=1);


    return 0;
}
