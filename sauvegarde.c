#include "sauvegarde.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sauvegarde(char nom[]) // rajouter paramètres int progressions
{
    char str[10]="../"; // nom du fichier pour aller dans route ici
    char nom[]; // nom saisie par l'utilisateur
    strcat(str,nom); // concat 2 char précédent
    strcat(str,".txt"); // concat en ajt txt

    FILE* pf = fopen(str, "w"); // recuperer fichier chaine de caractère
    if (pf == NULL) {
        printf("Erreur d'ouverture de fichier.");
    }
    fprintf(pf, "Le nom de l'utilisateur est %s", nom);
    fclose(pf);
    pf=NULL;

}



    fclose(pf);
    pf = NULL;

}
// Created by ayyub on 25/11/2024.
//