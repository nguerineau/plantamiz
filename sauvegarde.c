#include "sauvegarde.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sauvegarde(char nom[], int niveau) // rajouter paramètres int progressions
{
    char str[10]="../"; // nom du fichier pour aller dans route ici
    strcat(str,nom); // concat 2 char précédent
    strcat(str,".txt"); // concat en ajt txt

    FILE* pf = fopen(str, "w"); // recuperer fichier chaine de caractère
    if (pf == NULL) {
        printf("Erreur d'ouverture de fichier.");
    }
    fprintf(pf, "Le nom de l'utilisateur est %s et le niveau est %d " , nom,niveau);
    fclose(pf);
    pf=NULL;
}






// Created by ayyub on 25/11/2024.
//