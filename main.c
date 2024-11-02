#include <stdio.h>
#include "plateau.h"
#include "Contrat_plateau.h"
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
    int pointItem[nombreTotalPion] = {0}; // Pour stocker les points pour chaque item
    int curseurX = 0, curseurY = 0,vies = 5, coups=0;

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
        printf("Entrez votre deplacement: fleche haut ou z | fleche bas ou s | fleche gauche ou q | fleche droit ou d et validez avec la barre d'espace : ");


        char deplacement = _getch(); // Lire le déplacement de l'utilisateur

        Deplacement(deplacement, &curseurX, &curseurY);
        coups++;
       // gotolicol(0, ROWS + 7);// s'assurer de mettre affichage en dessous ce la grille
        printf("Coups restants: %d\n", OBJECTIF_CONTRAT_ATTEINT - coups); // Affiche le nombre de coups restants

        if (coups >= OBJECTIF_CONTRAT_ATTEINT) {
            printf("Vous avez atteint le nombre maximum de coups. Fin du jeu.\n");
            break; // Fin du jeu
        }


      if (deplacement == ' ') {// valider item avec espace
    if (curseurX < COLS - 1) { // S'assurer que l'échange est possible vers la droite
        // Échanger deux items
        char echange = grid[curseurY][curseurX];
        grid[curseurY][curseurX] = grid[curseurY][curseurX + 1];
        grid[curseurY][curseurX + 1]= echange;

        Groupement(grid, &points, pointItem);
        GroupementRectangle(grid, &points, pointItem);
        Score(points, pointItem, vies);
        TomberItems(grid);

        if (Contrats(pointItem, coups)) {
            printf("BRAVO CHAMPION, vous avez rempli le contrat pour ce niveau.\n");
            niveau++;
            points = 0; // Réinitialisation des points
            initializeGrid(grid);
            if (niveau >= nombreContrat) {
                printf("Vous avez terminé tous les niveaux !\n");
                break;
            }
        } else if (coups >= OBJECTIF_CONTRAT_ATTEINT) {
            printf("Désolé, vous n'avez pas rempli le contrat. Jeu finis.\n");
            break;
        }
    }
}
    if (coups >= OBJECTIF_CONTRAT_ATTEINT && !Contrats(pointItem, coups)) {
    vies--;
    printf("Vous avez perdu une vie, Vies restantes : %d\n", vies);
    if (vies <= 0) {
        printf("Vous avez perdu toutes vos vies. Fin du jeu.\n");
        break;
    }
}
    }
    return 0;
}
