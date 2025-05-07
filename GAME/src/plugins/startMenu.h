#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "sounds.h"
#include "save.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// int Init (SDL_Window** window, SDL_Renderer** renderer) ;
int Quit (SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, Mix_Music* music) ;

SDL_Texture* loadImage(const char path[], SDL_Renderer *renderer) ;
void renderStartBG(SDL_Renderer *renderer, SDL_Texture* TextureBG, int num) ;

void checkClick (SDL_Event event, Save* sauvegarde, int* step, SDL_Rect* Rect1, SDL_Rect* Rect2, SDL_Rect* optionsMenu, SDL_Rect* optionsBack, SDL_Rect* save0, SDL_Rect* save1) ;
void defRect (SDL_Rect* Rect1, SDL_Rect* Rect2, SDL_Rect* optionsMenu, SDL_Rect* optionsBack, SDL_Rect* save0, SDL_Rect* save1, int w, int h) ;

int startMenu(SDL_Window** window, SDL_Renderer** renderer, Save* sauvegarde) ;

int BGmusic(char* event, Mix_Music** music) ;

