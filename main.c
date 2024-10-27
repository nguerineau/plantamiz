#include <stdio.h>
#include "plateau.h"
#include "Selection_cordonnées.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Menu.h"
#include <conio.h>

int main(void)
{
    /**
     int plateau[ligne][colonne];
    init_plateau(plateau);
    display_plateau(plateau);
    while(1);
    **/
    int points = 0; // stocker le point total
    int pointItem[5] = {0}; // Pour stocker les points pour chaque item
    int curseurX = 0, curseurY = 0,vies = 5;
    Selection selectionner[2] = { { -1, -1 }, { -1, -1 } };
    int opt_menu = Menu();


    switch (opt_menu) {
        case 1://cas nouvelle partie
        char grid[ROWS][COLS];

        // Initialiser le générateur de nombres aléatoires
        srand(time(NULL));

        // Initialisation et affichage de la grille
        initializeGrid(grid);
        while (vies>0)
        {
            system("cls");
            displayGrid(grid);
            Score(points, pointItem, vies);
            printf("Utilisez Z-Q-S-D ou par les fleches pour déplacer le curseur, espace pour sélectionner item à déplacer.\n");

            char deplacement = _getch(); // Récupère la touche pressée
            if (deplacement == ' ') { // Sélection un item si la touche est une barre espace
                if (selectionner[0].cordonneeX == -1)// si  aucune séléction a été faite
                {
                    selectionner[0] = (Selection){curseurX, curseurY}; // Première sélection de item
                }
                else {
                    selectionner[1] = (Selection){curseurX, curseurY}; // Deuxième sélection de item

                    char stockage = grid[selectionner[1].cordonneeY][selectionner[1].cordonneeX];
                    grid[selectionner[1].cordonneeY][selectionner[1].cordonneeX] = grid[selectionner[0].cordonneeY][selectionner[0].cordonneeX];
                    grid[selectionner[0].cordonneeY][selectionner[0].cordonneeX] = stockage;
                    //groupement des items
                    Groupement(grid, &points, pointItem);
                    GroupementRectangle(grid, &points, pointItem);
                    TomberItems(grid); // Faire tomber les items après la suppression

                    // Réinitialiser les sélections
                    selectionner[0] = (Selection){-1, -1};
                    selectionner[1] = (Selection){-1, -1};

                    // Vérifier la fin de niveau
                    int niveau = finNiveau(points, &vies);


                    if (niveau== -1) {
                        break; // Fin du jeu
                    }
                    if (niveau == 1) {
                        points = 0; // Réinitialiser les points pour le nouveau niveau
                        initializeGrid(grid); // Réinitialiser la grille pour le nouveau niveau
                    }
                }
            } else {
                Deplacement(deplacement, &curseurX, &curseurY);
            }

        }
        break;

        case 2:
        break;

        case 3:
        break;

        case 4://regle du jeu
            affichage_regle_du_jeu();

        break;

    }

        return 0;

}
