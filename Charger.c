//
// Created by ayyub on 30/11/2024.
//
#include <stdio.h>
#include "Charger.h"
#include <string.h>


void charger(const char *cheminFichier, const char *nomRecherche) {
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

void searchRequest(const char *cheminFichier) {
        char nomRecherche[50];
        printf("\n\tSaisir le nom a rechercher :\n\t");
        scanf(" %s", nomRecherche);
        charger(cheminFichier, nomRecherche);

}