//
// Created by nicol on 10/20/2024.
//


#ifndef PLATEAU_H
#define PLATEAU_H



#define ROWS 25
#define COLS 45
#define nombreTotalPion 5
#define OBJECTIF_CONTRAT_ATTEINT 50
#define flecheHaut 72
#define flecheDroite 77
#define flecheGauche 75
#define flecheBas 80

typedef struct {
    int objectifsContrat[nombreTotalPion]; // Objectifs pour chaque type de pion pour les trois niveaux
    int coupsMax; // Coups maximum
} ContratPlateau;

enum pion {
    soleil, fraise, pomme, oignons, mandarine
};



void permuterItems(int *curseurX, int *curseurY, int *selectionX, int *selectionY,char grid[ROWS][COLS], int *points, int pointsItem[nombreTotalPion]);
int getItemIndex(char item);
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

int Score(int points, const int pointsItem[nombreTotalPion], int vies, int coups, const int objectifsContrat[nombreTotalPion]);
void ObjectifsItem(const int objectifsContrat[nombreTotalPion], const int pointsItem[nombreTotalPion]);
void initializeGrid(char grid[ROWS][COLS]);
void displayGrid(char grid[ROWS][COLS],int curseurX, int curseurY);
int Aucun_Item_identique(char grid[ROWS][COLS],int ligne, int colonne, char item);
extern ContratPlateau contrats[];
extern int nombreContrat;
extern int niveau;

#endif //PLATEAU_H
