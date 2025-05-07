#ifndef CARTE_H
#define CARTE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define LARGEUR_TILE 16
#define HAUTEUR_TILE 16

#define NOMBRE_TILE_LARGEUR 34
#define NOMBRE_TILE_HAUTEUR 34

#define NOMBRE_CARTES 5
#define NOMBRE_CARTES_BIS 8



void afficher_carte(SDL_Renderer* pRenderer, int** carte_id);
void afficher_carte0(SDL_Renderer* pRenderer, int** carte_id) ;
void afficher_carte1(SDL_Renderer* pRenderer, int** carte_id);
void afficher_carte2(SDL_Renderer* pRenderer, int** carte_id) ;
void afficher_carte3(SDL_Renderer* pRenderer, int** carte_id) ;

extern int carte1[NOMBRE_TILE_HAUTEUR][NOMBRE_TILE_LARGEUR];

extern int carte1b[NOMBRE_TILE_HAUTEUR][NOMBRE_TILE_LARGEUR];

int** trans(int carte_id[NOMBRE_TILE_HAUTEUR][NOMBRE_TILE_LARGEUR]);

int*** initialiser_carte(void);

int*** initialiser_carte_bis(void);

void free_carte(int **carte);

void free_cartes(int ***cartes);

void free_cartes_bis(int ***cartes);

#endif
