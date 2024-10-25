#include <stdio.h>
#include "plateau.h"
#include "pion.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main(void) {
    /**
     int plateau[ligne][colonne];
    init_plateau(plateau);
    display_plateau(plateau);
    while(1);
    **/

    char grid[ROWS][COLS];

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Initialisation et affichage de la grille
    initializeGrid(grid);
    displayGrid(grid);
    return 0;
}
