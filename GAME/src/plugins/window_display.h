#ifndef __WINDOW_DISPLAY_H__
#define __WINDOW_DISPLAY_H__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "carte.h"

void dialogue_box_nb(SDL_Window* gWindow, SDL_Renderer* gRenderer);
void terminal_box_nb(SDL_Window* gWindow, SDL_Renderer* gRenderer);
void dialogue_box_colour(SDL_Window* gWindow, SDL_Renderer* gRenderer);
void terminal_box_colour(SDL_Window* gWindow, SDL_Renderer* gRenderer);

void box_destroy(int** carte, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText);

#endif
