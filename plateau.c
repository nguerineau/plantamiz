//
// Created by nicol on 10/20/2024.
//
#include <stdio.h>
#include "plateau.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Pour la gestion des couleurs



// Liste des items
char items[] = {'S', 'F', 'P', 'O', 'M'};
int niveau=0;
ContratPlateau contrats[] = {
    {{20, 0, 0, 50, 20}, 30}, // Contrat pour le plateau niveau 1
    {{55, 30, 35, 45, 0}, 40}, // Contrat pour le plateau niveau 2
    {{70, 0, 60, 0, 50}, 50} }; // Contrat pour le plateau niveau 3

int nombreContrat=sizeof(contrats)/sizeof(ContratPlateau);

void gotolicol(int x, int y)//permetttant de positionner le curseur dans la console
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void AffichageCurseur(int curseurX, int curseurY) {
    gotolicol(curseurX * 2, curseurY + 1); // Ajuste pour l'espacement
    printf("-"); //  symbole pour le curseur
}

// Fonction pour changer la couleur dans la console
void color(int couleurDuTexte, int couleurDeFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

// Fonction pour générer un item aléatoire
char generateRandomItem() {
    return items[rand() % nombreTotalPion];
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
// Initialisation de la grille sans voisins identiques
void initializeGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char item;


            // Essayer de g�n�rer un item qui respecte les contraintes
            do {
                item = generateRandomItem();
            } while (Aucun_Item_identique(grid,i, j, item));

            grid[i][j] = item;
        }
    }
}

int Aucun_Item_identique(char grid[ROWS][COLS],int ligne, int colonne, char item) {
    if (ligne > 0 && grid[ligne - 1][colonne] == item) return 1; // Haut
    if (colonne > 0 && grid[ligne][colonne - 1] == item) return 1; // Gauche
    return 0; // Aucun voisin identique
}

// Fonction pour afficher la grille avec couleurs
void displayGrid(char grid[ROWS][COLS]) {
   system("cls");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Attribution des couleurs en fonction des items
            switch (grid[i][j]) {
                case 'S': color(14, 0); break; // Jaune pour Soleil
                case 'F': color(4, 0); break;  // Rouge pour Fraise
                case 'P': color(10, 0); break; // Vert pour Pomme
                case 'O': color(6, 0); break;  // Orange pour Oignon
                case 'M': color(5, 0); break;  // Violet pour Mandarine
                default: color(15, 0); break;  // Blanc pour autres items
            }
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    color(15, 0); // Remettre le texte en blanc
}


void Score(int points, int pointsItem[nombreTotalPion], int vie, int coups) {
    gotolicol(0, ROWS + 1);
    printf("Points Totals: %d\n", points);
    printf("Soleil: %d | Fraise: %d | Pomme: %d | Oignons: %d | Mandarine: %d\n",
           pointsItem[soleil], pointsItem[fraise], pointsItem[pomme], pointsItem[oignons], pointsItem[mandarine]);
    printf("Vies restantes: %d | Coups restants: %d\n", vie, OBJECTIF_CONTRAT_ATTEINT - coups);
}

void Deplacement(char deplacement, int *curseurX, int *curseurY) {// d�placement un item
    switch(deplacement) {

        case 'z':
        case flecheHaut: // CODE ANSI (fleche haut)
            if (*curseurY > 0)
                (*curseurY)--; // deplacement vers le haut
        break;

        case 's':
        case flecheBas: // CODE ANSI (fleche bas)
            if (*curseurY < ROWS - 1)
                (*curseurY)++; // deplacement vers le bas
        break;

        case 'd':
        case flecheDroite: // CODE ANSI (fleche droite)
             if (*curseurX < COLS - 1)
                 (*curseurX)++; // deplacement vers la droite
        break;


        case 'q':
        case flecheGauche: // CODE ANSI (fleche gauche)
             if (*curseurX > 0)
                 (*curseurX)--; // deplacement vers la gauche
        break;
    }
}

void GroupementVerticalHorizontal(char grid[ROWS][COLS], int *points, int pointsItem[nombreTotalPion]) {
    // initilse une matrice ( tableau à deux dimension) pour marquer les éléments déjà compter dans un groupement
    int ItemCompter[ROWS][COLS] = {0};  // vhaque case sera 1 si l'élément est compter, 0 si c pas le cas

    // vérifie des groupements horizontal
    for (int i = 0; i < ROWS; i++) {  // parcours chaque ligne de la grille
        for (int j = 0; j < COLS - 2; j++) {  // parcours chaque colonne, mais jusqu'à COLS - 2 pour éviter de dépasser la grille
            if (grid[i][j] == grid[i][j+1] && grid[i][j] == grid[i][j+2]) {// Vérifier si 3 éléments consécutifs sont identiques horizontalement
                int compteur = 3;  // compter d'abord les 3 éléments consécutifs
                // continuer à compté tant qu'on trouve des éléments identiques à droite
                while (j + compteur < COLS && grid[i][j] == grid[i][j+compteur]) {
                    compteur++;  // incrémente le compteur si l'élément suivant est identique
                }
                // ajouter des points pour ce groupement
                *points += compteur;  // On ajoute au total des points le nombre d'éléments du groupement
                // ajouter des points à l'élément spécifique dans le tableau pointsItem
                pointsItem[grid[i][j] - 'S'] += compteur;  // Le '- 'S' permet de convertir le caractère en indice du tableau
                // marquer des cases de ce groupement pour ne pas les compter à nouveau
                for (int k = 0; k < compteur; k++) {
                    ItemCompter[i][j+k] = 1;  // marque les cases comptabilisées dans la ligne
                }
                // saute les cases déjà compter dans le prochain tour de boucle
                j += compteur - 1;
            }
        }
    }

    // vérifier des groupements vertical
    for (int j = 0; j < COLS; j++) {  // parcours chaque colonne
        for (int i = 0; i < ROWS - 2; i++) {  // parcours chaque ligne, mais jusqu'à ROWS - 2 pour éviter de dépasser la grille
            if (grid[i][j] == grid[i+1][j] && grid[i][j] == grid[i+2][j]) {// vérifie si 3 éléments consécutifs sont identiques verticalement
                int compteur = 3;  // commencer par compter les 3 éléments consécutifs
                //continuer à compter tant qu'on trouve des éléments identiques en bas de celui-ci
                while (i + compteur < ROWS && grid[i][j] == grid[i+compteur][j]) {
                    compteur++;  // Incrémentation du compteur si l'élément suivant est identique
                }
                // ajouter des points pour ce groupement
                *points += compteur;  // Ajoute au total des points le nombre d'éléments du groupement
                // ajouter des points à l'élément spécifique dans le tableau pointsItem
                pointsItem[grid[i][j] - 'S'] += compteur;  // Le '- 'S' permet de convertir le caractère en indice du tableau
                // Marque les cases de ce groupement pour ne pas les compter à nouveau
                for (int k = 0; k < compteur; k++) {
                    ItemCompter[i+k][j] = 1;  // marque les cases compté dans la colonne
                }
                // sauter les cases déjà compté dans le prochain tour de boucle
                i += compteur - 1;
            }
        }
    }

    // après avoir détecté et compté les groupements, on vide les cases déjà compté
    // empêche les groupements précédents d'être compter encore
    for (int i = 0; i < ROWS; i++) {  // Parcours chaque ligne
        for (int j = 0; j < COLS; j++) {  // Parcours chaque colonne
            // Si l'élément de la case a été comptabilisé (marqué dans ItemCompter), on le remplace par un espace
            if (ItemCompter[i][j]) {
                grid[i][j] = ' ';  // Remplace l'élément comptabilisé par un espace
            }
        }
    }
}

void TomberItems(char grid[ROWS][COLS]) {
    // Faire tomber les items pour combler les vides
    for (int colonne = 0; colonne < COLS; colonne++) {
        for (int ligne = ROWS - 1; ligne >= 0; ligne--) {
            if (grid[ligne][colonne] == ' ') { // si espace vide
                for (int k = ligne - 1; k >= 0; k--) { // trouver un item au-dessus
                    if (grid[k][colonne] != ' ') { // item trouvé
                        grid[ligne][colonne] = grid[k][colonne];
                        grid[k][colonne] = ' '; // déplacer cet item
                        break;
                    }
                }
            }
        }
    }

    // Remplir les espaces vides par des items aléatoires
    for (int colonne = 0; colonne < COLS; colonne++) {
        for (int ligne = 0; ligne < ROWS; ligne++) {
            if (grid[ligne][colonne] == ' ') { // si espace vide
                grid[ligne][colonne] = generateRandomItem(); // remplir par un item aléatoire
            }
        }
    }
}
// Fonction pour faire des groupement de rectangle
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

    // Supprimer des items comptés
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
            return 0; // pas atteint
        }
    }
    return coups <= contrats[niveau].coupsMax; // Vérifie si le nombre de coups est respecté
}
void GroupementH(char grid[ROWS][COLS], int *points, int pointsItem[nombreTotalPion]) {

    int ItemCompter[ROWS][COLS] = {0}; // tableau pour suivre les cases déjà compter

    // parcourir de toutes les cases de la grille pour rechercher des H
    for (int i = 1; i < ROWS - 1; i++) {  // on commence à la ligne 1 et on s'arrête à la ligne ROWS-2
        for (int j = 1; j < COLS - 1; j++) {  // on commence à la colonne 1 et on s'arrête à la colonne COLS-2
            // Vérification si l'élément en position i et ausssi j peut être le centre d'un H
            if (grid[i][j] == grid[i-1][j] && grid[i][j] == grid[i+1][j] &&  // Vérifie les éléments vertical du H déssiné
                grid[i][j] == grid[i][j-1] && grid[i][j] == grid[i][j+1]) {  // Vérifie les éléments horizontal du H déssiné
                // Si un "H" est trouvé, on calcule le nombre d'items qui forment le "H"
                int compteur = 5;  // Un H est constitué de 5 cases
                *points += 2 * compteur;  // chaque H rapporte 2 * X points, avec X = 5 QUI est le nombre mininum necessaire pour former un H
                pointsItem[grid[i][j] - 'S'] += 2 * compteur;  // On ajoute les points au type d'item concerné
                // On marque les cases du "H" comme comptabilisées
                ItemCompter[i][j] = 1;  //  centre du "H"
                ItemCompter[i-1][j] = 1;  //  haut du "H"
                ItemCompter[i+1][j] = 1;  //  bas du "H"
                ItemCompter[i][j-1] = 1;  // le côté gauche du "H"
                ItemCompter[i][j+1] = 1;  //  côté droit du "H"
                }
        }
    }

    // après avoir comptabilisé les points pour tous les H, on efface les items déjà compter
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (ItemCompter[i][j]) {
                grid[i][j] = ' ';  // Remplace les items comptabilisés par un espace (c'est à dire qu'ils sont supprimé)
            }
        }
    }
}
void ObjectifsItem (int objectifs[nombreTotalPion], int pointsItem[nombreTotalPion]) {
    gotolicol(0, ROWS + 4);//évite que ça empiete sur les phrase au-dessus ou encore la grille
    printf("Objectifs  :\n");
    printf("Soleil: %d | Fraise: %d | Pomme: %d | Oignons: %d | Mandarine: %d\n",objectifs[soleil] - pointsItem[soleil],objectifs[fraise] - pointsItem[fraise],objectifs[pomme] - pointsItem[pomme],objectifs[oignons] - pointsItem[oignons],objectifs[mandarine] - pointsItem[mandarine]);
    // objectif final = objective d'un d'item spécifique - point gagné cet item gagné durant la partie
}
