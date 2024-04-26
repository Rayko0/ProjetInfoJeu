#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
    char** Tab2D; // 2-dimensional table of the room
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
    char skin;
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
    P1.skin='P';

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
    L = rand() % 8 + 3; // Générer une longueur aléatoire entre 3 et 10
    l = rand() % 8 + 3; // Générer une largeur aléatoire entre 3 et 10

    // Ajuster les dimensions si nécessaire pour éviter les salles de type couloir
    if (l - L > 2) {
        L += 4;
    } else if (L - l > 2) {
        l += 4;
    }

    r.l = l; // Stocker les dimensions
    r.L = L;

    // Allouer de la mémoire pour le tableau 2D
    r.Tab2D = malloc(l * sizeof(char*));
    if (r.Tab2D == NULL) {
        printf("Erreur allocation de mémoire pour les coordonnées\n");
        exit(3);
    }

    for (int i = 0; i < l; i++) {
        r.Tab2D[i] = malloc(L * sizeof(char));
        if (r.Tab2D[i] == NULL) {
            printf("Erreur allocation de mémoire pour les coordonnées\n");
            exit(1);
        }

        for (int j = 0; j < L; j++) {
            // Remplir le tableau 2D avec les caractères
            if (i == 0 || i == l - 1) {
                r.Tab2D[i][j] = '-';
            } else if (j == 0 || j == L - 1) {
                r.Tab2D[i][j] = '|';
            } else {
                r.Tab2D[i][j] = ' ';
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

void PrintfRoom(Room room){
    //printf("Largeur %d\n",room.l);
    //printf("Longueur : %d\n", room.L);
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

Door findDoor(Room CurrentRoom, Player P1){
    Door thedoor;
    for(int i=0;i<CurrentRoom.L;i++){
        for(int j=0;j<CurrentRoom.l;j++){
            if(P1.Position.x==CurrentRoom.TabDoor[1].position.x && P1.Position.y==CurrentRoom.TabDoor[1].position.y ){
                thedoor.position.x=CurrentRoom.TabDoor[1].position.x;
                thedoor.position.y=CurrentRoom.TabDoor[1].position.y;
            }
            if(P1.Position.x==CurrentRoom.TabDoor[3].position.x && P1.Position.y==CurrentRoom.TabDoor[3].position.y ){
                thedoor.position.x=CurrentRoom.TabDoor[3].position.x;
                thedoor.position.y=CurrentRoom.TabDoor[3].position.y;
            }
            if(P1.Position.x==CurrentRoom.TabDoor[0].position.x && P1.Position.y==CurrentRoom.TabDoor[0].position.y ){
                thedoor.position.x=CurrentRoom.TabDoor[0].position.x;
                thedoor.position.y=CurrentRoom.TabDoor[0].position.y;
            }
            if(P1.Position.x==CurrentRoom.TabDoor[2].position.x && P1.Position.y==CurrentRoom.TabDoor[2].position.y ){
                thedoor.position.x=CurrentRoom.TabDoor[2].position.x;
                thedoor.position.y=CurrentRoom.TabDoor[2].position.y;
            }
        }
    }
    return thedoor;
}

void roomCreationInGame(Room CurrentRoom, Player P1, Room** Wolrd) {
    Room NextRoom = CreateRoom();
    Door CurrentDoor = findDoor(CurrentRoom, P1);
    if(CurrentDoor.DoorIndex==0){
        CurrentRoom.TabConnectedDoor[0]=&NextRoom.TabDoor[2];
        NextRoom.TabConnectedDoor[2]=&CurrentRoom.TabDoor[0];
    }
    else if(CurrentDoor.DoorIndex==1){
        CurrentRoom.TabConnectedDoor[1]=&NextRoom.TabDoor[3];
        NextRoom.TabConnectedDoor[3]=&CurrentRoom.TabDoor[1];
    }
    else if(CurrentDoor.DoorIndex==2){
        CurrentRoom.TabConnectedDoor[2]=&NextRoom.TabDoor[0];
        NextRoom.TabConnectedDoor[0]=&CurrentRoom.TabDoor[2];
    }
    else if(CurrentDoor.DoorIndex==3){
        CurrentRoom.TabConnectedDoor[3]=&NextRoom.TabDoor[1];
        NextRoom.TabConnectedDoor[1]=&CurrentRoom.TabDoor[3];
    }

    //continuer et faire un switch en mode si je prend port nord j'arrive porte sud
    //et après tu claque un coup d'affichage et tu guettes

}

void doorInteraction(Room CurrentRoom,Player P1, Room** Wolrd){
    int choice;
    printf("voulez vous allez dans la prochaine salle ? 1oui 0non");
    scanf("%d",&choice);
    if(choice==1){
        roomCreationInGame()
    }
    else{
        return;
    }
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
