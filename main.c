#include <stdio.h>
#include "plateau.h"
#include "Selection_cordonnées.h"
#include "Contrat_plateau.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Menu.h"
#include "pion.h"
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
    int pointItem[nombreTotalPion] = {0}; // Pour stocker les points pour chaque item
    int curseurX = 0, curseurY = 0,vies = 5, coups=0;
    int niveau=0;
    ContratPlateau contrats[] = {
        {{20, 0, 0, 50, 20}, 30}, // Contrat pour le plateau niveau 1
        {{55, 30, 35, 45, 0}, 40}, // Contrat pour le plateau niveau 2
        {{70, 0, 60, 0, 50}, 50} }; // Contrat pour le plateau niveau 3

    //Selection selectionner[2] = { { -1, -1 }, { -1, -1 } };
    Menu();
    char grid[ROWS][COLS];

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Initialisation et affichage de la grille
    initializeGrid(grid);
    while (1) {
        system("cls");
        displayGrid(grid);
        AffichageCurseur(curseurX, curseurY);
        Score(points, pointItem, vies);
        Instruction();

        char deplacement = _getch(); // Lire le déplacement de l'utilisateur

        Deplacement(deplacement, &curseurX, &curseurY);
        coups++;
        gotolicol(0, ROWS + 3);// s'assurer de mettre affichage en dessous ce la grille
        printf("Coups restants: %d\n", OBJECTIF_CONTRAT_ATTEINT - coups); // Affiche le nombre de coups restants

        if (coups >= OBJECTIF_CONTRAT_ATTEINT) {
            printf("Vous avez atteint le nombre maximum de coups. Fin du jeu.\n");
            break; // Fin du jeu
        }

        // Logique de validation de la sélection
        if (deplacement == ' \r') { //  valide item à déplacé avec la barre d'espace
            Groupement(grid, &points, pointItem);
            GroupementRectangle(grid, &points, pointItem);
            TomberItems(grid);
            if (Contrats(pointItem, coups)) {
                printf("BRAVO CHAMPION, vous avez rempli le contrat pour ce niveau.\n");
                niveau++; // Passe au niveau suivant
                points = 0; // Réinitialise les points
                initializeGrid(grid); // Réinitialise la grille
                if (niveau >= sizeof(contrats) / sizeof(ContratPlateau)) {
                    printf("Vous avez terminé tous les niveaux !\n");
                    break; // Fin du jeu
                }
            } else {
                printf(" Désolé , vous n'avez pas rempli le contrat. Fin du jeu.\n");
                break; // Fin du jeu
            }
        }

        if (vies <= 0) {
            printf(" NON , Vous avez perdu toutes vos vies. Fin du jeu.\n");
            break; // Fin du jeu
        }
    }
    return 0;
}