//
// Created by ayyub on 20/10/2024.
//
#include "Menu.h"
#include "windows.h"
#include "plateau.h"
#include <stdio.h>


int Menu() {
    int choix;
    printf("\n");
    titreMenu();
    printf("\t-----------------MENU-----------------\n");
    printf("\t1 - Nouvelle partie\n");
    printf("\t2 - Charger une partie\n");
    printf("\t3 - Regles du jeu\n");
    printf("\t4 - reinitialiser la sauvegarde\n");
    printf("\tSaisir votre choix ?\n");
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
                //niveau = charger(nom);
                return 2;
                case 51://règle du jeu 3 ascii
                    printf("Voici les regles du jeu \n");
                    affichage_regle_du_jeu();
                return 3;
                case 52://rest progression 4 ascii
                    printf("voulez vous vraiment reinitialiser votre progression?\n");

                return 4;

                default:
                    printf("Choix invalide. Veuillez entrer un nombre entre 1 et 3.\n");
                break;
            }
        }
    }
}
// Fonction pour afficher le menu et selectionner un choix


void affichage_regle_du_jeu() {
    system("cls");
    printf(" -----------------regle du jeu-----------------\n\n");
    printf(" Un groupe de 4 items (horizontal ou vertical) de meme nature rapporte 4 points .\n\n");
    printf(" un groupe de 6 items (horizontal ou vertical) de meme nature provoque la disparition de tous les items identiques presents sur le tableau,\n");
    printf(" meme s'ils sont isoles, et remporte autant de points que d'items disparus.\n\n");
    printf(" un groupe d'items de meme nature en forme de H rapporte 2*X points avec X le nombre d'items formant le H.\n\n");
    printf(" un groupe d'items de meme nature formant un rectangle rapport  2*(L x l) points avec L = longeur et l = largeur du rectangle. \n\n");
    printf("\n\n");
    printf(" Appuyez sur 'p' pour quitter.\n");

    while (1) {
        // Boucle infinie
        if (_kbhit()) { // Vérifie si une touche est pressée alternative scanf pour une touche saisie
            char c = _getch(); // Récupère la touche pressée
            if (c == 'p') {// si la touche p à été appuyez
                printf("\nSortie des regle du jeu.\n");
                break; // Quitte la boucle
            }
        }
    }
    system("cls");
}

void titreMenu(){
    color(10, 0);
    printf(

"__________ .__                     __                    .__\n"
"\\______   \\|  |  _____     ____  _/  |_ _____     _____  |__|________\n"
" |     ___/|  |  \\__  \\   /    \\ \\   __\\\\__  \\   /     \\ |  |\\___   / \n"
" |    |    |  |__ / __ \\_|   |  \\ |  |   / __ \\_|  Y Y  \\|  | /    /  \n"
" |____|    |____/(____  /|___|  / |__|  (____  /|__|_|  /|__|/_____ \\ \n"
"                      \\/      \\/             \\/       \\/           \\/ \n\n");
    color(15, 0);


}






