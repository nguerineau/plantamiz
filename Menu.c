//
// Created by ayyub on 20/10/2024.
//
#include "Menu.h"

int Menu() {
    int choix;
    printf("\t-----------------MENU-----------------\n");
    printf("\t1 - Nouvelle partie\n");
    printf("\t2 - Charger une partie\n");
    printf("\t3 - Regles du jeu\n\n");
    printf("Saisir votre choix ?\n");
    //scanf("%d", &choix);
    while (1) {
        // Boucle infinie
        if (_kbhit()) { // Vérifie si une touche est pressée
            char choix = _getch(); // Récupère la touche pressée
            switch (choix) {

                case 49://nouvelle partie 1 ascii
                    printf("Vous lancez une nouvelle partie !\n");
                return 1;

                case 50://charger partie 2 ascii
                    printf("Vous chargez une partie !\n");
                return 2;
                case 51://règle du jeu 3 ascii
                    printf("Voici les regles du jeu \n");
                return 3;
                default:
                    printf("Choix invalide. Veuillez entrer un nombre entre 1 et 3.\n");

                break;
            }
        }
    }
}
// Fonction pour afficher le menu et selectionner un choix


void affichage_regle_du_jeu() {
    printf("-----------------regle du jeu-----------------\n");
    printf(" les regles ... vas falloir les ajouter.\n");




    printf("\n\n");
    printf("Appuyez sur 'p' pour quitter.\n");

    while (1) {
        // Boucle infinie
        if (_kbhit()) { // Vérifie si une touche est pressée
            char c = _getch(); // Récupère la touche pressée
            if (c == 'p') {
                printf("\nSortie des regle du jeu.\n");
                break; // Quitte la boucle
            }
        }
    }
}




