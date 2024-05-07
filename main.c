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
    r.TabDoor[0].DoorIndex = 0;

    r.TabDoor[2].position.x = rand() % (L - 2) + 1;
    r.TabDoor[2].position.y = l - 1;
    r.TabDoor[2].DoorIndex = 2;

    r.TabDoor[1].position.x = L - 1;
    r.TabDoor[1].position.y = rand() % (l - 2) + 1;
    r.TabDoor[1].DoorIndex = 1;

    r.TabDoor[3].position.x = 0;
    r.TabDoor[3].position.y = rand() % (l - 2) + 1;
    r.TabDoor[3].DoorIndex = 3;

    r.Tab2D[0][r.TabDoor[0].position.x] = '[';
    r.Tab2D[l - 1][r.TabDoor[2].position.x] = '[';
    r.Tab2D[r.TabDoor[1].position.y][L - 1] = '[';
    r.Tab2D[r.TabDoor[3].position.y][0] = '[';

    r.TabConnectedDoor[0]=NULL;
    r.TabConnectedDoor[1]=NULL;
    r.TabConnectedDoor[2]=NULL;
    r.TabConnectedDoor[3]=NULL;
    return r;
}


Room CreateFirstRoom(){
    Room r;
    do {
        r = CreateRoom();
    } while (r.l % 2 == 0 || r.L % 2 ==0);
    return r;
}

void PrintfRoom(Player * P1){
    //printf("Largeur %d\n",room.l);
    //printf("Longueur : %d\n", room.L);
    printf("Coo du joueur : %d x , %d y\n",P1->Position.x,P1->Position.y);
    printf("Adresse de la salle du joueur : %p\n",P1->room);
    for (int i = 0; i < P1->room->l; i++) {
        for (int j = 0; j < P1->room->L; j++) {

                    printf("%c", P1->room->Tab2D[i][j]);

        }
        printf("\n");
    }

}

void GetMiddle(int *x,int *y, Room room){

    *x=room.L/2;
    *y=room.l/2;

}


Door findDoor(Player *P1) {

    for (int i = 0; i < 4; i++) {
        if (P1->Position.x == P1->room->TabDoor[i].position.x && P1->Position.y == P1->room->TabDoor[i].position.y) {
            printf("la porte est la porte %d",i);
            return P1->room->TabDoor[i];
        }
    }
    // Si la position du joueur ne correspond à aucune porte, retourne la première porte par défaut

    return P1->room->TabDoor[2];
}


void roomCreationInGame(Player *P1, Room** World) {
    // Allouer de la mémoire pour la nouvelle salle
    Room *NextRoom = (Room*)malloc(sizeof(Room));
    if (NextRoom == NULL) {
        printf("Erreur : Échec de l'allocation de mémoire pour la nouvelle salle.\n");
        exit(1);
    }

    // Créer la nouvelle salle
    *NextRoom = CreateRoom();

    // Mettre à jour le tableau World avec un pointeur vers la nouvelle salle
    World[1] = NextRoom;

    // Trouver la porte par laquelle le joueur entre dans la nouvelle salle
    Door CurrentDoor = findDoor(P1);

    // Identifier la porte de la nouvelle salle où le joueur sortira
    // et établir une liaison entre les deux portes
    switch (CurrentDoor.DoorIndex) {
        case 0:
            // Le joueur entre par la porte nord de la salle actuelle
            P1->room->TabConnectedDoor[0] = &(NextRoom->TabDoor[2]);
            NextRoom->TabConnectedDoor[2] = &(P1->room->TabDoor[0]);
            // Définir les coordonnées du joueur dans la nouvelle salle
            P1->Position.x = P1->room->TabConnectedDoor[0]->position.x;
            P1->Position.y = P1->room->TabConnectedDoor[0]->position.y;
            break;
        case 1:
            // Le joueur entre par la porte est de la salle actuelle
            P1->room->TabConnectedDoor[1] = &(NextRoom->TabDoor[3]);
            NextRoom->TabConnectedDoor[3] = &(P1->room->TabDoor[1]);
            // Définir les coordonnées du joueur dans la nouvelle salle
            P1->Position.x = P1->room->TabConnectedDoor[1]->position.x;
            P1->Position.y = P1->room->TabConnectedDoor[1]->position.y;
            break;
        case 2:
            // Le joueur entre par la porte sud de la salle actuelle
            P1->room->TabConnectedDoor[2] = &(NextRoom->TabDoor[0]);
            NextRoom->TabConnectedDoor[0] = &(P1->room->TabDoor[2]);
            // Définir les coordonnées du joueur dans la nouvelle salle
            P1->Position.x = P1->room->TabConnectedDoor[2]->position.x;
            P1->Position.y = P1->room->TabConnectedDoor[2]->position.y;
            break;
        case 3:
            // Le joueur entre par la porte ouest de la salle actuelle
            P1->room->TabConnectedDoor[3] = &(NextRoom->TabDoor[1]);
            NextRoom->TabConnectedDoor[1] = &(P1->room->TabDoor[3]);
            // Définir les coordonnées du joueur dans la nouvelle salle
            P1->Position.x = P1->room->TabConnectedDoor[3]->position.x;
            P1->Position.y = P1->room->TabConnectedDoor[3]->position.y;
            break;
        default:
            // Gérer le cas où l'index de la porte n'est pas valide
            printf("Erreur: Index de porte invalide.\n");
            break;
    }

    // Mettre à jour la salle actuelle du joueur avec la nouvelle salle
    P1->room = World[1];
    // Mettre à jour l'affichage du joueur dans la nouvelle salle
    P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
}

void doorInteraction(Player* P1, Room** World){
    int choice;
    printf("Voulez-vous aller dans la prochaine salle ? 1 oui 0 non\n");
    scanf("%d", &choice);
    if(choice == 1){
        roomCreationInGame(P1, World);
    }
    else{
        return;
    }
}


void Travel(Player* P1,Room ** World){
    int choice;
    do{
        printf("-----------------------------------------------------------------------------------------------\n");
        printf("Quelle direction? A gauche : 1  A droite : 2  En bas : 3  En haut : 4  Quitter : 0\n");
        printf("-----------------------------------------------------------------------------------------------\n");
        scanf("%d", &choice);
    }while(choice<1 || choice>4);
    switch(choice){
        case 1:
            if (P1->room->Tab2D[P1->Position.y][P1->Position.x - 1] == ' '){
                P1->room->Tab2D[P1->Position.y][P1->Position.x] = ' ';
                if(P1->Position.x == P1->room->TabDoor[1].position.x && P1->Position.y == P1->room->TabDoor[1].position.y){
                    P1->room->Tab2D[P1->Position.y][P1->Position.x]='[';
                }
                P1->Position.x --;
                P1->room->Tab2D[P1->Position.y][P1->Position.x]=P1->skin;

            }
            else if (P1->room->Tab2D[P1->Position.y][P1->Position.x - 1] == '|'){}
            else if (P1->room->Tab2D[P1->Position.y][P1->Position.x - 1] == '['){
                P1->room->Tab2D[P1->Position.y][P1->Position.x] = ' ';
                if(P1->room->TabConnectedDoor[3]==NULL) {
                    P1->Position.x = P1->Position.x - 1;
                    doorInteraction(P1, World);
                }
                else{
                    P1->Position.x = P1->room->TabConnectedDoor[3]->position.x;
                    P1->Position.y = P1->room->TabConnectedDoor[3]->position.y;
                    P1->room = World[0];
                    P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                }
            }
            break;
        case 2:
            if (P1->room->Tab2D[P1->Position.y][P1->Position.x + 1] == ' '){
                P1->room->Tab2D[P1->Position.y][P1->Position.x] = ' ';
                if(P1->Position.x == P1->room->TabDoor[3].position.x && P1->Position.y == P1->room->TabDoor[3].position.y){
                    P1->room->Tab2D[P1->Position.y][P1->Position.x]='[';
                }
                P1->Position.x ++;
                P1->room->Tab2D[P1->Position.y][P1->Position.x]=P1->skin;
            }
            else if (P1->room->Tab2D[P1->Position.y][P1->Position.x + 1] == '|'){}
            else if (P1->room->Tab2D[P1->Position.y][P1->Position.x + 1] == '['){
                P1->room->Tab2D[P1->Position.y][P1->Position.x] = ' ';
                if(P1->room->TabConnectedDoor[1]==NULL) {
                    P1->Position.x = P1->Position.x + 1;
                    doorInteraction(P1, World);
                }
                else{
                    P1->Position.x = P1->room->TabConnectedDoor[1]->position.x;
                    P1->Position.y = P1->room->TabConnectedDoor[1]->position.y;
                    P1->room = World[0];
                    P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                }
            }
            break;

        case 3:
            if (P1->room->Tab2D[P1->Position.y+1][P1->Position.x] == ' '){
                P1->room->Tab2D[P1->Position.y][P1->Position.x] = ' ';
                if(P1->Position.x == P1->room->TabDoor[0].position.x && P1->Position.y == P1->room->TabDoor[0].position.y){
                    P1->room->Tab2D[P1->Position.y][P1->Position.x]='[';
                }
                P1->Position.y ++;
                P1->room->Tab2D[P1->Position.y][P1->Position.x]=P1->skin;
            }
            else if (P1->room->Tab2D[P1->Position.y+1][P1->Position.x] == '-'){}
            else if (P1->room->Tab2D[P1->Position.y+1][P1->Position.x] == '['){
                P1->room->Tab2D[P1->Position.y][P1->Position.x] = ' ';
                if(P1->room->TabConnectedDoor[2]==NULL) {
                    P1->Position.x = P1->Position.y + 1;
                    doorInteraction(P1, World);
                }
                else{
                    P1->Position.x = P1->room->TabConnectedDoor[2]->position.x;
                    P1->Position.y = P1->room->TabConnectedDoor[2]->position.y;
                    P1->room = World[0];
                    P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                }
            }
            break;
        case 4:
            if (P1->room->Tab2D[P1->Position.y-1][P1->Position.x] == ' '){
                P1->room->Tab2D[P1->Position.y][P1->Position.x] = ' ';
                if(P1->Position.x == P1->room->TabDoor[2].position.x && P1->Position.y == P1->room->TabDoor[2].position.y){
                    P1->room->Tab2D[P1->Position.y][P1->Position.x]='[';
                }
                P1->Position.y --;
                P1->room->Tab2D[P1->Position.y][P1->Position.x]=P1->skin;
            }
            else if (P1->room->Tab2D[P1->Position.y-1][P1->Position.x] == '-'){}
            else if (P1->room->Tab2D[P1->Position.y-1][P1->Position.x] == '['){
                P1->room->Tab2D[P1->Position.y][P1->Position.x] = ' ';
                if(P1->room->TabConnectedDoor[0]==NULL) {
                    P1->Position.y = P1->Position.y - 1;
                    doorInteraction(P1, World);
                }
                else{
                    P1->Position.x = P1->room->TabConnectedDoor[0]->position.x;
                    P1->Position.y = P1->room->TabConnectedDoor[0]->position.y;
                    P1->room = World[0];
                    P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                }
            }
            break;
        case 0:
            exit(0);
    }

}

int main() {
    srand(time(NULL));
    int NumberOfRoom = GenerateNumberOfRoom();
    printf("Nombre de salle dans la partie : %d\n", NumberOfRoom);
    Room* World = malloc(sizeof(Room)*NumberOfRoom);
    Room room;
    room = CreateFirstRoom();
    World[0] = room;
    Player player;
    player = BuildPlayer();
    player.room=&World[0];
    int x = 0;
    int y = 0;
    GetMiddle(&x,&y,room);
    //printf("Le milieu de la salle est [%d][%d]\n", y, x);
    room.Tab2D[y][x]=player.skin;
    player.Position.x=x;
    player.Position.y=y;
    PrintfRoom(&player);
    Travel(&player,&World);
    PrintfRoom(&player);
    int stop=0;

    do{
        Travel(&player,&World);
        PrintfRoom(&player);

    } while (stop!=1);


    return 0;
}
