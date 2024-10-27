//
// Created by nicol on 10/20/2024.
//

#ifndef PLATEAU_H
#define PLATEAU_H
/**
#define ligne 25
#define colonne 45

//fonction
void init_plateau();
void display_plateau();
**/

#define ROWS 25
#define COLS 45
#include "pion.h"
#include "Contrat_plateau.h"
#define OBJECTIF_CONTRAT_ATTEINT 50




void color(int couleurDuTexte, int couleurDeFond);
char generateRandomItem();
int checkGroup(char grid[ROWS][COLS], int row, int col, char item);
void Instruction();
void gotolicol(int x, int y);
void GroupementRectangle(char grid[ROWS][COLS], int *points, int pointsItem[5]);
void Groupement (char grid[ROWS][COLS], int *points, int pointsItem[5]);
int Contrats(int pointsItem[nombreTotalPion], int coups);
//int finNiveau(int points, int *vie);
void TomberItems(char grid[ROWS][COLS]);
void AffichageCurseur(int curseurX, int curseurY);
void Deplacement(char deplacement, int *curseurX, int *curseurY);
void Score(int points, int pointsItem[5], int vie);
void initializeGrid(char grid[ROWS][COLS]);
void displayGrid(char grid[ROWS][COLS]);

#endif //PLATEAU_H
