#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void CreateRoom() {
    int l, L;
    L = rand() % 7 + 6; // Générer une longueur aléatoire entre 6 et 12
    l = L - (rand() % 5); // Générer une largeur aléatoire qui assure que la différence est de 4 max
    printf("Longueur: %d\n", L);
    printf("Largeur: %d\n", l);

    // Création du tableau 2D pour représenter la room
    char room[l][L];

    // Remplissage du tableau pour les bords et les coins
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < L; j++) {
            if (i == 0 && j == 0) {
                room[i][j] = '1';
            }
            else if (i == 0 && j == L - 1){
                room[i][j] = '2';
            }
            else if (i == l - 1 && j == 0){
                room[i][j] = '3';
            }
            else if (i == l - 1 && j == L - 1){
                room[i][j] = '4';
            }
            else if (i == 0 || i == l - 1) {
                room[i][j] = '-';
            }
            else if (j == 0 || j == L - 1) {
                room[i][j] = '|';
            }
            else {
                room[i][j] = ' '; // Intérieur de la room
            }
        }
    }

    // Affichage du tableau représentant la room
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < L; j++) {
            printf("%c", room[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));

    CreateRoom();
    return 0;
}