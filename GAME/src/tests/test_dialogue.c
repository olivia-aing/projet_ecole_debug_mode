/*Ajout des bibliothèques*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../plugins/dialogue.h"

int window_height = 800;
int window_width = 500;

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
    PTPixel = TTF_OpenFont("img/assets/Puzzle-Tale-Pixel-Regular.ttf",50);

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

    TTF_SetFontSize(PTPixel, 30);
    

    SDL_Event events;
    bool isOpen = true ;
    bool box_open = false;
    SDL_Surface* test = NULL;
    int dialogue_progress = 0;

    /*Boucle du jeu lorsqu'il est ouvert*/
    while (isOpen)
    {
        
        while (SDL_PollEvent(&events))
        {
            

            switch (events.type)
            {
                case SDL_QUIT:
                /*Le cas où on appuie sur la croix, pour fermer la fenêtre*/
                    isOpen = false;
                    break;

                case SDL_KEYDOWN:
                switch (events.key.keysym.sym) {
                    case SDLK_DOWN:
                        switch(dialogue_progress)
                            {
                                case 0 :
                                    test = dialogue_box_nb(gWindow, gRenderer);
                                    cadre(gWindow, gRenderer);
                                    dialogue("Kiki", "base", "Il est grand temps d'essayer avec un texte un peu plus long.\n Comme celui-ci, par exemple.\n", gWindow, gRenderer, PTPixel);
                                    dialogue_progress++;
                                    break;
                                case 1 :
                                    dialogue("Kiki", "base", "Et ça, c'est le second dialogue !\n\n\n\n", gWindow, gRenderer, PTPixel);
                                    dialogue_progress++;
                                    break;
                                case  2 :
                                    test = dialogue_box_nb(gWindow, gRenderer);
                                    narration("Et ça, c'est ce que ça donne sans portrait !\n\n\n",gWindow,gRenderer,PTPixel);
                                    dialogue_progress++;
                                    break;
                                case 3 :
                                    box_destroy(test, gWindow);
                                    box_open = false;
                                    dialogue_progress=0;
                                    break;

                                

                            }
                        break;
                }
 
            }
        }
    }
    
    if (box_open){
        box_destroy(test, gWindow);
        box_open = false;
    }
    
    //SDL_FreeSurface(test); Rappel : test est free dans le  box_destroy !
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(PTPixel);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}