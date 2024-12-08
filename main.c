#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <windows.h> // Pour la gestion des couleurs
#include "Menu.h"
#include "plateau.h"
#include "sauvegarde.h"
#include <unistd.h>
// tu mets dans la fonction main


int main(void) {

    int points = 0, vies = 5, coups = 0, total = 0, ptotal=0,opt_menu=0,game=0;
    int pointsItem[nombreTotalPion] = {0};

    while(TRUE) {
        switch(game) {
            case 0:
                opt_menu = Menu();
            switch (opt_menu) {
                case 1://nouvelle partie
                    niveau=0;
                    game=1;
                    sleep(5);
                break;
                case 2://charger
                    niveau=searchRequest();
                    game=1;
                    sleep(5);
                break;
                case 3://rules
                    game=0;
                break;
                case 4://reset
                    sauvegarde(0,0);
                    printf("votre progression est reinitialiser");
                    sleep(5);
                    game=0;
                break;
                case 5:
                    afficheScores();
                    game=0;
                break;
            }

            break;
            case 1:

                // La grille
                    char grid[ROWS][COLS];
            srand(time(NULL));
            initializeGrid(grid);

            int curseurX = 0, curseurY = 0;
            int selectionX = -1, selectionY = -1;

            while (vies > 0) {
                system("cls");  // Nettoie la console pour chaque mise à jour
                displayGrid(grid,curseurX, curseurY);
                printf("##############################  Niveau actuel : %d  #####################################\n", niveau + 1);
                total = Score(points, pointsItem, vies, coups, contrats[niveau].objectifsContrat);

                // Instructions pour les déplacements
                printf("Entrez votre deplacement ===> z-q-s-d ou les fleches directionnelles pour bouger sur le plateau\n"
                    "pour permuter des item, mettez le curseur sur l'item puis appuyez sur espce pour le selectionner.\n"
                    "deplacer vous sur un des pions adjacent puis appuyer sur espace pour permutter les pions\n\n"
                    "appuyer sur la touche p pour quittez la partie et revenir au menu.\n"
                    "attention votre progression durant le niveau ne sera pas sauvegarder");

                char deplacement = _getch();  // Lire la touche pressée
                if(deplacement =='p') {
                    system("cls");
                    game=0;
                    break;
                }
                Deplacement(deplacement, &curseurX, &curseurY);  // Déplacer le curseur en fonction de la touche pressée

                if (deplacement == ' ') {  // Si la barre d'espace est pressée, effectuer une permutation
                    if (selectionX == -1 && selectionY == -1) {
                        // Sélectionner un élément
                        selectionX = curseurX;
                        selectionY = curseurY;
                        grid[selectionY][selectionX] = grid[selectionY][selectionX];  // Met en minuscule pour indiquer la sélection
                    } else if (selectionX == curseurX && selectionY == curseurY) {
                        // Désélectionner l'élément
                        grid[selectionY][selectionX] = grid[selectionY][selectionX];  // Remet en majuscule
                        selectionX = selectionY = -1;  // Annuler la sélection
                    } else {
                        // Permuter les éléments et vérifier les groupements
                        permuterItems(&curseurX, &curseurY, &selectionX, &selectionY, grid, &points, pointsItem);
                        coups++;  // Incrémenter les coups après permutation

                        // Vérifier les groupements après la permutation

                        GroupementRectangle(grid, &points, pointsItem);
                        GroupementVerticalHorizontal(grid, &points, pointsItem);
                        GroupementH(grid, &points, pointsItem);

                        // Appliquer la gravité (les éléments tombent)
                        TomberItems(grid);
                    }
                }

                // Vérifier les objectifs du contrat pour le niveau
                if (Contrats(pointsItem, coups)) {
                    printf("Vous avez rempli le contrat pour le niveau %d.\n", niveau + 1);

                    // Demander si le joueur souhaite continuer après avoir terminé le niveau
                    printf("Souhaitez-vous passez au niveau suivant ? (o pour OUI, n pour NON) : ");
                    char choix;
                    choix = _getch();
                    if (choix == 'o' || choix == 'O') {
                        niveau++;  // Passer au niveau suivant
                        sauvegarde(niveau,total+ptotal);
                        ptotal = total;
                        initializeGrid(grid);  // Réinitialiser la grille
                        total = 0 ; // Réinitialiser les points pour le score
                        points = 0;  // Réinitialiser les points
                        coups = 0;  // Réinitialiser les coups
                        vies = 5;  // Réinitialiser les vies
                        for (int i = 0; i < nombreTotalPion; i++) {
                            pointsItem[i] = 0;  // Réinitialiser les points des items
                        }

                        if (niveau >=nombreContrat ) {
                            printf("Vous avez termine tous les niveaux, BRAVO !\n");
                            game=0;
                            break;  // Fin du jeu
                        }
                    }
                    else {
                        printf("Fin du jeu. A une prochaine fois !\n");
                        game=0;
                        break;  // Fin du jeu
                    }
                }

                // Si le nombre de coups dépasse la limite définie dans les contrats, retirer une vie
                if (coups >= contrats[niveau].coupsMax) {
                    printf("Le nombre de coups depasse la limite du contrat pour ce niveau.\n");

                    printf("Souhaitez-vous recommencer le niveau ? (o pour OUI, n pour NON) : ");
                    char choix;
                    choix = _getch();
                    if (choix == 'o' || choix == 'O') {
                        vies--;  // Retirer une vie
                        coups = 0;  // Réinitialiser les coups
                        printf("Vous avez perdu une vie. Vous recommencez ce niveau.\n");
                        initializeGrid(grid);  // Réinitialiser la grille
                        points = 0;  // Réinitialiser les points
                        for (int i = 0; i < nombreTotalPion; i++) {
                            pointsItem[i] = 0;  // Réinitialiser les points des items
                        }
                    } else {
                        printf("Fin du jeu. A une prochaine fois !\n");
                        sauvegarde(niveau,ptotal);
                        game=0;
                        break;  // Fin du jeu
                    }
                }
            }

            // Si le joueur perd toutes ses vies
            if (vies == 0) {
                sauvegarde(niveau,ptotal);
                printf("Vous avez perdu toutes vos vies. Reessayez ? (o pour OUI, n pour NON) : ");
                char choix;
                choix = _getch();
                if (choix == 'o' || choix == 'O') {
                    main();  // Relancer le jeu
                } else {
                    printf("Fin du game. A une prochaine fois !\n");
                    game=0;
                }
            }
            break;
        }
    }
}
