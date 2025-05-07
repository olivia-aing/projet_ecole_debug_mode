#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "window_display.h"
#include "save.h"


void open_terminal(int variable_histoire, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font);
void affiche_commandes(int variable_histoire, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font);
int terminal (SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* GrandPixel, Save* sauvegarde,int *debug_mod,int *pouvoir_carte,int *compteur_astar);




#endif
