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

void color(int couleurDuTexte, int couleurDeFond);
char generateRandomItem();
int checkGroup(char grid[ROWS][COLS], int row, int col, char item);
void initializeGrid(char grid[ROWS][COLS]);
void displayGrid(char grid[ROWS][COLS]);

#endif //PLATEAU_H
