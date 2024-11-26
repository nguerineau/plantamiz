#include <stdio.h>
#include "plateau.h"
#include "Contrat_plateau.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Menu.h"
#include <conio.h>

int main(void)
{    char nom[];
    printf("\n Saisir votre nom : \n");
    scanf("%s",&nom);
    int points = 0;
    int pointsItem[nombreTotalPion] = {0};
    int vies = 5, coups = 0;

    Menu();
    printf("\n Saisir votre nom : \n");
    scanf("%s",&nom);
    sauvegarde();

    char grid[ROWS][COLS];
    int curseurX = 0, curseurY = 0;

    srand(time(NULL));
    initializeGrid(grid);

    while (1) {
        displayGrid(grid);
        AffichageCurseur(curseurX, curseurY);
        Score(points, pointsItem, vies);
        printf("Entrez votre deplacement (z/q/s/d ou espace pour valider) : ");
        char deplacement = _getch();

      Deplacement(deplacement, &curseurX, &curseurY);
    if (deplacement == ' ') { // Valider échange avec espace


    // Vérifier la validité de l'échange (dans les limites de la grille)
    if (curseurX + 1 < COLS) {
        // Échanger les items
       char echange = grid[curseurY][curseurX];
        grid[curseurY][curseurX] = grid[curseurY][curseurX + 1];
        grid[curseurY][curseurX + 1] = echange;

        // Vérifier si un groupement est formé après l'échange
        int pointsAvant = points;
        Groupement(grid, &points, pointsItem);
        GroupementRectangle(grid, &points, pointsItem);

        // Si aucun point n'est marqué, annuler l'échange
        if (points == pointsAvant) {
            // Ré-inverser l'échange
            echange = grid[curseurY][curseurX];
            grid[curseurY][curseurX] = grid[curseurY][curseurX + 1];
            grid[curseurY][curseurX + 1] = echange;
        } else {
            // Si des points sont marqués, faire tomber les items et remplir les espaces
            TomberItems(grid);

            // Vérifier les objectifs du contrat pour le niveau
            if (Contrats(pointsItem, coups)) {
                printf(" vous avez rempli le contrat pour ce niveau.\n");
                niveau++;
                points = 0; // Réinitialiser les points pour le prochain niveau
                initializeGrid(grid);

                if (niveau >= nombreContrat) {
                    printf("Vous avez terminé tous les niveau \n");
                    break;
                }
            }
        }
    } else {
        printf("Échange non valide, essayez une direction différente.\n");
    }
}
    }

    return 0;
}

     /**
     int plateau[ligne][colonne];
    init_plateau(plateau);
    display_plateau(plateau);
    while(1);
    **/
    /*int points = 0; // stocker le point total
    int pointItem[nombreTotalPion] = {0}; // Pour stocker les points pour chaque item
    int curseurX = 0, curseurY = 0,vies = 5, coups=0;

    startmenu:

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
        goto startmenu;
    }
    return 0;
}*/
