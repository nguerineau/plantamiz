#include "sauvegarde.h"//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sauvegarde(char nom[], int progression) {
    int i = 0;
    FILE* pf = fopen("../monFichier.txt", "w");
    if (pf == NULL) {
        printf("Erreur d'ouverture de fichier.");
    }


    fclose(pf);
    pf = NULL;

}
// Created by ayyub on 25/11/2024.
//