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
                        if (P1->room->TabConnectedDoor[3] == NULL) {
                            (*cpt)++;
                            P1->Position.x = P1->Position.x - 1;
                            doorInteraction(P1, World, *cpt);
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
                        if (P1->room->TabConnectedDoor[1] == NULL) {
                            (*cpt)++;
                            P1->Position.x = P1->Position.x + 1;
                            doorInteraction(P1, World, *cpt);
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
                        if (P1->room->TabConnectedDoor[0] == NULL) {
                            (*cpt)++;
                            P1->Position.y = P1->Position.y + 1;
                            doorInteraction(P1, World, *cpt);
                        } else {
                            P1->Position.x = P1->room->TabConnectedDoor[0]->position.x;
                            P1->Position.y = P1->room->TabConnectedDoor[0]->position.y;
                            P1->room = World[P1->room->TabDoor[0].NextRoomIndex];
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
                        if (P1->room->TabConnectedDoor[2] == NULL) {
                            (*cpt)++;
                            P1->Position.y = P1->Position.y - 1;
                            doorInteraction(P1, World, *cpt);
                        } else {
                            P1->Position.x = P1->room->TabConnectedDoor[2]->position.x;
                            P1->Position.y = P1->room->TabConnectedDoor[2]->position.y;
                            P1->room = World[P1->room->TabDoor[2].NextRoomIndex];
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
