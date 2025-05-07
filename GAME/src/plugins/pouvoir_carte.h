#ifndef POUVOIR_CARTE_H
#define POUVOIR_CARTE_H

#include "fileprio.h"
#include "astar.h"
#include "carte.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void afficher_carte_astar(SDL_Renderer* pRenderer, int **carte_id, chemin *c);

SDL_Texture* pouvoir_astar(SDL_Renderer* renderer, int **map,chemin *c);


#endif
