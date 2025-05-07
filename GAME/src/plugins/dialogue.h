#ifndef __DIALOGUE_H__
#define __DIALOGUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "window_display.h"

void cadre(SDL_Window* gWindow, SDL_Renderer* gRenderer);
void dialogue(char* name, char* expression, char* texte, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font);
void dialogue_prog(char* name, char* expression, char* texte, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font);
void narration(char* texte, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font);
void narration_prog(char* texte, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font);



#endif
