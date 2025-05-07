/*Ajout des bibliothèques*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../plugins/story_event.h"

int window_height = 800;
int window_width = 1104;

int main(int argc, char *argv[])
{
    /*Initialisation, vérification que tout fonctionne*/
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] init > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window* gWindow = NULL ;
    gWindow = SDL_CreateWindow("\\debug_mode",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);   
    SDL_Renderer* gRenderer = NULL ;
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gWindow == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] gWindow > %s", SDL_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    if (gRenderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] gRenderer > %s", SDL_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    if (IMG_Init(IMG_INIT_PNG)==0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] IMG_Init > %s", SDL_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        IMG_Quit();    
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    if (TTF_Init()==-1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] TTF_Init > %s", TTF_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        TTF_Quit();
        IMG_Quit();    
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    TTF_Font* PTPixel = NULL;
    PTPixel = TTF_OpenFont("img/assets/Puzzle-Tale-Pixel-Regular.ttf",20);
    TTF_SetFontStyle(PTPixel, TTF_STYLE_NORMAL);
    TTF_SetFontHinting(PTPixel, TTF_HINTING_NORMAL);

    if(PTPixel==NULL)
    {
        printf("Erreur de création de la police : %s", TTF_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] TTF_Init > %s", TTF_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        TTF_CloseFont(PTPixel);
        TTF_Quit();
        IMG_Quit();    
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    TTF_Font* GrandPixel = NULL;
    GrandPixel = TTF_OpenFont("img/assets/Grand9K-Pixel.ttf",20);
    TTF_SetFontStyle(GrandPixel, TTF_STYLE_NORMAL);
    TTF_SetFontHinting(GrandPixel, TTF_HINTING_NORMAL);

    if(GrandPixel==NULL)
    {
        printf("Erreur de création de la police : %s", TTF_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] TTF_Init > %s", TTF_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        TTF_CloseFont(PTPixel);
        TTF_CloseFont(GrandPixel);
        TTF_Quit();
        IMG_Quit();    
        SDL_Quit(); 
        return EXIT_FAILURE;
    }



    /*
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    */

    SDL_Rect test;
    test.x=0;
    test.y=0;
    test.w=window_width;
    test.h=window_height;

    SDL_SetRenderDrawColor(gRenderer,100,100,100,255);
    SDL_RenderFillRect(gRenderer,&test);
    SDL_RenderPresent(gRenderer);
    SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
    

    SDL_Event events;
    bool isOpen = true ;
    int story_progress;
    printf("Entrer l'int de l'event à essayer : \n");
    scanf("%d",&story_progress);
    int recall;

    /*Boucle du jeu lorsqu'il est ouvert*/
    while (isOpen)
    {
        
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {

                case SDL_KEYDOWN:
                switch(events.key.keysym.sym)
                {
                    case SDLK_UP:
                        recall = story_progress;
                        story_progress = call_event(story_progress, gWindow, gRenderer, events, PTPixel, GrandPixel);
                        if (recall == story_progress){
                            isOpen = false;
                        }
                        printf("%d\n",story_progress);
                        break;
                }
                break;
                
                case SDL_QUIT:
                /*Le cas où on appuie sur la croix, pour fermer la fenêtre*/
                    isOpen = false;
                    break;

                
 
            }
        }
    }

    //SDL_FreeSurface(test); Rappel : test est free dans le  box_destroy !
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(PTPixel);
    TTF_CloseFont(GrandPixel);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
