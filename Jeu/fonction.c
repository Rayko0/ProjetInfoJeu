#include "menuInGame.h"
#include "fonction.h"
#include <unistd.h>
const int MovX[4] = {0,0,-1,1};
const int MovY[4] = {-1,1,0,0};


//graphiques
char* Doors[4] = {"╠", "╣" , "╦", "╩"};//Doors[0]=30; Doors[1]=31; Doors[2]=32; Doors[3]=33
char* LinkSkin[4] = {"╌", "╌" , "╎", "╎"};//╌ = 81; ╎ = 82; 
char* Skins[6] = {"🧔", "🤖", "😼" ,"👶", "🤡", "😈"};//Skin[0]=40;
char* Monsters[6] = {"▓", "👻", "👽", "👾", "🧞" ,"🧟"};//Monsters[0]=50;
char* Items[3] = {"🗡","🛡","♡"};//0 = Epee = 60, 1 = Bouclier= 61, 2 = Coeur=62;

Mob BuildMob(){
    Mob Mob;
    Mob.Hp=25;
    Mob.Atk=5;
    Mob.Esq=3;
    Mob.Def=8;
    Mob.skin= 50;
    return Mob;
}

void PrintMessage(char* message){
    // Pour afficher les messages dans un box
    printf("╭"
    "──────────────────────────────────────────────────────────────────────────────────────────"
    "╮"
    "\n");
    printf("                   %s                    \n", message);
    printf("╰"
    "──────────────────────────────────────────────────────────────────────────────────────────"
    "╯"
    "\n");
}


Item BuildItem() {
    Item item;
    int itemnum = rand() % 3;
    if (itemnum == 0) {
        item.Sword = 1;
        item.Shield = 0;
        item.Heart = 0;
        item.skin = 60;
    } else if (itemnum == 1) {
        item.Sword = 0;
        item.Shield = 1;
        item.Heart = 0;
        item.skin = 61;
    } else if (itemnum == 2) {
        item.Sword = 0;
        item.Shield = 0;
        item.Heart = 1;
        item.skin = 62;
    }
    item.position.x = 0;
    item.position.y = 0;
    return item;
}

World* CreateWorld(int NumberOfRoom){
    World* world = malloc(sizeof(World));
    //define the map limits
    world->size.x = MAX_WORLD_SIZE;
    world->size.y = MAX_WORLD_SIZE;
    //define the rooms array in world
    world->rooms = malloc(sizeof(Room)*NumberOfRoom);

    //define the map array
    world->map = malloc(sizeof(int*) * world->size.x);
    for(int i= 0; i < world->size.x; i++) {
        world->map[i] = malloc(sizeof(int)*world->size.y);
        for(int j = 0; j < world->size.y; j++){
	 world->map[i][j] = 0;
    }
}
    
    //define the maximum number of Doors
    world->NbMax = NumberOfRoom-1;
    world->NbDoors = 0; 
    world->NbRooms = 0; 

    return world;
}

void AddRoomToWorld(World* world, Room* room){
    for(int i = 0; i < room->size.x; i++){
        for(int j = 0; j < room->size.y; j++){
            	
		world->map[room->position.x+i][room->position.y+j] = room->Tab2D[i][j];
        }
    }
}

Player* BuildPlayer(){
    Player* P1 = malloc(sizeof(Player));
    do {
        printf("╭"
        "────────────────────────"
        "╮"
        "\n");
        printf("│  Donnez votre pseudo : │\n");
        printf("╰"
        "────────────────────────"
        "╯"
        "\n");
        scanf("%s", P1->Name);
        size_t len = strlen(P1->Name);
        if (len > 0 && P1->Name[len - 1] == '\n') {
            P1->Name[strlen(P1->Name) - 1] = '\0';
        }
        // Vérifier la longueur du pseudo
        if (len > MAX_NAME_LENGTH) {
	    printf("\033[31m╭"
            "────────────────────────────────────────────────────────────────────"
            "╮"
            "\033[0m\n");
            printf("\033[31m│\033[0m  Le pseudo ne peut pas dépasser %d caractères. Veuillez réessayer. \033[31m│\033[0m\n", MAX_NAME_LENGTH);

            printf("\033[31m╰"
            "────────────────────────────────────────────────────────────────────"
            "╯"
            "\033[0m\n");
        }
    } while (strlen(P1->Name) > MAX_NAME_LENGTH);
    P1->Hp = 100;
    P1->Atk = 10;
    P1->Esq = 10;
    P1->Def = 25;
    P1->Exp=0;
    P1->Position.x=0;
    P1->Position.y=0;
    P1->skin= 40;
    for(int i=0; i<4; i++){
	P1->Inventory[i].exist=0;
    }

    return P1;
    P1->KillCounter=0;
    P1->DeathCounter=0;
}

int GenerateNumberOfRoom(){ 
    // Generate a random number of room between 10 and MAXROOM in a pointer to an integer
    int a;
    a = rand() % 11 + (MAXROOM-10);
    return a;
}

void combat(Player *player, Mob *mob, World *World) {
    // Boucle de combat jusqu'à ce que l'un des participants n'ait plus de points de vie
    while (player->Hp > 0 && mob->Hp > 0) {
        // Le joueur attaque le monstre
        float player_damage = player->Atk * (1 - (mob->Esq / 100)); // Calcul des dégâts du joueur
        mob->Hp -= player_damage; // Réduction des points de vie du monstre

        // Le monstre attaque le joueur
        float mob_damage = mob->Atk * (1 - (player->Esq / 100)); // Calcul des dégâts du monstre
        player->Hp -= mob_damage; // Réduction des points de vie du joueur

        // Affichage des dégâts infligés à chaque tour
        sleep(1);
	printf("%s inflige %.2f dégâts au bug\n", player->Name, player_damage);
        printf("Le bug inflige %.2f dégâts à %s.\n", mob_damage, player->Name);
    }

    // Affichage du résultat du combat
    if (player->Hp <= 0) {
        sleep(1);
	printf("%s a été vaincu par le bug !\n", player->Name);
        //Donc faut regénérer une map etc
    } else {
        sleep(1);
	printf("%s a vaincu le bug !\n", player->Name);
	sleep(1);
	World->rooms[player->roomIndex]->RoomMob.exist=0;
	World->rooms[player->roomIndex]->Tab2D[World->rooms[player->roomIndex]->RoomMob.Position.x][World->rooms[player->roomIndex]->RoomMob.Position.y]=0;
	player->KillCounter+=1;
	sleep(1);
	printf("%s a %d Kill\n", player->Name, player->KillCounter);
	AddRoomToWorld(World, World->rooms[player->roomIndex]);
	sleep(1);
}
sleep(1);
}

bool isSpaceFree(World* world, Coordinates pos, int k) {
    if (pos.x - 10 < 0 || pos.x + 10 >= world->size.x || pos.y - 10 < 0 || pos.y + 10 >= world->size.y) return false;
    for (int i = -11 * (k%4 != 3) + 1; i < 11 * (k%4 != 2); i++) {
        for (int j = -11 * (k%4 != 1) + 1; j < 11 * (k%4 != 0); j++) {
            if (world->map[pos.x + i][pos.y + j] != 0) {
                printf("test1\n");
                return false; // Espace non libre
            }
        }
    }
    return true; // Espace libre
}


Room* CreateRoom(World* world) {
    int l, L;
    Room* r = malloc(sizeof(Room));
    if (r == NULL) {
        PrintMessage("Erreur : Échec de l'allocation de mémoire pour la nouvelle salle.");
        exit(1);
    }
    r->RoomIndex = world->cnt;
    L = ((rand() % 4)*2) + 5; // Générer une longueur aléatoire entre 3 et 11 et impaire
    l = ((rand() % 4)*2) + 5; // Générer une largeur aléatoire entre 3 et 11 et impaire

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
    r->Tab2D = malloc(l * sizeof(int *));
    if (r->Tab2D == NULL) {
        printf("Erreur allocation de mémoire pour les coordonnées\n");
        exit(3);
    }

    for (int i = 0; i < l; i++) {
        r->Tab2D[i] = malloc(L * sizeof(int));
        if (r->Tab2D[i] == NULL) {
            printf("Erreur allocation de mémoire pour les coordonnées\n");
            exit(1);
        }
	}
        
    for(int i=0;i<l;i++){
	for (int j = 0; j < L; j++) {
            // Remplir le tableau 2D avec les caractères
            if(i == 0 && j == 0) r->Tab2D[i][j] = 10;
            else if(i == 0 && j == L-1) r->Tab2D[i][j] = 11;
            else if(i == l-1 && j == L-1) r->Tab2D[i][j] = 12;
            else if(i == l-1 && j == 0) r->Tab2D[i][j] = 13;
            else if (i == 0 || i == l - 1) r->Tab2D[i][j] = 14;
            else if (j == 0 || j == L - 1) r->Tab2D[i][j] = 15;
            else r->Tab2D[i][j] = 0;
        }
    }
    Coordinates p;
   int doorIndex;
   do {
        // Générer des coordonnées aléatoires à l'intérieur de la salle
        p.x = rand() % (r->size.x - 3) + 2; // Évitez les bords
        p.y = rand() % (r->size.y - 3) + 2;

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
   r->RoomMob.Position.x=p.x;
   r->RoomMob.Position.y=p.y;
   r->Tab2D[r->RoomMob.Position.x][r->RoomMob.Position.y]=mob.skin;
   mob.exist=1;
   
   Item item = BuildItem();
   Coordinates p2;
   int doorIndex2;
   do {
        // Générer des coordonnées aléatoires à l'intérieur de la salle
        p2.x = rand() % (r->size.x - 3) + 2; // Évitez les bords
        p2.y = rand() % (r->size.y - 3) + 2;

        // Vérifier si la position est devant une porte
        doorIndex2 = -1;
        for (int i = 0; i < 4; i++) {
            if (p2.x == r->TabDoor[i].position.x && p2.y == r->TabDoor[i].position.y) {
                doorIndex2 = i;
 		break; // La position est devant une porte, réessayer
            }
        }
    } while (doorIndex2 != -1 || p2.x==p.x || p2.y==p.y ); // Réessayer jusqu'à ce que la position ne soit pas devant une porte 
    r->RoomItem = item;
    r->RoomItem.position.x=p2.x;
    r->RoomItem.position.y=p2.y;
    r->Tab2D[r->RoomItem.position.x][r->RoomItem.position.y]=item.skin;
    item.exist=1;

    world->NbRooms++;
    return r;
}

void AddDoorToRoom(World* world, Room* r, int ObDoor){
    // Porte d'indice 0 -> porte Ouest
    // Porte d'indice 1 -> porte Est
    // Porte d'indice 2 -> porte Nord
    // Porte d'indice 3 -> porte Sud
    for (int k = 0; k < 2; ++k)
    {
        // probablitié d'avoir une porte 3/5
        if(k == ObDoor) continue;
        if (rand() % 5 <= 1 || world->NbDoors >= world->NbMax)  r->TabDoor[k].position.x = r->TabDoor[k].position.y = -1;
        else {
            r->TabDoor[k].position.x = rand() % (r->size.x - 2) + 1;
            r->TabDoor[k].position.y = k * (r->size.y - 1);
            Coordinates pos;
            pos.x =  r->TabDoor[k].position.x + r->position.x, pos.y =  r->TabDoor[k].position.y + r->position.y;
            if(!isSpaceFree(world, pos, k)) r->TabDoor[k].position.x = r->TabDoor[k].position.y = -1;
            else world->NbDoors++;
        }
    }
    for (int k = 2; k < 4; ++k)
    {
        if(k == ObDoor) continue;
        if(rand() % 5 <= 1 || world->NbDoors >= world->NbMax)  r->TabDoor[k].position.x = r->TabDoor[k].position.y = -1;
        else {
            r->TabDoor[k].position.x = (k%2) * (r->size.x - 1);
            r->TabDoor[k].position.y = rand() % (r->size.y - 2) + 1;
            Coordinates pos;
            pos.x =  r->TabDoor[k].position.x + r->position.x, pos.y =  r->TabDoor[k].position.y + r->position.y;
            if(!isSpaceFree(world, pos, k)) r->TabDoor[k].position.x = r->TabDoor[k].position.y = -1;
            else world->NbDoors++;
        }
    }


    for (int k = 0; k < 4; ++k) {
        if(k == ObDoor) continue;
        if(r->TabDoor[k].position.x != -1) r->Tab2D[r->TabDoor[k].position.x][r->TabDoor[k].position.y] = 30 +k;
        r->TabDoor[k].RoomIndex = r->RoomIndex;
        r->TabConnectedDoor[k]=100;
    }
}

Room* CreateFirstRoom(World* world){
    Room* r = CreateRoom(world);
    int x = 0, y =0;
    //find the coordinates of the player (define them in the middle of the map)
    GetMiddle(&x,&y,world->size);
    //define the position of the room in the map (we always save the top left corner)
    r->position.x = x-r->size.x/2;
    r->position.y = y-r->size.y/2;
    AddDoorToRoom(world, r, -1);
    return r;
}

void PrintfRoom(Player * P1, World* world){
    printf("\033c");
    printf("Le joueur est dans la salle %d\n",world->rooms[P1->roomIndex]->RoomIndex);
    for (int i = CameraRangeX; i <= CameraRangeX; i++) {
        for (int j = CameraRangeY; j <= CameraRangeY; j++){
            if(!i && !j) {
                printf("%s", Skins[0]);
            }
            switch(world->map[i][j]){
            case 10:
            	printf("╔");
            	break;
            case 11:
            	printf("╗");
            	break;
            case 12:
            	printf("╝");
            	break;
            case 13:
            	printf("╚");
            	break;
            case 14:
            	printf("═");
            	break;
            case 15:
            	printf("║");
            	break;
            case 0:
            	printf(" ");
            	break;
            case 30:
            	printf("╠");
            	break;
            case 31:
            	printf("╣");
            	break;
            case 32:
            	printf("╦");
            	break;
            case 33:
            	printf("╦");
            	break;
            case 50:
            	printf("▓");
            	break;
            case 60:
            	printf("🗡");
            	break;
            case 61:
            	printf("🛡");
            	break;
            case 62:
            	printf("♡");
            	break;
            default:
		printf(" ");
		break;	
            
            }
        printf("\n");
        }
    }
}

void GetMiddle(int *x,int *y, Coordinates Size){

    *x=Size.x/2;
    *y=Size.y/2;

}


int findDoor(Player *P1, World * world) {
    // Si la position du joueur ne correspond à une porte, retourne l'indice de celle ci
    for (int i = 0; i < 4; i++) {
        if (P1->Position.x == world->rooms[P1->roomIndex]->TabDoor[i].position.x + world->rooms[P1->roomIndex]->position.x 
        && P1->Position.y == world->rooms[P1->roomIndex]->TabDoor[i].position.y + world->rooms[P1->roomIndex]->position.y) {
            return i;
        }
    }
    // Si la position du joueur ne correspond à aucune porte, retourne -1

    return -1;
}


void roomCreationInGame(Player *P1, World* world) {
    
    // Créer la nouvelle salle
    int CurrentDoorIndex = findDoor(P1,world);
    // Le deuxième argument est pour créer obligatoirement la porte qui mène à la nouvelle chambre
    Room* NextRoom = CreateRoom(world);
    // Mettre à jour le tableau World avec un pointeur vers la nouvelle salle
    world->rooms[world->cnt] = NextRoom;

    // Trouver la porte par laquelle le joueur entre dans la nouvelle salle
    P1->Position.x += MovX[CurrentDoorIndex];
    P1->Position.y += MovY[CurrentDoorIndex];
    if(CurrentDoorIndex==0 || CurrentDoorIndex==2){
     world->map[P1->Position.x][P1->Position.y] = 82;
    }
    else if(CurrentDoorIndex==1 || CurrentDoorIndex==3){
     world->map[P1->Position.x][P1->Position.y] = 81;
    }
    P1->Position.x += MovX[CurrentDoorIndex];
    P1->Position.y += MovY[CurrentDoorIndex];   
    // Créer la porte de la nouvelle salle où le joueur sortira
    // et établir une liaison entre les deux portes
    // l'est et l'ouest se connectent et le nord avec le sud
    // Donc 0 <-> 1 et 2 <-> 3
    // Donc il suffit de changer la premiére bit pour trouver l'autre porte : on peut utiliser l'operation XOR.
    int NextDoorIndex = CurrentDoorIndex ^ 1;

    if(NextDoorIndex >= 2){
        NextRoom->TabDoor[NextDoorIndex].position.x = (NextDoorIndex%2) * (NextRoom->size.x - 1);
        NextRoom->TabDoor[NextDoorIndex].position.y = rand() % (NextRoom->size.y - 2) + 1;
    } else {
        NextRoom->TabDoor[NextDoorIndex].position.x = rand() % (NextRoom->size.x - 2) + 1;
        NextRoom->TabDoor[NextDoorIndex].position.y = NextDoorIndex * (NextRoom->size.y - 1);
    }
    NextRoom->Tab2D[NextRoom->TabDoor[NextDoorIndex].position.x][NextRoom->TabDoor[NextDoorIndex].position.y] = 30+NextDoorIndex;
    NextRoom->TabDoor[NextDoorIndex].RoomIndex = NextRoom->RoomIndex;   


    
    world->rooms[P1->roomIndex]->TabConnectedDoor[CurrentDoorIndex] = NextRoom->RoomIndex;
    NextRoom->TabConnectedDoor[NextDoorIndex] = P1->roomIndex;

    NextRoom->position.x = P1->Position.x - world->rooms[NextRoom->RoomIndex]->TabDoor[NextDoorIndex].position.x;
    NextRoom->position.y = P1->Position.y - world->rooms[NextRoom->RoomIndex]->TabDoor[NextDoorIndex].position.y;
    //  Ajouter les autres portes 
    AddDoorToRoom(world,NextRoom,NextDoorIndex);

    // Mettre à jour la salle actuelle du joueur avec la nouvelle salle
    P1->roomIndex = NextRoom->RoomIndex;
    AddRoomToWorld(world,NextRoom);
}



void doorInteraction(Player* P1, World* world, int dir){
    int choice = -1;
    int verif;
    do{
        PrintMessage("Voulez-vous aller dans la prochaine salle ? Oui : 1 Non : 0");

        verif=scanf("%d", &choice);
        vide_buffer();


    } while (choice!=1 && choice !=0 && verif !=-1);
    if(choice == 1){
        P1->Position.x += MovX[dir];
        P1->Position.y += MovY[dir];
        (world->cnt)+=1;
        roomCreationInGame(P1, world);
    }
}

void addToInventory(Player *P1, Room * room){
   for(int i=0; i<4; i++){
	if(P1->Inventory[i].exist == 0){
		P1->Inventory[i]=room->RoomItem;
		P1->Inventory[i].exist=1;
		printf("L'objet c'est %s\n" ,P1->Inventory[i].skin);
		break;
        }
   	
   }
   if(room->RoomItem.exist!=0){
	printf("Inventaire plein !\n");
   }
}

void Travel(Player* P1, World* world){
    char input;
 	int verif;	
 	do{
        PrintfRoom(P1, world);
	printf("\033[35m○"
           "◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈"
           "○\033[0m     \033[33m┌─────────────────────┐\033[0m\n");
    printf("     \033[35mSTATISTIQUES\033[0m               \033[33m│  Quelle direction?  │\033[0m\n"
           "     \033[37mPartie de  : %s\033[0m\033[33m\n"
           "                                 \033[0m  ⭡ : z              \033[33m \033[0m\n"
           "     \033[32mVie : %.2f\033[0m               \033[33m \033[0m  ⭠ : q              \033[33m \033[0m\n"
           "     \033[31mAttaque : %.2f\033[0m            \033[33m \033[0m  ⭣ : s              \033[33m \033[0m\n"
           "     \033[36mExpérience : %.2f\033[0m          \033[33m│\033[0m  ⭢ : d   Menu : 0   \033[33m│\033[0m\n", P1->Name, P1->Hp, P1->Atk, P1->Exp);
    printf("\033[35m○"
           "◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈◈"
           "○\033[0m     \033[33m└─────────────────────┘\033[0m"
           "\n\n");
printf("\033[36m◑"
           "◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡"
           "◐\033[0m"
           "\n");
    // Afficher l'inventaire
    printf("     \033[36mINVENTAIRE\033[0m\n\n");
    for (int i = 0; i < 4; i++) {
        if(P1->Inventory[i].exist!=0){
        printf("     \033[33mEmplacement %d: %s\033[0m\n", i + 1, P1->Inventory[i].skin);
    	}
	else{printf("     \033[33mEmplacement %d : Vide\033[0m\n",i+1);}
    }

    printf("\033[36m◑"
           "◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡◠◡"
           "◐\033[0m"
           "\n\n");

        verif=scanf("%c", &input);
        vide_buffer();
	} while (input!='z' && input!='q' && input!='s' && input!='d' && input!='0' && verif !=-1);

    int choice;
    GameState GameState;
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
	
	GameState.world = *world;
	GameState.player = *P1;
	menuInGame(GameState);
     break; 
   }
   choice--;
    if (world->map[P1->Position.x  + MovX[choice]][P1->Position.y  + MovY[choice]] == 30+choice){
        if(world->rooms[P1->roomIndex]->TabConnectedDoor[choice]==100) {
            doorInteraction(P1, world,choice);
        }
        else{
            P1->Position.x += 3*MovX[choice];
            P1->Position.y += 3*MovY[choice];
            P1->roomIndex = world->rooms[P1->roomIndex]->TabConnectedDoor[choice];       
	}
    }
    if (world->map[P1->Position.x + MovX[choice]][P1->Position.y + MovY[choice]] == 0){
        P1->Position.x += MovX[choice];
        P1->Position.y += MovY[choice];
    }
    else if (world->map[P1->Position.x + MovX[choice]][P1->Position.y + MovY[choice]] == 50){
        int choix;
        int verif;
        do{
		printf("ça fight ce bug ou quoi ?\n");
		printf("Oui : 1 / J'ai peur : 0\n");

		verif=scanf("%d", &choix);
        	vide_buffer();
	} while (choix!=1 && choix!=0 && verif !=-1);
	switch(choix){
		case 1:
			combat(P1,&(world->rooms[P1->roomIndex]->RoomMob), world);
			break;
		default:
			break;
	}
    }
    else if (world->map[P1->Position.x + MovX[choice]][P1->Position.y + MovY[choice]] == 60){
        int choix;
	int verif;
	do{
		printf("Voulez-vous ajouter l'épée à ton inventaire ? (+X d'Attaque)\n");
		printf("Oui : 1 / Non : 0\n");

		verif=scanf("%d", &choix);
        	vide_buffer();

	} while (choix!=1 && choix!=0 && verif !=-1);

        switch(choix){
		case 1:
			world->rooms[P1->roomIndex]->Tab2D[world->rooms[P1->roomIndex]->RoomItem.position.x][world->rooms[P1->roomIndex]->RoomItem.position.y]=0;
			world->rooms[P1->roomIndex]->RoomItem.exist=0;
			AddRoomToWorld(world, world->rooms[P1->roomIndex]);
			addToInventory(P1, world->rooms[P1->roomIndex]);
			
			break;
		default:
			break;
	}

    }
    else if (world->map[P1->Position.x + MovX[choice]][P1->Position.y + MovY[choice]] == 61){
        int choix;
	int verif;
	do{
		printf("Voulez-vous le bouclier à ton inventaire ? (+X de défense)\n");
		printf("Oui : 1 / Non : 0\n");

		verif=scanf("%d", &choix);
        	vide_buffer();
	} while (choix!=1 && choix!=0 && verif !=-1);

        switch(choix){
		case 1:
			world->rooms[P1->roomIndex]->Tab2D[world->rooms[P1->roomIndex]->RoomItem.position.x][world->rooms[P1->roomIndex]->RoomItem.position.y]=0;
			world->rooms[P1->roomIndex]->RoomItem.exist=0;
			AddRoomToWorld(world, world->rooms[P1->roomIndex]);
			addToInventory(P1, world->rooms[P1->roomIndex]);
			
			
			break;
		default:
			break;
	}

    }
    else if (world->map[P1->Position.x + MovX[choice]][P1->Position.y + MovY[choice]] == 62){
        int choix;
	int verif;
	do{
		printf("Voulez-vous ajouter du soin à ton inventaire ? ?\n");
		printf("Oui : 1 / Non : 0\n");
		
		verif=scanf("%d", &choix);
        	vide_buffer();

	} while (choix!=1 && choix!=0 && verif !=-1);

        switch(choix){
		case 1:
			world->rooms[P1->roomIndex]->Tab2D[world->rooms[P1->roomIndex]->RoomItem.position.x][world->rooms[P1->roomIndex]->RoomItem.position.y]=0;
			world->rooms[P1->roomIndex]->RoomItem.exist=0;			
			AddRoomToWorld(world, world->rooms[P1->roomIndex]);	
			addToInventory(P1, world->rooms[P1->roomIndex]);
			break;
		default:
			break;
	}

    }

}
