#include <stdio.h>
#include "plateau.h"
#include "pion.h"

int main(void) {
    int plateau[ligne][colonne];
    init_plateau(plateau);
    display_plateau(plateau);
    while(1);
    return 0;
}
