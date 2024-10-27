//
// Created by Walid BENSAID on 27/10/2024.
//

#ifndef CONTRAT_PLATEAU_H
#define CONTRAT_PLATEAU_H
#include "pion.h"

typedef struct {
    int objectifsContrat[nombreTotalPion]; // Objectifs pour chaque type de pion pour les trois niveaux
    int coupsMax; // Coups maximum
} ContratPlateau;


#endif //CONTRAT_PLATEAU_H
