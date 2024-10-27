//
// Created by nicol on 10/20/2024.
//
#include <stdio.h>
#include "plateau.h"
#include <stdlib.h>
#include <time.h>
#include "Contrat_plateau.h"
#include "pion.h"
#include <windows.h> // Pour la gestion des couleurs

/***
struct plateau { // revoir l'utilité de cettet element
    unsigned int longueur; //longeur plateau
    unsigned int hauteur ; //hauteur plateau
    char *nom; // nom du plateau
    int objectif_soleil; // quantité de soleil demandé pour le contract
    int objectif_fraise; // quantité de fraise demandé pour le contract
    int objectif_pomme; // quantité de pomme demandé pour le contract
    int objectif_oignon; // quantité de oignon demandé pour le contract
    int objectif_mandarine; // quantité de mandarine demandé pour le contract
};


void init_plateau(int tableau[ligne][colonne]) {
    int i, j;
    for (i = 0; i < ligne; i++) {
        for (j = 0; j < colonne; j++) {
            tableau[i][j] = 0;
        }
    }

}

void display_plateau(int tableau[ligne][colonne]) {
    int i,j;
    printf("                                        PLANTAMIZ \n");
    for(i=0; i<ligne;i++){
        for(j=0; j<colonne; j++){
            printf("%2d",tableau[i][j]);
        }
        printf("\n");
    }

}
***/

// Liste des items
char items[] = {'S', 'F', 'P', 'O', 'M'};
int niveau=0;
ContratPlateau contrats[] = {
    {{20, 0, 0, 50, 20}, 30}, // Contrat pour le plateau niveau 1
    {{55, 30, 35, 45, 0}, 40}, // Contrat pour le plateau niveau 2
    {{70, 0, 60, 0, 50}, 50} }; // Contrat pour le plateau niveau 3

void gotolicol(int x, int y)//permetttant de positionner le curseur dans la console
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void AffichageCurseur(int curseurX, int curseurY) {
    gotolicol(curseurX * 2, curseurY + 1); // Ajuste pour l'espacement
    printf("^"); // Ou un autre symbole pour le curseur
}

// Fonction pour changer la couleur dans la console
void color(int couleurDuTexte, int couleurDeFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

// Fonction pour générer un item aléatoire
char generateRandomItem() {
    return items[rand() % 5];
}

// Vérifie si un groupe de 3 est formé horizontalement ou verticalement
int checkGroup(char grid[ROWS][COLS], int row, int col, char item) {
    // Vérification horizontale (gauche)
    if (col >= 2 && grid[row][col-1] == item && grid[row][col-2] == item) {
        return 1;
    }
    // Vérification verticale (au-dessus)
    if (row >= 2 && grid[row-1][col] == item && grid[row-2][col] == item) {
        return 1;
    }
    return 0;
}


// Fonction d'initialisation de la grille sans groupes de 3 ou plus
void initializeGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char item;
            do {
                item = generateRandomItem();
            } while (checkGroup(grid, i, j, item));  // Regénérer l'item s'il forme un groupe
            grid[i][j] = item;
        }
    }
}

// Fonction pour afficher la grille avec couleurs
void displayGrid(char grid[ROWS][COLS]) {
    system("cls");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Attribution des couleurs en fonction des items
            switch(grid[i][j]) {
                case 'S': color(14, 0); break; // Jaune pour Soleil
                case 'F': color(4, 0); break;  // Rouge pour Fraise
                case 'P': color(10, 0); break; // Vert pour Pomme
                case 'O': color(6, 0); break;  // Orange pour Oignon
                case 'M': color(5, 0); break;  // Violet pour Mandarine
            }
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    color(15, 0); // Remettre le texte en blanc
}

void Instruction() {
    gotolicol(0, ROWS + 4); // Positionne l'affichage un peu plus bas
    printf("Entrez votre deplacement: fleche haut a ou z | fleche bas ou s | fleche gauche ou q | fleche droit ou d et validez avec la barre d'espace : ");

}
void Score(int points, int pointsItem[nombreTotalPion], int vie) {
         gotolicol(0, ROWS + 1);
          int S=pointsItem[soleil];// point pour item soleil
          int F=pointsItem[fraise];// point pour item fraise
          int P=pointsItem[pomme];// point pour item pomme
          int O=pointsItem[oignons];// point pour item oignon
          int M=pointsItem[mandarine]; // point pour item mandarine
    printf("Points Totals: %d\n", points);
    printf("Soleil: %d\n Fraise: %d\n Pomme: %d\n Oignon: %d\n Mandarine:%d\n",S, F, P, O, M);
    printf("Vies restantes: %d\n", vie);
}

void Deplacement(char deplacement, int *curseurX, int *curseurY) {// déplacement un item
    switch(deplacement) {

    case 'z':
    case 72: // CODE ANSI (fleche haut)
        if (*curseurY > 0)
            (*curseurY)--; // deplacement vers le haut
        break;

    case 's':
    case 80: // CODE ANSI (fleche bas)
        if (*curseurY < ROWS - 1)
            (*curseurY)++; // deplacement vers le bas
        break;

    case 'd':
    case 77: // CODE ANSI (fleche droite)
         if (*curseurX < COLS - 1)
            (*curseurX)++; // deplacement vers la droite
         break;


    case 'q':
    case 75: // CODE ANSI (fleche gauche)
         if (*curseurX > 0)
         (*curseurX)--; // deplacement vers la gauche
     break;
    }
}

void Groupement (char grid[ROWS][COLS], int *points, int pointsItem[nombreTotalPion]) {
    int ItemCompter[ROWS][COLS] = {0}; // éviter de recompter les points ( items déjà compté)

    // Vérification des groupement items à horizontal
    for (int ligne = 0; ligne < ROWS; ligne++) {
    for (int colonne = 0; colonne < COLS - 2; colonne++) {// compter jusqu'a deux colonnes avant la fin ( nécesitant mininum ça pour faire  un groupement de 3)
        if (grid[ligne][colonne] == grid[ligne][colonne + 1] && grid[ligne][colonne] == grid[ligne][colonne + 2]) {//vérifie si les 3 items proche sont identiques
            int compteurPoint = 3;// compter trois points
            while (colonne + compteurPoint < COLS && grid[ligne][colonne] == grid[ligne][colonne + compteurPoint]) {
                compteurPoint++; // continuer de compter tant que les items proche sont identiques
                }
            if (compteurPoint >= 4) {
                *points ++= compteurPoint; // 1 point par item
                 pointsItem[grid[ligne][colonne] - 'S'] += compteurPoint; // Mise à jour des points par item
                for (int k = 0; k < compteurPoint; k++) {
                    ItemCompter[ligne][colonne + k] = 1;
                    }
                }
                colonne += compteurPoint - 1; // Sauter les items déjà comptés
            }
        }
    }

    // Vérification des groupement items à la vertical
    for (int colonne = 0; colonne < COLS; colonne++) {
        for (int ligne = 0; ligne < ROWS - 2; ligne++) {// compter jusqu'a deux lignes avant la fin ( nécesitant mininum ça pour faire les groupements de 3)
            if (grid[ligne][colonne] == grid[ligne + 1][colonne] && grid[ligne][colonne] == grid[ligne + 2][colonne]) {//vérifie si les 3 items sont identiques
                int compteurPoint=3;
                while (ligne + compteurPoint < ROWS && grid[ligne][colonne] == grid[ligne + compteurPoint][colonne]) {
                    compteurPoint++;
                    }
                if (compteurPoint > 3) {
                    *points += compteurPoint; // on compte 1 point par item
                    pointsItem[grid[ligne][colonne] - 'S'] += compteurPoint; // Mise à jour des points par item
                    for (int k = 0; k < compteurPoint; k++) {
                        ItemCompter[ligne + k][colonne] = 1;
                    }
                }
                ligne += compteurPoint - 1; // Sauter les items déjà comptés
            }
        }
    }

    // Suppression des items comptés
    for (int ligne = 0; ligne < ROWS; ligne++) {
        for (int colonne = 0; colonne < COLS; colonne++) {
            if (ItemCompter[ligne][colonne]) {
                grid[ligne][colonne] = ' '; // Suppression ou remplacer par des items aléatoire par dessus
            }
        }
    }
}

void TomberItems(char grid[ROWS][COLS]) {// fonction permettant de remplir  les espaces vides du aux items regroupé par d'autres items aléatoire
    for (int colonne = 0; colonne < COLS; colonne++) {
    for (int ligne = ROWS - 1; ligne >= 0; ligne--) {// parcours en commençant par la derniere ligne du plataux et monte vers le haut ( vers la première ligne)
        if (grid[ligne][colonne] == ' ') {// si espace vide
        for (int k = ligne - 1; k >= 0; k--) {// parcours LE DESSUS de l'espace vide pour trouver un items présent
            if (grid[k][colonne] != ' ') {// si il n'y a pas espace vide
                grid[ligne][colonne] = grid[k][colonne];
                grid[k][colonne] = ' ';// déplacer cet item present dans espace vide
        break;// seul le PREMIER item détécté est déplacé
            }
        }
    }
}
}
    //parcourir les lignes et colonnes du plateaux
    for (int colonne = 0; colonne < COLS; colonne++) {
    for (int ligne = 0; ligne < ROWS; ligne++) {
        if (grid[ligne][colonne] == ' ') {// si il ya un espace vide
            grid[ligne][colonne] = generateRandomItem();// remplir ces espaces vides par des items aléatoire
            }
        }
    }
}

// Fonction pour vérifier et marquer les rectangles
void GroupementRectangle(char grid[ROWS][COLS], int *points, int pointsItem[nombreTotalPion]) {
    int largeur = 0;
    int hauteur = 0;
    int ItemCompter[ROWS][COLS] = {0}; // éviter de recompter les points ( items déjà compté)

    for (int ligne = 0; ligne < ROWS; ligne++) {
    for (int colonne = 0; colonne < COLS; colonne++) {
        if (grid[ligne][colonne] != ' ' && !ItemCompter[ligne][colonne]) {// vérifie si la case n'est pas vide et pas compté
            char item = grid[ligne][colonne];

            // but : trouver la largeur du rectangle
        while (colonne + largeur < COLS && grid[ligne][colonne + largeur] == item) {// compter les items identique dans les lignes
            largeur++;// prendre ça dans la largeur
            }

                // but : trouver la hauteur du rectangle
        while (ligne + hauteur < ROWS && grid[ligne + hauteur][colonne] == item) {//pour chaque ligne des items , on vérifie si la colonne est identique à sa largeur (meme nature)
            int k;
        for (k = 0; k < largeur; k++) {
         if (grid[ligne + hauteur][colonne + k] != item) {// on sort de la boucle si la largeur des items ne correspond à ces colonnes ( hauteur)
            break;
                    }
                }
        if (k == largeur) // si la largeur items est également la meme avec sa hauteur ( meme nature colonne et ligne)
            hauteur++;// augmenter la hauteur pour prendre le plus possible
            else
                break;
            }

                // étape: avoir le rectangle
                if (largeur >= 2 && hauteur >= 2) {
            int compteurPoint = largeur * hauteur; // Nombre d'items dans le rectangle ( LARGEUR X HAUTEUR)
            *points += compteurPoint; // Ajouter les points
            pointsItem[item - 'S'] += compteurPoint; // Mise à jour des points par item


            for (int h = 0; h < hauteur; h++) {// comptabiliser les items comptés
                for (int l = 0; l < largeur; l++) {
                    ItemCompter[ligne + h][colonne + l] = 1;
                }
            }
        }


                colonne += largeur - 1; // Sauter les items déjà comptés
            }
        }
    }

    // Suppression des items comptés
    for (int ligne = 0; ligne < ROWS; ligne++) {
        for (int colonne = 0; colonne < COLS; colonne++) {
            if (ItemCompter[ligne][colonne]) {
                grid[ligne][colonne] = ' '; // Suppression du groupement items
            }
        }
    }
}
int Contrats(int pointsItem[nombreTotalPion], int coups) {

    for (int i = 0; i < nombreTotalPion; i++) {// Vérifie si les objectifs du contrat  sont atteints
        if (pointsItem[i] < contrats[niveau].objectifsContrat[i]) {
            return 0; // Contrat non atteint
        }
    }
    return coups <= contrats[niveau].coupsMax; // Vérifie si le nombre de coups est respecté
}
/*int finNiveau(int points, int *vie) {
    if (points >= POINTS_NIVEAU_REQUIS) {
        printf("BRAVO CHAMPION , Niveau suivant atteint\n");

        // AYYUB ICI TU FAIS LA SAUVEGARDE

        return 1;
    } else {
        printf("Vous avez pas atteint le score. vous avez eprdu une vie \n");
        (*vie)-1; // Une vie perdu

        if (*vie == 0) {
            printf("Vous avez perdu toutes vos vies. Fin du jeu.\n");
            return -1 ; // Fin du jeu
        }
        return 0; // échoué
    }
}*/