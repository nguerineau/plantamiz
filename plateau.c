//
// Created by nicol on 10/20/2024.
//
#include <stdio.h>
#include "plateau.h"

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


void cree_plateau() {


}

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

