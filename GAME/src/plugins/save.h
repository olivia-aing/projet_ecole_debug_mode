#ifndef SAVE_H
#define SAVE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct _SaveGame {
    bool num ; // numéro du txt où sera enregistré la sauvegarde (≠ sauvegarde chargée) = 0 par défaut
    int avancement ; // variable de l'histoire
    int idCarte ; // n° de la salle où est actuellement le joueur 
    int x ; // position x dans la salle courante idCarte
    int y ; // position y dans la salle courante idCarte
    bool idVisites[20] ; // liste des idCarte visitées : pour l'avancement de la carte
} Save ;

void saveGame(Save* sauvegarde) ;
bool loadGame(Save* sauvegarde, int num) ;
void addSalleVisitee(Save* sauvegarde, int idCarte) ;
Save* createSave(int numS, int avancement, int idCarte, int x, int y) ;
void printSave(Save* sauvegarde) ;


#endif
