//
// Created by ayyub on 25/11/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sauvegarde.h"
const char *cheminFichier = "../utilisateurs.txt";

void sauvegarde(int niveau,int score) {
    FILE *fichier = fopen(cheminFichier, "r+");
    if (fichier == NULL) {
        fichier = fopen(cheminFichier, "w");
        if (fichier == NULL) {
            printf("Erreur : impossible de créer ou d'ouvrir le fichier.\n");
            return;
        }
    }

    char nom[50];
    char nomLu[50];
    int niveaulu, scorelu;
    int trouve = 0;

    // Entrée utilisateur
    printf("\n\tentree votre nom :\n\t");
    scanf(" %s", nom);

    fseek(fichier, 0, SEEK_SET);

    char buffer[1000] = {0};
    int position = 0; //position dans le fichier

    while (fscanf(fichier, "%[^:]:%d:%d\n", nomLu, &niveaulu, &scorelu) == 3) {
        if (strcmp(nom, nomLu) == 0) { // comparée le nom à sauvegarder et le nom lu dans le fichier pour remplacer les donnée
            trouve = 1;
        }
        position += sprintf(buffer + position, "%s:%d:%d\n", strcmp(nom, nomLu) == 0 ? nom : nomLu, strcmp(nom, nomLu) == 0 ? niveau : niveaulu, strcmp(nom, nomLu) == 0 ? score : scorelu);
    }

    if (!trouve) { // si l'utilisateur n'existe pas alors on le crée
        position += sprintf(buffer + position, "%s:%d:%d\n", nom, niveau, score);
    }

    freopen(cheminFichier, "w", fichier);
    fputs(buffer, fichier);

    fclose(fichier);
}

void charger(const char *nomRecherche) {
    FILE *fichier = fopen(cheminFichier, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    char nom[50];
    int niveau, score;
    int trouve = 0;

    while (fscanf(fichier, "%[^:]:%d:%d\n", nom, &niveau, &score) == 3) {
        if (strcmp(nom, nomRecherche) == 0) {
            printf("\tDonnees trouvees : Nom = %s, Niveau = %d, Score = %d\n", nom, niveau, score);
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("\tErreur : Aucun utilisateur trouve avec le nom '%s'.\n", nomRecherche);
    }

    fclose(fichier);
}

void searchRequest() {
    char nomRecherche[50];
    printf("\n\tSaisir le nom a rechercher :\n\t");
    scanf(" %s", nomRecherche);
    charger(nomRecherche);

}