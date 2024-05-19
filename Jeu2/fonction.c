#include "menuInGame.h"
#include "fonction.h"

const int MovX[4] = {0,0,-1,1};
const int MovY[4] = {-1,1,0,0};
const char* VIDE = " ";

//graphiques
char* Doors[4] = {"╠", "╣" , "╦", "╩"};
char* LinkSkin[4] = {"╌", "╌" , "╎", "╎"};
char* Skins[9] = {"🧔", "👨‍🦱", "👩‍🦱", "🤖", "😼" , "👨‍🦳" ,"👶", "🤡", "😈"};
char* Monsters[6] = {"▓", "👻", "👽", "👾", "🧞" ,"🧟"};
char* Items[3] = {"🗡","🛡","♡"};//0 = Epee, 1 = Bouclier, 2 = Coeur

void PrintMessage(char* message){
    // Pour afficher les messages dans un box
    printf("\U0000256D"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U0000256E"
               "\n");
        printf("\U00002502 %s\n", message);
        printf("\U00002570"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U0000256F"
               "\n");
}

Mob BuildMob(){
    Mob Mob;
    Mob.Hp=25;
    Mob.Atk=5;
    Mob.skin= Monsters[0];
    return Mob;
}

Item BuildItem() {
    Item item;
    int itemnum = rand() % 3;
    if (itemnum == 0) {
        item.Sword = 1;
        item.Shield = 0;
        item.Heart = 0;
        item.skin = Items[0];
    } else if (itemnum == 1) {
        item.Sword = 0;
        item.Shield = 1;
        item.Heart = 0;
        item.skin = Items[1];
    } else if (itemnum == 2) {
        item.Sword = 0;
        item.Shield = 0;
        item.Heart = 1;
        item.skin = Items[2];
    }
    item.position.x = 0;
    item.position.y = 0;
    return item;
}

World* CreateWorld(int NumberOfRoom){
    World* world = malloc(sizeof(World));
    //define the map limits
    world->size.x = 1024, world->size.y = 1024;
    //define the rooms array in world
    world->rooms = malloc(sizeof(Room)*NumberOfRoom);
    //define the map array
    world->map = malloc(sizeof(char**) * world->size.x);
    for(int i= 0; i < world->size.x; i++) {
        world->map[i] = malloc(sizeof(char*)*world->size.y);
        for(int j = 0; j < world->size.y; j++) world->map[i][j] = " ";
    }

    return world;
}

void AddRoomToWorld(World* world, Room* room){
    for(int i = 0; i < room->size.x; i++)
        for(int j = 0; j < room->size.y; j++)
            world->map[room->position.x+i][room->position.y+j] = room->Tab2D[i][j];
}

Player* BuildPlayer(){
    Player* P1 = malloc(sizeof(Player));

    do {
        printf("Donnez votre pseudo :\n");
        scanf("%s", P1->Name);
        size_t len = strlen(P1->Name);
        /*if (P1.Name == NULL) {
            printf("Erreur lors de la saisie du pseudo.\n");
            exit(4);
        }*/ //TODO:A mediter
        if (len > 0 && P1->Name[len - 1] == '\n') {
            P1->Name[strlen(P1->Name) - 1] = '\0';
        }
        // Vérifier la longueur du pseudo
        if (len > MAX_NAME_LENGTH) {
            PrintMessage("Le pseudo ne peut pas dépasser %d caractères. Veuillez réessayer.\n");
        }
    } while (strlen(P1->Name) > MAX_NAME_LENGTH);

    P1->Hp = 100;
    P1->Atk = 10;
    P1->Exp=0;
    P1->Position.x=0;
    P1->Position.y=0;
    P1->skin= Skins[0];
    return P1;
}

int GenerateNumberOfRoom(){ // Generate a random number of room between 10 and MAXROOM in a pointer to an integer
    int a;
    a = rand() %11 + (MAXROOM-10);
    return a;
}

Room* CreateRoom(int cnt) {
    int l, L;
    Room* r = (Room*)malloc(sizeof(Room));
    if (r == NULL) {
        PrintMessage("Erreur : Échec de l'allocation de mémoire pour la nouvelle salle.");
        exit(1);
    }
    r->RoomIndex = cnt;
    L = ((rand() % 4)*2) + 5; // Générer une longueur aléatoire entre 3 et 11
    l = ((rand() % 4)*2) + 5; // Générer une largeur aléatoire entre 3 et 11

    // Ajuster les dimensions si nécessaire pour éviter les salles de type couloir
    if (l - L > 3){
        L+=rand() % 3 + 2;
    }
    if (L - l > 3){
        l+=rand() % 3 + 2;
    }

    r->size.x = l; // Stocker les dimensions
    r->size.y = L;

    // Allouer de la mémoire pour le tableau 2D
    r->Tab2D = malloc(l * sizeof(char**));
    if (r->Tab2D == NULL) {
        printf("Erreur allocation de mémoire pour les coordonnées\n");
        exit(3);
    }

    for (int i = 0; i < l; i++) {
        r->Tab2D[i] = malloc(L * sizeof(char*));
        if (r->Tab2D[i] == NULL) {
            printf("Erreur allocation de mémoire pour les coordonnées\n");
            exit(1);
        }

        for (int j = 0; j < L; j++) {
            // Remplir le tableau 2D avec les caractères
            if(i == 0 && j == 0) r->Tab2D[i][j] = "╔";
            else if(i == 0 && j == L-1) r->Tab2D[i][j] = "╗";
            else if(i == l-1 && j == L-1) r->Tab2D[i][j] = "╝";
            else if(i == l-1 && j == 0) r->Tab2D[i][j] = "╚";
            else if (i == 0 || i == l - 1) r->Tab2D[i][j] = "═";
            else if (j == 0 || j == L - 1) r->Tab2D[i][j] = "║";
            else r->Tab2D[i][j] = " ";
        }
    }

    // Placer aléatoirement les portes sur chaque côté de la salle
    // Porte d'indice 0 -> porte Ouest
    // Porte d'indice 1 -> porte Est
    // Porte d'indice 2 -> porte Nord
    // Porte d'indice 3 -> porte Sud
    for (int k = 0; k < 2; ++k)
    {
        r->TabDoor[k].position.x = rand() % (l - 2) + 1;
        r->TabDoor[k].position.y = k * (L - 1);
    }
    for (int k = 2; k < 4; ++k)
    {
        r->TabDoor[k].position.x = (k%2) * (l - 1);
        r->TabDoor[k].position.y = rand() % (L - 2) + 1;
    }


    for (int k = 0; k < 4; ++k) {
        //printf("%d %d %d %d\n", r.TabDoor[k].position.x, r.TabDoor[k].position.y, l, L);
        r->Tab2D[r->TabDoor[k].position.x][r->TabDoor[k].position.y] = Doors[k];
        r->TabDoor[k].RoomIndex = r->RoomIndex;
        r->TabConnectedDoor[k]=NULL;
    }
   Coordinates p;
   int doorIndex;
   do {
        // Générer des coordonnées aléatoires à l'intérieur de la salle
        p.x = rand() % (r->size.x - 2) + 1; // Évitez les bords
        p.y = rand() % (r->size.y - 2) + 1;

        // Vérifier si la position est devant une porte
        doorIndex = -1;
        for (int i = 0; i < 4; i++) {
            if (p.x == r->TabDoor[i].position.x && p.y == r->TabDoor[i].position.y) {
                doorIndex = i;
 		break; // La position est devant une porte, réessayer
            }
        }
    } while (doorIndex != -1); // Réessayer jusqu'à ce que la position ne soit pas devant une porte 
   Mob mob =BuildMob();
   r->Tab2D[p.x][p.y]=mob.skin;
   r->RoomMob = mob;
   
   Item item = BuildItem();
   Coordinates p2;
   int doorIndex2;
   do {
        // Générer des coordonnées aléatoires à l'intérieur de la salle
        p2.x = rand() % (r->size.x - 2) + 1; // Évitez les bords
        p2.y = rand() % (r->size.y - 2) + 1;

        // Vérifier si la position est devant une porte
        doorIndex2 = -1;
        for (int i = 0; i < 4; i++) {
            if (p2.x == r->TabDoor[i].position.x && p2.y == r->TabDoor[i].position.y) {
                doorIndex2 = i;
 		break; // La position est devant une porte, réessayer
            }
        }
    } while (doorIndex != -1 && p2.x==p.x && p2.y==p.y ); // Réessayer jusqu'à ce que la position ne soit pas devant une porte 
    r->Tab2D[p2.x][p2.y]=item.skin;
    r->RoomItem = item;

    return r;
}


Room* CreateFirstRoom(){
    Room* r;
    r = CreateRoom(0);
    return r;
}

void PrintfRoom(Player * P1, World* world){
    printf("\033c");
    printf("Coo du joueur : %d x , %d y\n",P1->Position.x,P1->Position.y);
    printf("Joueur est dans la salle %d\n",P1->room->RoomIndex);
    for (int i = -CameraRangeX; i <= CameraRangeX; i++) {
        for (int j = -CameraRangeY; j <= CameraRangeY; j++)
            if(!i && !j) printf("%s", P1->skin);
            else {
                if(!j && (world->map[P1->Position.x + i][P1->Position.y + j] == "║" || world->map[P1->Position.x + i][P1->Position.y + j] == " " || world->map[P1->Position.x + i][P1->Position.y + j] == "╎ ")) printf(" ");
                else if(!j) printf("═");
                printf("%s",world->map[P1->Position.x + i][P1->Position.y + j]);
            }
        printf("\n");
    }    
    printf("\033[35m\U000025CF"
            "\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF"
            "\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF"
            "\U000025BF\U000025BF"
            "\U000025CF\033[0m"
            "\n");
    printf("     \033[35mSTATISTIQUES\033[0m\n"
            "     \033[37mPartie de : %s\033[0m\n"
            "     \033[32mHealth : %.2f\033[0m\n"
            "     \033[31mAttack : %.2f\033[0m\n"
            "     \033[36mExp : %.2f\033[0m\n", P1->Name, P1->Hp, P1->Atk, P1->Exp);
    printf("\033[35m\U000025CF"
            "\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF"
            "\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF"
            "\U000025BF\U000025BF"
            "\U000025CF\033[0m"
            "\n\n");
}

void GetMiddle(int *x,int *y, Coordinates Size){

    *x=Size.x/2;
    *y=Size.y/2;

}


int findDoor(Player *P1) {
    // Si la position du joueur ne correspond à une porte, retourne l'indice de celle ci
    for (int i = 0; i < 4; i++) {
        if (P1->Position.x == P1->room->TabDoor[i].position.x + P1->room->position.x 
        && P1->Position.y == P1->room->TabDoor[i].position.y + P1->room->position.y) {
            printf("la porte est la porte %d\n",i);
            return i;
        }
    }
    // Si la position du joueur ne correspond à aucune porte, retourne -1

    return -1;
}


void roomCreationInGame(Player *P1, World* world, int cpt) {
    
    // Créer la nouvelle salle
    Room* NextRoom = CreateRoom(cpt);
    // Mettre à jour le tableau World avec un pointeur vers la nouvelle salle
    world->rooms[cpt] = NextRoom;

    // Trouver la porte par laquelle le joueur entre dans la nouvelle salle
    int CurrentDoorIndex = findDoor(P1);
    P1->Position.x += MovX[CurrentDoorIndex];
    P1->Position.y += MovY[CurrentDoorIndex];

    world->map[P1->Position.x][P1->Position.y] = LinkSkin[CurrentDoorIndex];

    P1->Position.x += MovX[CurrentDoorIndex];
    P1->Position.y += MovY[CurrentDoorIndex];   
    // Identifier la porte de la nouvelle salle où le joueur sortira
    // et établir une liaison entre les deux portes

    // l'est et l'ouest se connectent et le nord avec le sud
    // Donc 0 <-> 1 et 2 <-> 3
    // Donc il suffit de changer la premiére bit pour trouver l'autre porte : on peut utiliser l'operation XOR.
    P1->room->TabConnectedDoor[CurrentDoorIndex] = &(NextRoom->TabDoor[CurrentDoorIndex ^ 1]);
    NextRoom->TabConnectedDoor[CurrentDoorIndex ^ 1] = &(P1->room->TabDoor[CurrentDoorIndex]);

    NextRoom->position.x = P1->Position.x - P1->room->TabConnectedDoor[CurrentDoorIndex]->position.x;
    NextRoom->position.y = P1->Position.y - P1->room->TabConnectedDoor[CurrentDoorIndex]->position.y;
    printf("%d %d\n", NextRoom->position.x , NextRoom->position.y );
    // Mettre à jour la salle actuelle du joueur avec la nouvelle salle
    P1->room = NextRoom;
    AddRoomToWorld(world,NextRoom);
}


void doorInteraction(Player* P1, World* world, int* cnt, int dir){
    int choice = -1;
    PrintMessage("Voulez-vous aller dans la prochaine salle ? 1 oui 0 non");
    scanf("%d", &choice);
    if(choice == 1){
        P1->Position.x += MovX[dir];
        P1->Position.y += MovY[dir];
        (*cnt)++;
        roomCreationInGame(P1, world, *cnt);
    }
}


void Travel(Player* P1, World* world,int * cnt){
    char input;
    char buffer[10]; // Utilisation d'un buffer pour lire l'entrée utilisateur
 
        PrintfRoom(P1, world);
        printf("\033[33m\U0000256D"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500"
               "\U0000256E\033[0m"
               "\n");
        printf("\033[33m\U00002502  Quelle direction?    \U00002502\033[0m\n"
               "\033[33m\U00002502\033[0m  \U000025B2 : z                \033[33m\U00002502\033[0m\n"
               "\033[33m\U00002502\033[0m  \U000025C0 : q                \033[33m\U00002502\033[0m\n"
               "\033[33m\U00002502\033[0m  \U000025BC : s                \033[33m\U00002502\033[0m\n"
               "\033[33m\U00002502\033[0m  \U000025B6 : d                \033[33m\U00002502\033[0m\n"
               "\033[33m\U00002502\033[0m  Menu : 0             \033[33m\U00002502\033[0m\n");
        printf("\033[33m\U00002570"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
               "\U00002500\U00002500\U00002500"
               "\U0000256F\033[0m"
               "\n\n");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Assurez-vous que l'entrée ne contient qu'un seul caractère suivi d'un '\n'
        if (sscanf(buffer, " %c", &input) == 1 && buffer[1] == '\n') {   

    int choice;
    switch(input){
    case 'z':
     choice = 3;
     break;
    case 'q':
     choice = 1;
     break;
    case 's':
     choice = 4;
     break;
    case 'd':
     choice = 2;
     break;
    case '0':
     menuInGame();
     break; 
   }
    choice--;
    if (world->map[P1->Position.x  + MovX[choice]][P1->Position.y  + MovY[choice]] == Doors[choice]){
        if(P1->room->TabConnectedDoor[choice]==NULL) {
            doorInteraction(P1, world,cnt,choice);
        }
        else{
            P1->Position.x += 3*MovX[choice];
            P1->Position.y += 3*MovY[choice];
            P1->room = world->rooms[P1->room->TabConnectedDoor[choice]->RoomIndex];
        }
    }
    if (world->map[P1->Position.x + MovX[choice]][P1->Position.y + MovY[choice]] == " "){
        P1->Position.x += MovX[choice];
        P1->Position.y += MovY[choice];
    }
   } 
}
}
