//
// Created by nicol on 10/20/2024.
//


#ifndef PLATEAU_H
#define PLATEAU_H

#include "Contrat_plateau.h"

#define ROWS 7
#define COLS 7
#define nombreTotalPion 5
#define OBJECTIF_CONTRAT_ATTEINT 50
#define flecheHaut 72
#define flecheDroite 77
#define flecheGauche 75
#define flecheBas 80






void color(int couleurDuTexte, int couleurDeFond);
char generateRandomItem();
int checkGroup(char grid[ROWS][COLS], int row, int col, char item);
void gotolicol(int x, int y);

void GroupementRectangle(char grid[ROWS][COLS], int *points, int pointsItem[5]);
void GroupementVerticalHorizontal (char grid[ROWS][COLS], int *points, int pointsItem[5]);
void GroupementH(char grid[ROWS][COLS], int *points, int pointsItem[nombreTotalPion]);
int Contrats(int pointsItem[nombreTotalPion], int coups);

void TomberItems(char grid[ROWS][COLS]);

void AffichageCurseur(int curseurX, int curseurY);
void Deplacement(char deplacement, int *curseurX, int *curseurY);

void Score(int points, int pointsItem[nombreTotalPion], int vie, int coups);
void ObjectifsItem (int objectifs[nombreTotalPion], int pointsItem[nombreTotalPion]);
void initializeGrid(char grid[ROWS][COLS]);
void displayGrid(char grid[ROWS][COLS]);

extern ContratPlateau contrats[];
extern int nombreContrat;
extern int niveau;

#endif //PLATEAU_H
