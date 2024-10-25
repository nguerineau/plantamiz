//
// Created by nicol on 10/20/2024.
//
#include <stdio.h>
#include "plateau.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Pour la gestion des couleurs

/***
struct plateau { // revoir l'utilité de cettet element
    unsigned int longueur; //longeur plateau
    unsigned int hauteur ; //hauteur plateau
    char *nom; // nom du plateau
    int objectif_soleil; // quantité de soleil demandé pour le contract
    int objectif_fraise; // quantité de fraise demandé pour le contract
    int objectif_pomme; // quantité de pomme demandé pour le contract
    int objectif_oignon; // quantité de oignon demandé pour le contract
    int objectif_mandarine; // quantité de mandarine demandé pour le contract
};


void init_plateau(int tableau[ligne][colonne]) {
    int i, j;
    for (i = 0; i < ligne; i++) {
        for (j = 0; j < colonne; j++) {
            tableau[i][j] = 0;
        }
    }

}

void display_plateau(int tableau[ligne][colonne]) {
    int i,j;
    printf("                                        PLANTAMIZ \n");
    for(i=0; i<ligne;i++){
        for(j=0; j<colonne; j++){
            printf("%2d",tableau[i][j]);
        }
        printf("\n");
    }

}
***/

// Liste des items
char items[] = {'S', 'F', 'P', 'O', 'M'};


// Fonction pour changer la couleur dans la console
void color(int couleurDuTexte, int couleurDeFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

// Fonction pour générer un item aléatoire
char generateRandomItem() {
    return items[rand() % 5];
}

// Vérifie si un groupe de 3 est formé horizontalement ou verticalement
int checkGroup(char grid[ROWS][COLS], int row, int col, char item) {
    // Vérification horizontale (gauche)
    if (col >= 2 && grid[row][col-1] == item && grid[row][col-2] == item) {
        return 1;
    }
    // Vérification verticale (au-dessus)
    if (row >= 2 && grid[row-1][col] == item && grid[row-2][col] == item) {
        return 1;
    }
    return 0;
}


// Fonction d'initialisation de la grille sans groupes de 3 ou plus
void initializeGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char item;
            do {
                item = generateRandomItem();
            } while (checkGroup(grid, i, j, item));  // Regénérer l'item s'il forme un groupe
            grid[i][j] = item;
        }
    }
}

// Fonction pour afficher la grille avec couleurs
void displayGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Attribution des couleurs en fonction des items
            switch(grid[i][j]) {
                case 'S': color(14, 0); break; // Jaune pour Soleil
                case 'F': color(4, 0); break;  // Rouge pour Fraise
                case 'P': color(10, 0); break; // Vert pour Pomme
                case 'O': color(6, 0); break;  // Orange pour Oignon
                case 'M': color(5, 0); break;  // Violet pour Mandarine
            }
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    color(15, 0); // Remettre le texte en blanc
}

