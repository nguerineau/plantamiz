//
// Created by ayyub on 20/10/2024.
//
#include "Menu.h"

void Menu() {
    int choix;
    printf("\t-----------------MENU-----------------\n");
    printf("\t1 - Nouvelle partie\n");
    printf("\t2 - Charger une partie\n");
    printf("\t3 - Mot de passe partie\n");
    printf("\t4 - Regles du jeu\n\n");
    printf("Saisir votre choix ?\n");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            printf("Vous lancez une nouvelle partie !\n");
        break;
        case 2:
            printf("Vous chargez une partie !\n");
        break;
        case 3:
            printf("Entrez le mot de passe de la partie \n");
        break;
        case 4:
            printf("Voici les regles du jeu \n");
        break;
        default:
            printf("Choix invalide. Veuillez entrer un nombre entre 1 et 4.\n");

        break;
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




