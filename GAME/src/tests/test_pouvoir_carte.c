// #include <stdio.h>
// #include <stdlib.h>
// #include "carte.h"
// #include "astar.h"
// #include "fileprio.h"

// #include <SDL2/SDL.h>

#include "../plugins/pouvoir_carte.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
    /*Initialisation, vérification que tout fonctionne*/
    int ctest[NOMBRE_TILE_HAUTEUR][NOMBRE_TILE_LARGEUR] = {
{0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0},
{0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0},

{0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0},
{0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0},
{0,0, 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0, 0,0},
{0,0, 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0, 0,0},
{0,0, 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0, 0,0},
{0,0, 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0, 0,0},
{0,0, 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0, 0,0},
{0,0, 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0, 0,0},
{0,0, 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0, 0,0},
{0,0, 0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0, 0,0},
{0,0, 0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0, 0,0},
{0,0, 0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1, 0,0},
{0,0, 0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0, 0,0},
{0,0, 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0,0},
{0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0, 0,0},
{0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0, 0,0},

{0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0},
{0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0}
};
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window* pWindow = NULL ;     
    SDL_Renderer* pRenderer = NULL ;
    if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }
    SDL_Event events;
    bool isOpen = true ;
    // chemin *c=NULL;
    position *src=create_position(0,0);
    // c=create_chemin(src,NULL);
    position *dst=create_position(6,6);
    int **cc=trans(ctest);
    print_map(cc);
    // chemin *c2=astar(src,dst,cc);
    // print_chemin(c2);
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
            }
        }
        // chemin *c=astar(src,dst,carte1);
        // afficher_carte_astar(pRenderer, cc,c2);
        SDL_Texture *texture=pouvoir_astar(pRenderer,cc,src,dst);
        SDL_RenderCopy(pRenderer,texture,NULL,NULL);
        SDL_RenderPresent(pRenderer);
        SDL_DestroyTexture(texture);
    }
    free(src);
    free(dst);
    // free_chemin(c2);
    free_carte(cc);
    SDL_DestroyRenderer(pRenderer);SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return EXIT_SUCCESS;
}
