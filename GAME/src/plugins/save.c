#include "save.h"

// enregistre les variables dans la sauvegarde n°<num> : 0 ou 1
void saveGame(Save* sauvegarde) {
    // récupère le lien vers la sauvegarde dans la variable filename
    char filename[30] = "" ; char* beg = "./saves/sauvegarde" ; char* end = ".txt" ; 
    char numStr[2] ; snprintf(numStr, sizeof(numStr), "%d", sauvegarde->num);
    strcat(filename, beg) ; strcat(filename, numStr)  ; strcat(filename, end) ;
    FILE *file = fopen(filename, "w") ; // ouvre le fichier de sauvegarde en write (overwrite)
    if(file == NULL) {
        printf("Not able to open the file :%s\n", filename);
        fclose(file) ;
        return ;
    }
    fprintf(file, "%d\n%d\n%d\n%d", sauvegarde->avancement, sauvegarde->idCarte, sauvegarde->x, sauvegarde->y) ; 
    // ajoute dans le fichier txt les variables de la sauvegarde à la ligne
    
    for (int i = 0 ; i<20 ; i++) {
        fprintf(file, "\n%d", sauvegarde->idVisites[i]) ; // écrit à chaque ligne si la salle n°i a été visitée ou pas (bool)
    }
    fclose(file) ;
}


/* la fonction modifie directement la structure Save en fonction de la sauvegarde
que l'on recupère dans le fichier ./saves/sauvegarde<num> */
bool loadGame(Save* sauvegarde, int num) { // num correspond à la sauvegarde à charger -> on ne sauvegardera pas forcément dans cette sauvegarde
    char filename[30] = "" ; char* beg = "./saves/sauvegarde" ; char* end = ".txt" ; 
    char numStr[2] ; snprintf(numStr, sizeof(numStr), "%d", num);
    strcat(filename, beg) ; strcat(filename, numStr) ; strcat(filename, end) ;

    FILE *file = fopen(filename, "r"); // ouvre la sauvegarde en lecture
    if(file == NULL) {
        printf("Not able to open the file : %s\n", filename);
        fclose(file) ;
        return 1 ;
    }
    int vide = feof(file) ; // vérifie si le .txt est vide : end of file ?
    if (vide) {
        // la sauvegarde à charger est vide -> on lance un nouveau jeu 
        sauvegarde = createSave(sauvegarde->num , 0, 0, 0, 0) ; // par défault : sauvegarde vide enregistrée dans sauvegarde0.txt
    } else {
        // printf("On lance le jeu de la sauvegarde n°%d \n", sauvegarde->num) ;
        char content[10];
        fgets(content, 50, file); // lit la première ligne du txt et l'inscrit dans 'content' (char[10])
        sauvegarde->avancement = atoi(content) ; // char -> int
        fgets(content, 50, file); // lit la prochaine ligne -> char content[10]
        sauvegarde->idCarte = atoi(content) ;
        fgets(content, 50, file);
        sauvegarde->x = atoi(content) ;
        fgets(content, 50, file);
        sauvegarde->y = atoi(content) ;
        for (int i=0 ; i<20 ; i++) { // pour les 20 salles :
            if (atoi(fgets(content, 50, file))) { // si la ligne corresp à la salle i = 1 
                addSalleVisitee(sauvegarde, i) ; // ajoute la salle i à la liste des salles visitées
            }
        }
    } 
    fclose(file);
    return vide ; 
}


// ajoute la salle n°idCarte à la liste des salles déjà visitées
void addSalleVisitee(Save* sauvegarde, int idCarte) {
    sauvegarde->idVisites[idCarte] = true ;
}


// créé une sauvegarde avec les parametres définis avec aucune salle visitée
Save* createSave(int numS, int avancement, int idCarte, int x, int y) {
    Save* sauvegarde = (Save*)malloc(sizeof(Save)) ;
    if (sauvegarde != NULL) {
        sauvegarde->num = numS ; // définit le n° de la sauvegarde à utiliser pour l'enregistrer
        sauvegarde->avancement = avancement ; 
        sauvegarde->idCarte = idCarte ; 
        sauvegarde->x = x ; 
        sauvegarde->y = y ; 
        for (int i = 0; i < 20; i++) { // initialise à aucune salle n'a été visitée
            sauvegarde->idVisites[i] = false ; 
        }
    }
    return sauvegarde ;
}


// coté dev : écrit dans le terminal l'état actuel de la sauvegarde en cours (jamais visible coté joueur)
void printSave(Save* sauvegarde) { 
    printf("-----\nVérification de l'état de la sauvegarde : n°%d\n", sauvegarde->num);
    printf("avancement : %d, carte actuelle : %d, x : %d, y : %d\n", sauvegarde->avancement, sauvegarde->idCarte, sauvegarde->x, sauvegarde->y);
    for (int i = 0 ; i<20 ; i++) {
        printf("salle n°%d visitée ?\t%s\n", i, sauvegarde->idVisites[i] == 0 ? "false" : "true" ) ;
    }
    printf("-----\n") ;
}
