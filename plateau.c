//
// Created by nicol on 08/12/2024.
//

#include "plateau.h"
#include <stdio.h>
#include <windows.h>

// Liste des items
char items[] = {'S', 'F', 'P', 'O', 'M'};

int niveau=0;

ContratPlateau contrats[] = {
    {{0, 20, 0, 30, 10}, 30}, // Contrat pour le plateau niveau 1
    {{55, 30, 35, 45, 0}, 40}, // Contrat pour le plateau niveau 2
    {{70, 0, 60, 0, 50}, 50} }; // Contrat pour le plateau niveau 3



// Enumération des types d'items
enum ItemType {
    SOLEIL = 0,
    FRAISE = 1,
    POMME = 2,
    OIGNON = 3,
    MANDARINE = 4
};



int nombreContrat=sizeof(contrats)/sizeof(ContratPlateau);
// Déclaration de la fonction pour obtenir l'indice d'un élément
int getItemIndex(char item) {
    switch (item) {
        case 'S': return SOLEIL;
        case 'F': return FRAISE;
        case 'P': return POMME;
        case 'O': return OIGNON;
        case 'M': return MANDARINE;
        default: return -1;  // Si l'élément n'est pas reconnu
    }
}


// Fonction pour changer la couleur dans la console
void color(int couleurTexte, int couleurFond) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, couleurFond * 16 + couleurTexte);
}

// Fonction pour positionner le curseur dans la console
void gotolicol(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fonction pour générer un item aléatoire
char generateRandomItem() {
    return items[rand() % nombreTotalPion];
}

// Vérifier si un item est identique à ses voisins
int Aucun_Item_identique(char grid[ROWS][COLS],int ligne, int colonne, char item) {
    if (ligne > 0 && grid[ligne - 1][colonne] == item) return 1; // Haut
    if (colonne > 0 && grid[ligne][colonne - 1] == item) return 1; // Gauche
    return 0; // Aucun voisin identique
}

// Initialisation de la grille sans voisins identiques
void initializeGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char item;

            // Essayer de générer un item qui respecte les contraintes
            do {
                item = generateRandomItem();
            } while (Aucun_Item_identique(grid,i, j, item));


            grid[i][j] = item;
        }
    }
}

// Fonction pour afficher la grille avec les couleurs appropriées
void displayGrid(char grid[ROWS][COLS],int curseurX, int curseurY) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == curseurY && j == curseurX) {
                color(15, 9); // Texte blanc, fond bleu
            } else {
                switch (grid[i][j]) {
                    case 'S': color(14, 0); break; // Jaune pour Soleil
                    case 'F': color(4, 0); break;  // Rouge pour Fraise
                    case 'P': color(10, 0); break; // Vert pour Pomme
                    case 'O': color(6, 0); break;  // Orange pour Oignon
                    case 'M': color(5, 0); break;  // Violet pour Mandarine
                    default: color(15, 0); break;  // Blanc pour autres items
                }
            }

            // Affiche l'élément avec la couleur appropriée
            printf("%c ", grid[i][j]);
        }
        printf("\n"); // Nouvelle ligne après chaque rangée
    }

    color(15, 0); // Réinitialiser les couleurs
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



void TomberItems(char grid[ROWS][COLS]) {
    // Parcours de la grille de bas en haut pour simuler la gravité
    for (int j = 0; j < COLS; j++) {  // Parcours de chaque colonne
        for (int i = ROWS - 1; i >= 0; i--) {  // Commence de la dernière ligne
            if (grid[i][j] == ' ') {  // Si la case est vide
                // Cherche l'élément au-dessus
                for (int k = i - 1; k >= 0; k--) {
                    if (grid[k][j] != ' ') {  // Si un élément est trouvé
                        // Déplacer l'élément vers le bas
                        grid[i][j] = grid[k][j];
                        grid[k][j] = ' ';  // Vider la case d'origine
                        break;
                    }
                }
            }
        }
    }

    // Après avoir appliqué la gravité, il faut remplir les cases vides avec des éléments aléatoires
    for (int j = 0; j < COLS; j++) {
        if (grid[0][j] == ' ') {  // Si la case du haut est vide
            // Remplir cette case avec un élément aléatoire
            grid[0][j] = "SFOPM"[rand() % nombreTotalPion];  // Choisir un élément aléatoire parmi 'S', 'F', 'O', 'P', 'M'
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

void ObjectifsItem(const int objectifsContrat[nombreTotalPion], const int pointsItem[nombreTotalPion]) {
    printf("\nObjectifs pour ce niveau :\n");
    for (int i = 0; i < nombreTotalPion;i++) {
        if (pointsItem[i] < objectifsContrat[i]) {
            printf("  %c : %d/%d points (objectif non atteint)\n", "SFPOM"[i], pointsItem[i], objectifsContrat[i]);
        } else {
            printf("  %c : %d/%d points (objectif atteint)\n", "SFPOM"[i], pointsItem[i], objectifsContrat[i]);
        }
    }
    printf("\n");
}

int Score(int points, const int pointsItem[nombreTotalPion], int vies, int coups, const int objectifsContrat[nombreTotalPion]) {

    gotolicol(0, ROWS+2);// afficher en-dessous de la grille pour éviter qu'il empiéte sur le plateau
    int totalpoints=0;
    for (int i = 0; i < nombreTotalPion; i++) {
        totalpoints += pointsItem[i];  // ajouter les points de chaque item
    }

    printf("\n-------------------------- Score --------------------------\n");
    printf("Points totaux : %d\n", totalpoints);
    printf("Vies restantes : %d\n", vies);
    printf("Nombre de coups effectues : %d\n", coups);

    // Affichage des points par item
    printf("\nPoints par item :\n");
    for (int i = 0; i < nombreTotalPion; i++) {
        if (pointsItem[i] > 0) {
            printf("  %c : %d points\n", "SFPOM"[i], pointsItem[i]);
        }
    }

    // Affichage des objectifs du contrat pour le niveau actuel
    ObjectifsItem(objectifsContrat, pointsItem);

    printf("\n---------------------------------------------------------\n");
    return totalpoints;
}

void permuterItems(int *curseurX, int *curseurY, int *selectionX, int *selectionY,char grid[ROWS][COLS], int *points, int pointsItem[nombreTotalPion]) {
    char echange;


    if (abs(*selectionX - *curseurX) == 1 && *selectionY == *curseurY || abs(*selectionY - *curseurY) == 1 && *selectionX == *curseurX) {
        // Les deux éléments sont voisins, on peut permuter
        echange = grid[*curseurY][*curseurX];
        grid[*curseurY][*curseurX] = grid[*selectionY][*selectionX];
        grid[*selectionY][*selectionX] = echange;

        // Réinitialiser la sélection
        *selectionX = *selectionY = -1;  // Annuler la sélection
    } else {
        // Si les éléments ne sont pas voisins
        printf("Les éléments sélectionnés ne sont pas voisins. Essayez encore.\n");
        *selectionX = *selectionY = -1; // Annuler la sélection
    }
}

void GroupementVerticalHorizontal(char grid[ROWS][COLS], int *points, int pointsItem[nombreTotalPion]) {
    int ItemCompter[ROWS][COLS] = {0};  // tableau pour les cases comptées

    // vérifie des groupements horizontal (3, 4, et 6 items)

     for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 5; j++) {  // vérifie jusqu'à COLS-5 pour éviter de sortir de la grille
            char ActuelItem = grid[i][j];

            // vérifie pour un groupement de 6 items consécutifs
            if (ActuelItem != ' ' && ActuelItem == grid[i][j+1] && ActuelItem == grid[i][j+2] && ActuelItem== grid[i][j+3] && ActuelItem == grid[i][j+4] && ActuelItem == grid[i][j+5]) {

                int nbElement = 0;
                // Supprimer tous les items identiques sur le plateau
                for (int k = 0; k < ROWS; k++) {
                    for (int l = 0; l < COLS; l++) {
                        if (grid[k][l] == ActuelItem){
                                 grid[k][l] = ' ';  // Supprimer les items identiques
                                 nbElement++;

                        }
                    }
                }
                 *points += nbElement;  // ajouter les points pour ce groupement
                pointsItem[getItemIndex(ActuelItem)] += nbElement;  // ajouter les points pour cet item

                // sauter les cases déjà comptées
                j += 5;
            }
            // vérifier pour un groupement de 4 items consécutifs
            else if (ActuelItem != ' ' && ActuelItem == grid[i][j+1] && ActuelItem == grid[i][j+2] && ActuelItem == grid[i][j+3]) {

                int nbElement = 4;
                *points += nbElement;  // Ajouter les points pour ce groupement
                pointsItem[getItemIndex(ActuelItem)] += nbElement;  // Ajouter les points pour cet item

                // marquer ces items comme comptabilisés
                for (int k = 0; k < nbElement; k++) {
                    ItemCompter[i][j+k] = 1;
                }

                // supprimer les items en les remplaçant par des espaces
                for (int k = 0; k < nbElement; k++) {
                    grid[i][j+k] = ' ';
                }

                // Sauter les cases déjà comptées
                j += nbElement - 1;
            }
            // Vérification pour un groupement de 3 éléments consécutifs
            else if (ActuelItem != ' ' && ActuelItem == grid[i][j+1] && ActuelItem == grid[i][j+2]) {

                int nbElement = 3;
                *points += nbElement;  // Ajouter les points pour ce groupement
                pointsItem[getItemIndex(ActuelItem)] += nbElement;  // Ajouter les points pour cet item

                // marquer ces items comme comptabilisés
                for (int k = 0; k < nbElement; k++) {
                    ItemCompter[i][j+k] = 1;
                }

                // supprimer les items en les remplaçant par des espaces
                for (int k = 0; k < nbElement; k++) {
                    grid[i][j+k] = ' ';
                }

                // Sauter les cases déjà comptées
                j += nbElement - 1;
            }
        }
    }

    // Vérification des groupements verticaux (3, 4, et 6 éléments)
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS - 5; i++) {  // Vérifie jusqu'à ROWS-5 pour éviter de sortir de la grille
            char ActuelItem = grid[i][j];

            // vérifier pour un groupement de 6 items consécutifs
            if (ActuelItem != ' ' && ActuelItem == grid[i+1][j] && ActuelItem == grid[i+2][j] && ActuelItem == grid[i+3][j] && ActuelItem == grid[i+4][j] && ActuelItem== grid[i+5][j]) {

                int nbElement = 0;
                // supprimer tous les items identiques sur la grille
                for (int k = 0; k < ROWS; k++) {
                    for (int l = 0; l < COLS; l++) {
                        if (grid[k][l] == ActuelItem) {
                            grid[k][l] = ' ';  // Supprimer les items identiques
                            nbElement++;
                        }
                    }
                }
                *points += nbElement;  // Ajouter les points pour ce groupement
                pointsItem[getItemIndex(ActuelItem)] += nbElement;  // Ajouter les points pour cet item

                // sauter les cases déjà comptées
                i += 5;
            }
            // vérifier pour un groupement de 4 items consécutifs
            else if (ActuelItem != ' ' && ActuelItem == grid[i+1][j] && ActuelItem == grid[i+2][j] && ActuelItem == grid[i+3][j]) {

                int nbElement = 4;
                *points += nbElement;  // Ajouter les points pour ce groupement
                pointsItem[getItemIndex(ActuelItem)] += nbElement;  // Ajouter les points pour cet item

                // marquer ces items comme comptabilisés
                for (int k = 0; k < nbElement; k++) {
                    ItemCompter[i+k][j] = 1;
                }

                // supprimer les items en les remplaçant par des espaces
                for (int k = 0; k < nbElement; k++) {
                    grid[i+k][j] = ' ';
                }

                // Sauter les cases déjà comptées
                i += nbElement - 1;
            }
            // Vérification pour un groupement de 3 éléments consécutifs
            else if (ActuelItem != ' ' && ActuelItem == grid[i+1][j] && ActuelItem== grid[i+2][j]) {

                int nbElement = 3;
                *points += nbElement;  // ajouter les points pour ce groupement
                pointsItem[getItemIndex(ActuelItem)] += nbElement;  // ajouter les points pour cet item

                // marquer ces items comme comptabilisés
                for (int k = 0; k < nbElement; k++) {
                    ItemCompter[i+k][j] = 1;
                }

                // supprimer lesitems  en les remplaçant par des espaces
                for (int k = 0; k < nbElement; k++) {
                    grid[i+k][j] = ' ';
                }

                // Sauter les cases déjà comptées
                i += nbElement - 1;
            }
        }
    }

    // Réinitialiser la grille en enlevant les cases comptabilisées
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (ItemCompter[i][j]) {
                grid[i][j] = ' ';  // marquer les items comme supprimés
            }
        }
    }
     TomberItems(grid);
}


// Fonction pour faire des groupements de rectangle
void GroupementRectangle(char grid[ROWS][COLS], int *points, int pointsItem[nombreTotalPion]) {
    int ItemCompter[ROWS][COLS] = {0}; // Marqueur pour les cases déjà comptées

    for (int ligne = 0; ligne < ROWS; ligne++) {
        for (int colonne = 0; colonne < COLS; colonne++) {
            if (grid[ligne][colonne] != ' ' && !ItemCompter[ligne][colonne]) { // Vérifie si la case n'est pas vide et non comptabilisée
                char item = grid[ligne][colonne];

                // Déterminer la largeur du rectangle
                int largeur = 0;
                while (colonne + largeur < COLS && grid[ligne][colonne + largeur] == item) {
                    largeur++; // Compte les éléments identiques dans la ligne
                }

                // Déterminer la hauteur du rectangle
                int hauteur = 0;
                while (ligne + hauteur < ROWS && grid[ligne + hauteur][colonne] == item) {
                    int k;
                    for (k = 0; k < largeur; k++) {
                        if (grid[ligne + hauteur][colonne + k] != item) {
                            break; // Si la largeur ne correspond pas, on arrête de chercher
                        }
                    }
                    if (k == largeur) { // Si la largeur est valide pour toute la hauteur
                        hauteur++; // Incrémenter la hauteur
                    } else {
                        break; // Si la largeur ne correspond pas, on arrête de chercher
                    }
                }

                // Si un rectangle valide est trouvé (largeur >= 2 et hauteur >= 2)
                if (largeur >= 2 && hauteur >= 2) {
                    int compteurPoint = 2 * (largeur * hauteur); // Calculer les points : 2 * (largeur * hauteur)
                    *points += compteurPoint; // Ajouter les points pour ce rectangle
                    pointsItem[getItemIndex(item)] += compteurPoint; // Ajouter les points à l'élément spécifique

                    // Marquer les éléments du rectangle comme comptabilisés
                    for (int h = 0; h < hauteur; h++) {
                        for (int l = 0; l < largeur; l++) {
                            ItemCompter[ligne + h][colonne + l] = 1;
                        }
                    }

                    // Remplacer les éléments comptabilisés par des espaces (supprimer le groupement)
                    for (int h = 0; h < hauteur; h++) {
                        for (int l = 0; l < largeur; l++) {
                            grid[ligne + h][colonne + l] = ' ';
                        }
                    }
                }

                colonne += largeur - 1; // Sauter les cases déjà comptées dans la même ligne
            }
        }
    }

    // Supprimer les éléments comptabilisés (les cases marquées par 1 dans ItemCompter)
    for (int ligne = 0; ligne < ROWS; ligne++) {
        for (int colonne = 0; colonne < COLS; colonne++) {
            if (ItemCompter[ligne][colonne]) {
                grid[ligne][colonne] = ' '; // Supprimer les éléments comptabilisés
            }
        }
    }
     TomberItems(grid);
}
void GroupementH(char grid[ROWS][COLS], int *points, int pointsItem[nombreTotalPion]) {

    int ItemCompter[ROWS][COLS] = {0}; // tableau pour suivre les cases déjà comptées

    // parcourir toutes les cases de la grille pour rechercher des H
    for (int i = 1; i < ROWS - 1; i++) {  // on commence à la ligne 1 et on s'arrête à la ligne ROWS-2
        for (int j = 1; j < COLS - 1; j++) {  // on commence à la colonne 1 et on s'arrête à la colonne COLS-2
            char ActuelItem= grid[i][j];
            // Vérification si l'élément en position i et j peut être le centre d'un "H"
            if (ActuelItem != ' ' && ActuelItem== grid[i-1][j] && // vérifie l'item au dessus
                ActuelItem == grid[i+1][j] && // vérifie l'item en dessous
                ActuelItem == grid[i][j-1] && // vérifie l'item à gauche
                ActuelItem == grid[i][j+1]) { // vérifie l'item à droite
                // calcul du nombre d'items dans ce "H"
                int compteur = 5; // Un H de base contient 5 items au moins

                // Vérifie s'il existe une extension du H verticalement ou horizontalement
                int gauche = 0, droite = 0;

                // Recherche de l'extension à gauche
                while (j - gauche - 1 >= 0 && grid[i][j - gauche - 1] == ActuelItem) {
                    gauche++;
                }

                // Recherche de l'extension à droite
                while (j + droite + 1 < COLS && grid[i][j + droite+ 1] == ActuelItem) {
                    droite++;
                }

                // Recherche d'extension supplémentaire à verticalement au dessus et en dessous
                int haut = 0, bas = 0;
                while (i - haut - 1 >= 0 && grid[i - haut - 1][j] == ActuelItem) {
                    haut++;
                }

                while (i + bas + 1 < ROWS && grid[i + bas + 1][j] == ActuelItem) {
                    bas++;
                }

                // Calcul du total des éléments dans le H (compte l'élément central et les extensions)
                compteur = 5 + gauche + droite + haut + bas;
                *points += 2 * compteur; // chaque H rapporte 2 * X points
                pointsItem[getItemIndex(ActuelItem)] += 2 * compteur; // Ajouter les points à l'item concerné

                // Marquer ces cases comme comptabilisées
                ItemCompter[i][j] = 1; // centre du "H"
                for (int k = 1; k <= gauche; k++) {
                    ItemCompter[i][j - k] = 1; // côté gauche du "H"
                }
                for (int k = 1; k <= droite; k++) {
                    ItemCompter[i][j + k] = 1; // côté droit du "H"
                }
                for (int k = 1; k <= haut; k++) {
                    ItemCompter[i - k][j] = 1; // haut du "H"
                }
                for (int k = 1; k <= bas; k++) {
                    ItemCompter[i + k][j] = 1; // bas du "H"
                }

                // Supprimer les éléments formant le "H"
                grid[i][j] = ' '; // centre
                for (int k = 1; k <= gauche; k++) {
                    grid[i][j - k] = ' '; // côté gauche
                }
                for (int k = 1; k <= droite; k++) {
                    grid[i][j + k] = ' '; // côté droit
                }
                for (int k = 1; k <= haut; k++) {
                    grid[i - k][j] = ' '; // haut
                }
                for (int k = 1; k <= bas; k++) {
                    grid[i + k][j] = ' '; // bas
                }
            }
        }
    }

    // Après avoir comptabilisé les points pour tous les H, on efface les items déjà comptabilisés
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (ItemCompter[i][j]) {
                grid[i][j] = ' '; // Remplace les items comptabilisés par un espace (ils sont supprimés)
            }
        }
    }
     TomberItems(grid);
}