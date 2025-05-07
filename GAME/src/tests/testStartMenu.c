#include "../plugins/startMenu.h"


int main(int argc, char *argv[]) {
    SDL_Window* window = NULL ;
    SDL_Renderer* renderer = NULL ;
    int status = EXIT_FAILURE ; // renvoyée à la fin et vérifie si erreur dans l'exec
    Save *sauvegarde = createSave(0, 0, 0, 0, 0); // créé une sauvegarde vide (modifiée si besoin dans le menu start) par défaut s'enregistre dans la n°0

    TTF_Font* font = NULL;
    SDL_Event event ;
    int quit = 0 ;

    Init(&window, &renderer) ;  // /!\ tmp is freed here

    quit = startMenu(&window, &renderer, sauvegarde) ;

    while (quit != 1) { 
        SDL_RenderPresent(renderer); 
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    quit = 1 ;
                    break ;
                case SDL_KEYDOWN :
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        quit = 1 ;
                    }
                    break ;
            }
        }
    }
    saveGame(sauvegarde) ;
    // printf("anyway quits here\n\n");
    status = Quit(&window, &renderer, &font, NULL) ;
    return status ; 
}

