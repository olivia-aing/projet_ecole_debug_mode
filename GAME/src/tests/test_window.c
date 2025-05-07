/*Ajout des bibliothèques*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./../plugins/window_display.h"

int window_height = 600;
int window_width = 800;


void init_wCol(SDL_Window* gWindow, SDL_Renderer* gRenderer)
{
    SDL_Surface* gSurface = SDL_GetWindowSurface(gWindow);
    int w = gSurface->w;
    int h = gSurface->h;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(gRenderer, 150, 150, 150, 255);
    SDL_RenderFillRect(gRenderer, &rect);
    SDL_RenderPresent(gRenderer);

}

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
        SDL_DestroyRenderer(gRenderer);SDL_DestroyWindow(gWindow);        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    if (gRenderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] gRenderer > %s", SDL_GetError());
        SDL_DestroyRenderer(gRenderer);SDL_DestroyWindow(gWindow);        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    SDL_Event events;
    bool isOpen = true ;
    bool box_open = false;
    int variable_histoire=0;
    SDL_Texture* texture;
    SDL_Rect spriteRect;
    SDL_Rect destRect;

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
                    case SDLK_UP:
                        if (!box_open){
                            init_wCol(gWindow,gRenderer);
                            dialogue_box_nb(gWindow, gRenderer);
                            box_open = true;
                        }
                        else{
                            box_destroy(variable_histoire, gWindow, gRenderer,spriteRect,destRect,texture);
                            box_open = false;
                            init_wCol(gWindow,gRenderer);
                        }
                        printf("Dialogue nb\n");
                        break;
                    
                    case SDLK_DOWN:
                        if (!box_open){
                            init_wCol(gWindow,gRenderer);
                            dialogue_box_colour(gWindow, gRenderer);
                            box_open = true;
                        }
                        else{
                            box_destroy(variable_histoire, gWindow, gRenderer,spriteRect,destRect,texture);
                            box_open = false;
                            init_wCol(gWindow,gRenderer);
                        }
                        printf("Dialogue col\n");
                        break;

                    case SDLK_LEFT:
                        if (!box_open){
                            init_wCol(gWindow,gRenderer);
                            terminal_box_nb(gWindow, gRenderer);
                            box_open = true;
                        }
                        else{
                            box_destroy(variable_histoire, gWindow, gRenderer,spriteRect,destRect,texture);
                            box_open = false;
                            init_wCol(gWindow,gRenderer);
                        }
                        printf("Terminal nb\n");
                        break;

                    case SDLK_RIGHT:
                        if (!box_open){
                            init_wCol(gWindow,gRenderer);
                            terminal_box_colour(gWindow, gRenderer);
                            box_open = true;
                        }
                        else{
                            box_destroy(variable_histoire, gWindow, gRenderer,spriteRect,destRect,texture);
                            box_open = false;
                            init_wCol(gWindow,gRenderer);
                        }
                        printf("Terminal col\n");
                        break;
                    
                    break;
                    }
 
            }
        }
    }
    if (box_open){
        box_destroy(variable_histoire, gWindow, gRenderer,spriteRect,destRect,texture);
        box_open = false;
        
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    return EXIT_SUCCESS;
}
