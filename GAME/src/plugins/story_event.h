#ifndef __STORY_EVENT_H__
#define __STORY_EVENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "window_display.h"
#include "dialogue.h"
#include "terminal.h"
#include "carte.h"

//
#define BLEU 6

// Evenements généraux

int call_event(int variable_histoire, int** carte, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText);
int vh_increment(int variable_histoire, bool gentil);
int skippeable(int skip, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font);
void remise_surface(int variable_histoire, bool frame, int** carte, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText, SDL_Window* gWindow, SDL_Renderer* gRenderer);
void entrer(SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font);

// Bonjour monsieur le test
int event_test(int variable_histoire, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font);

// Ensemble des cutscenes
int intro_cutscene(int** carte,SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText);
int prologue(int** carte, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText);
int ep12(int variable_histoire,int** carte, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText);
int ep34(int variable_histoire,int** carte, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText);
int ep56(int variable_histoire,int** carte, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText);
int ep78(int variable_histoire,int** carte, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText);
int ep910(int variable_histoire,int** carte, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText);


// Aled Tutoriel
int call_tutoriel(int variable_histoire, int** carte, int agacement, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText);


#endif
