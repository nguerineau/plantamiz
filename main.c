#include <stdio.h>
#include "plateau.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Menu.h"
#include <conio.h>
#include "sauvegarde.h"

int main(void) {

    int points = 0;
    int pointsItem[nombreTotalPion] = {0};
    int vies = 5, coups = 0;


    while(TRUE) {
        int opt_menu = Menu();
            switch (opt_menu) {
                case 1://nouvelle partie
                    niveau=0;
                break;
                case 2://charger
                    niveau=searchRequest();
                break;
                case 4://reset
                    sauvegarde(0,0);
                break;
            }
           char grid[ROWS][COLS];
        int curseurX = 0, curseurY = 0;

        srand(time(NULL));
        initializeGrid(grid);


        while(vies>0) {
            system("cls");//nettoie la grille a chaque nouvelle positon du curseur
            displayGrid(grid);
            printf("Niveau actuel : %d\n", niveau + 1);
            AffichageCurseur(curseurX, curseurY);
            Score(points, pointsItem, vies, coups);
            ObjectifsItem(contrats[niveau].objectifsContrat, pointsItem);
            printf("Entrez votre deplacement ===> z-q-s-d ou les fleches directionnelles pour bouger sur le plateau\n"
                "pour permuter des item, mettez le curseur sur l'item puis appuyez sur espce pour le selectionner.\n"
                "deplacer vous sur un des pions adjacent puis appuyer sur espace pour permutter les pions\n\n"
                "appuyer sur la touche p pour quittez la partie et revenir au menue.\n"
                "attention votre progression durant le niveau ne sera pas sauvegarder");

            char deplacement = _getch();
            if(deplacement =='p') {
                break;
            }
            Deplacement(deplacement, &curseurX, &curseurY);
            if (deplacement == ' ') { // valider échange avec espace
                if (curseurX+1 < COLS) { // vérifie la validité de l'échange (dans les limites de la grille)
                    // Échanger les items
                    char echange = grid[curseurY][curseurX];
                    grid[curseurY][curseurX] = grid[curseurY][curseurX + 1];
                    grid[curseurY][curseurX + 1] = echange;

                    // vérifie si un groupement est formé après l'échange
                    int pointsAvant = points;
                    GroupementVerticalHorizontal(grid, &points, pointsItem);
                    GroupementRectangle(grid, &points, pointsItem);
                    GroupementH(grid, &points, pointsItem);
                    // si aucun point n'est marqué, annuler l'échange
                    if (points == pointsAvant) {
                        // ré-inverse l'échange
                        echange = grid[curseurY][curseurX];
                        grid[curseurY][curseurX] = grid[curseurY][curseurX + 1];
                        grid[curseurY][curseurX + 1] = echange;
                    } else {
                        // Si des points sont marqués, faire tomber les items et remplir les espaces
                        TomberItems(grid);
                        coups++;
                    }
                }
                // vérifie les objectifs du contrat pour le niveau
                if (Contrats(pointsItem, coups)) {
                    printf(" vous avez rempli le contrat pour le niveau %d.\n", niveau+1);
                    niveau++;// prochain niveau
                    sauvegarde(niveau,0);
                    initializeGrid(grid);// réinitialiser la grille
                    points = 0; // Réinitialiser les points pour le prochain niveau
                    coups = 0; // Réinitialise le nombre de coups
                    vies = 5;
                    if (niveau >= nombreContrat) {
                        printf("Vous avez terminé tous les niveau, BRAVO BRO \n");
                        break;
                    }

                }
            }
            if (coups >= contrats[niveau].coupsMax) {
                vies--;// je retire une vie
                coups = 0; // initialiaser les nombres de coup
                printf("Vous avez échoué ce niveau %d. Vous recommencez tout de suite\n", niveau);
            }

            if (vies == 0){
                printf("Vous etez nul. Réessayez ?\n");
                sauvegarde(niveau,0);

            }
        }
    }
}


