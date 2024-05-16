#include "menuInGame.h"
#include "fonction.h"
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
    P1.skin='A';
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
    L = rand() % 8 + 5; // Générer une longueur aléatoire entre 3 et 11
    l = rand() % 8 + 5; // Générer une largeur aléatoire entre 3 et 11

    // Ajuster les dimensions si nécessaire pour éviter les salles de type couloir
    if (l - L > 3){
        L+=rand() % 3 + 2;
    }
    if (L - l > 3){
        l+=rand() % 3 + 2;
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
            if (i == 0 && j == 0) {
                r.Tab2D[i][j] = '1';
            } else if (i == 0 && j == L - 1) {
                r.Tab2D[i][j] = '2';
            } else if (i == l - 1 && j == 0) {
                r.Tab2D[i][j] = '3';
            } else if (i == l - 1 && j == L - 1) {
                r.Tab2D[i][j] = '4';
            } else if (i == 0 || i == l - 1) {
                r.Tab2D[i][j] ='6';
            } else if (j == 0 || j == L - 1) {
                r.Tab2D[i][j] = '5';
            } else {
                r.Tab2D[i][j] = '0';
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

    r.Tab2D[0][r.TabDoor[0].position.x] = 'N';
    r.Tab2D[l - 1][r.TabDoor[2].position.x] = 'S';
    r.Tab2D[r.TabDoor[1].position.y][L - 1] = 'E';
    r.Tab2D[r.TabDoor[3].position.y][0] = 'W';

    r.TabConnectedDoor[0]=NULL;
    r.TabConnectedDoor[1]=NULL;
    r.TabConnectedDoor[2]=NULL;
    r.TabConnectedDoor[3]=NULL;
    r.TabDoor[0].NextRoomIndex=-1;
    r.TabDoor[1].NextRoomIndex=-1;
    r.TabDoor[2].NextRoomIndex=-1;
    r.TabDoor[3].NextRoomIndex=-1;
    r.roomIndex=0;
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
    printf("\033c");
    //printf("Largeur %d\n",room.l);
    //printf("Longueur : %d\n", room.L);
    printf("Coo du joueur : %d x , %d y\n",P1->Position.x,P1->Position.y);
    printf("Adresse de la salle du joueur : %p\n",P1->room);
    printf("Joueur est dans la salle %d\n",P1->room->roomIndex);
    for (int i = 0; i < P1->room->l; i++) {
        for (int j = 0; j < P1->room->L; j++) {

            if(P1->room->Tab2D[i][j]=='A'){
                printf("A");
            }
            if(P1->room->Tab2D[i][j]=='0'){
                printf(" ");
            }
            if(P1->room->Tab2D[i][j]=='1'){
                printf("\U00002554");
            }
            if(P1->room->Tab2D[i][j]=='2'){
                printf("\U00002557");
            }
            if(P1->room->Tab2D[i][j]=='3'){
                printf("\U0000255A");
            }
            if(P1->room->Tab2D[i][j]=='4'){
                printf("\U0000255D");
            }
            if(P1->room->Tab2D[i][j]=='5'){
                printf("\U00002551");
            }
            if(P1->room->Tab2D[i][j]=='6'){
                printf("\U00002550");
            }
            if(P1->room->Tab2D[i][j]=='N'){
                printf("N");
            }
            if(P1->room->Tab2D[i][j]=='S'){
                printf("S");
            }
            if(P1->room->Tab2D[i][j]=='E'){
                printf("E");
            }
            if(P1->room->Tab2D[i][j]=='W'){
                printf("W");
            }


        }
        printf("\n");
    }
    printf("\n");
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


void roomCreationInGame(Player *P1, Room** World,int  cpt) {
    // Allouer de la mémoire pour la nouvelle salle
    Room *NextRoom = (Room*)malloc(sizeof(Room));
    if (NextRoom == NULL) {
        printf("Erreur : Échec de l'allocation de mémoire pour la nouvelle salle.\n");
        exit(1);
    }

    // Créer la nouvelle salle
    *NextRoom = CreateRoom();

    // Mettre à jour le tableau World avec un pointeur vers la nouvelle salle
    World[cpt] = NextRoom;

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
            P1->room->TabDoor[0].NextRoomIndex=cpt;
            NextRoom->TabDoor[2].NextRoomIndex=P1->room->roomIndex;
            NextRoom->roomIndex=cpt;
            break;
        case 1:
            // Le joueur entre par la porte est de la salle actuelle
            P1->room->TabConnectedDoor[1] = &(NextRoom->TabDoor[3]);
            NextRoom->TabConnectedDoor[3] = &(P1->room->TabDoor[1]);
            // Définir les coordonnées du joueur dans la nouvelle salle
            P1->Position.x = P1->room->TabConnectedDoor[1]->position.x;
            P1->Position.y = P1->room->TabConnectedDoor[1]->position.y;
            P1->room->TabDoor[1].NextRoomIndex=cpt;
            NextRoom->TabDoor[3].NextRoomIndex=P1->room->roomIndex;
            NextRoom->roomIndex=cpt;
            break;
        case 2:
            // Le joueur entre par la porte sud de la salle actuelle
            P1->room->TabConnectedDoor[2] = &(NextRoom->TabDoor[0]);
            NextRoom->TabConnectedDoor[0] = &(P1->room->TabDoor[2]);
            // Définir les coordonnées du joueur dans la nouvelle salle
            P1->Position.x = P1->room->TabConnectedDoor[2]->position.x;
            P1->Position.y = P1->room->TabConnectedDoor[2]->position.y;
            P1->room->TabDoor[2].NextRoomIndex=cpt;
            NextRoom->TabDoor[0].NextRoomIndex=P1->room->roomIndex;
            NextRoom->roomIndex=cpt;
            break;
	case 3:
            // Le joueur entre par la porte ouest de la salle actuelle
            P1->room->TabConnectedDoor[3] = &(NextRoom->TabDoor[1]);
            NextRoom->TabConnectedDoor[1] = &(P1->room->TabDoor[3]);
            // Définir les coordonnées du joueur dans la nouvelle salle
            P1->Position.x = P1->room->TabConnectedDoor[3]->position.x;
            P1->Position.y = P1->room->TabConnectedDoor[3]->position.y;
            P1->room->TabDoor[3].NextRoomIndex=cpt;
            NextRoom->TabDoor[1].NextRoomIndex=P1->room->roomIndex;
            NextRoom->roomIndex=cpt;
            break;
	default:
            // Gérer le cas où l'index de la porte n'est pas valide
            printf("Erreur: Index de porte invalide.\n");
            break;
    }

    // Mettre à jour la salle actuelle du joueur avec la nouvelle salle
    P1->room = World[cpt];
    // Mettre à jour l'affichage du joueur dans la nouvelle salle
    P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
}

void doorInteraction(Player* P1, Room** World,int  cpt, char dir){
    int choice;
    printf("Voulez-vous aller dans la prochaine salle ? 1 oui 0 non\n");
    scanf("%d", &choice);
    if(choice == 1){
        roomCreationInGame(P1, World,cpt);
    }
    else if(choice == 0){
	switch (dir){
		case 's':
			P1->Position.y-=1;
			P1->room->Tab2D[P1->Position.y][P1->Position.x]=P1->skin;
			break; 
		case 'n':
			P1->Position.y+=1;
			P1->room->Tab2D[P1->Position.y][P1->Position.x]=P1->skin;
			break;
		case 'e':
			P1->Position.x-=1;
			P1->room->Tab2D[P1->Position.y][P1->Position.x]=P1->skin;
			break;
		case 'w':
			P1->Position.x+=1;
			P1->room->Tab2D[P1->Position.y][P1->Position.x]=P1->skin;
			break;
	}
    }
    else{
        return;
    }
}

void Travel(Player* P1, Room** World, int* cpt) {
    char choice;
    char buffer[10]; // Utilisation d'un buffer pour lire l'entrée utilisateur
    
    printf("\033[33m\U0000256D"
           "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
           "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
           "\U00002500"
           "\U0000256E\033[0m"
           "\n");
    printf("\033[33m\U00002502  Quelle direction?  \U00002502\033[0m\n"
           "\033[33m\U00002502\033[0m  \U000025B2 : z              \033[33m\U00002502\033[0m\n"
           "\033[33m\U00002502\033[0m  \U000025C0 : q              \033[33m\U00002502\033[0m\n"
           "\033[33m\U00002502\033[0m  \U000025BC : s              \033[33m\U00002502\033[0m\n"
           "\033[33m\U00002502\033[0m  \U000025B6 : d              \033[33m\U00002502\033[0m\n"
           "\033[33m\U00002502\033[0m  Menu : 0           \033[33m\U00002502\033[0m\n");
    printf("\033[33m\U00002570"
           "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
           "\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500\U00002500"
           "\U00002500"
           "\U0000256F\033[0m"
           "\n\n");
    printf("\033[35m\U000025CF"
           "\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF"
           "\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF\U000025BF"
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
           "\U000025CF\033[0m"
           "\n\n");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Assurez-vous que l'entrée ne contient qu'un seul caractère suivi d'un '\n'
        if (sscanf(buffer, " %c", &choice) == 1 && buffer[1] == '\n') {
            
	switch (choice) {
                case 'q':
                    if (P1->room->Tab2D[P1->Position.y][P1->Position.x - 1] == '0') {
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = '0';
                        if (P1->Position.x == P1->room->TabDoor[1].position.x && P1->Position.y == P1->room->TabDoor[1].position.y) {
                            P1->room->Tab2D[P1->Position.y][P1->Position.x] = 'E';
                        }
                        P1->Position.x--;
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                    } else if (P1->room->Tab2D[P1->Position.y][P1->Position.x - 1] == 'W') {
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = '0';
                        char dir = 'w';
			if (P1->room->TabConnectedDoor[3] == NULL) {
                            (*cpt)++;
                            P1->Position.x = P1->Position.x - 1;
                            doorInteraction(P1, World, *cpt, dir);
                        } else {
                            P1->Position.x = P1->room->TabConnectedDoor[3]->position.x;
                            P1->Position.y = P1->room->TabConnectedDoor[3]->position.y;
                            P1->room = World[P1->room->TabDoor[3].NextRoomIndex];
                            P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                        }
                    }
                    break;
                case 'd':
                    if (P1->room->Tab2D[P1->Position.y][P1->Position.x + 1] == '0') {
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = '0';
                        if (P1->Position.x == P1->room->TabDoor[3].position.x && P1->Position.y == P1->room->TabDoor[3].position.y) {
                            P1->room->Tab2D[P1->Position.y][P1->Position.x] = 'W';
                        }
                        P1->Position.x++;
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                    } else if (P1->room->Tab2D[P1->Position.y][P1->Position.x + 1] == 'E') {
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = '0';
                        char dir = 'e';
			if (P1->room->TabConnectedDoor[1] == NULL) {
                            (*cpt)++;
                            P1->Position.x = P1->Position.x + 1;
                            doorInteraction(P1, World, *cpt, dir);
                        } else {
                            P1->Position.x = P1->room->TabConnectedDoor[1]->position.x;
                            P1->Position.y = P1->room->TabConnectedDoor[1]->position.y;
                            P1->room = World[P1->room->TabDoor[1].NextRoomIndex];
                            P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                        }
                    }
                    break;
                case 's':
                    if (P1->room->Tab2D[P1->Position.y + 1][P1->Position.x] == '0') {
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = '0';
                        if (P1->Position.x == P1->room->TabDoor[0].position.x && P1->Position.y == P1->room->TabDoor[0].position.y) {
                            P1->room->Tab2D[P1->Position.y][P1->Position.x] = 'N';
                        }
                        P1->Position.y++;
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                    } else if (P1->room->Tab2D[P1->Position.y + 1][P1->Position.x] == 'S') {
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = '0';
                        char dir = 's';
			if (P1->room->TabConnectedDoor[2] == NULL) {
                            (*cpt)++;
                            P1->Position.y = P1->Position.y + 1;
                            doorInteraction(P1, World, *cpt, dir);
                        } else {
                            P1->Position.x = P1->room->TabConnectedDoor[2]->position.x;
                            P1->Position.y = P1->room->TabConnectedDoor[2]->position.y;
                            P1->room = World[P1->room->TabDoor[2].NextRoomIndex];
                            P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                        }
                    }
                    break;
                case 'z':
                    if (P1->room->Tab2D[P1->Position.y - 1][P1->Position.x] == '0') {
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = '0';
                        if (P1->Position.x == P1->room->TabDoor[2].position.x && P1->Position.y == P1->room->TabDoor[2].position.y) {
                            P1->room->Tab2D[P1->Position.y][P1->Position.x] = 'S';
                        }
                        P1->Position.y--;
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                    } else if (P1->room->Tab2D[P1->Position.y - 1][P1->Position.x] == 'N') {
                        P1->room->Tab2D[P1->Position.y][P1->Position.x] = '0';
                        char dir = 'n';
			if (P1->room->TabConnectedDoor[0] == NULL) {
                            (*cpt)++;
                            P1->Position.y = P1->Position.y - 1;
                            doorInteraction(P1, World, *cpt, dir);
                        } else {
                            P1->Position.x = P1->room->TabConnectedDoor[0]->position.x;
                            P1->Position.y = P1->room->TabConnectedDoor[0]->position.y;
                            P1->room = World[P1->room->TabDoor[0].NextRoomIndex];
                            P1->room->Tab2D[P1->Position.y][P1->Position.x] = P1->skin;
                        }
                    }
                    break;
                case '0':
                    menuInGame();
                default:
                    printf("Entrée invalide! Veuillez entrer une direction valide.\n");
                    break;
            }
        } else {
            printf("Erreur: Veuillez entrer un seul caractère.\n");
        }
    } else {
        printf("Erreur lors de la lecture de l'entrée.\n");
    }
}

void combat(Player *player, Mob *mob) {
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    // Boucle de combat jusqu'à ce que l'un des participants n'ait plus de points de vie
    while (player->Hp > 0 && mob->Hp > 0) {
        // Le joueur attaque le monstre
        float player_damage = player->Atk * (1 - (mob->Esq / 100)); // Calcul des dégâts du joueur
        mob->Hp -= player_damage; // Réduction des points de vie du monstre

        // Le monstre attaque le joueur
        float mob_damage = mob->Atk * (1 - (player->Esq / 100)); // Calcul des dégâts du monstre
        player->Hp -= mob_damage; // Réduction des points de vie du joueur

        // Affichage des dégâts infligés à chaque tour
        printf("%s inflige %.2f dégâts au Mob\n", player->Name, player_damage);
        printf("Le Mob inflige %.2f dégâts à %s.\n", mob_damage, player->Name);
    }

    // Affichage du résultat du combat
    if (player->Hp <= 0) {
        printf("%s a été vaincu par la créature !\n", player->Name);
    } else {
        printf("%s a vaincu la créature !\n", player->Name);
    }
}

void Clock(){
    int timer = 60;
    while (timer > 0) {
        printf("Temps restant : %d secondes\n", timer);
        sleep(1); // Pause d'une seconde
        timer--; // Décrémente le timer
    }

    printf("Temps écoulé !\n");

    return 0;
}
