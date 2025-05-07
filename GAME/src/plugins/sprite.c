#include "sprite.h"


void destroy(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture *texture){
    if (window!=NULL){
        SDL_DestroyWindow(window);
    }

    if (renderer!=NULL){
        SDL_DestroyRenderer(renderer);
    }

    if (texture!=NULL){
        SDL_DestroyTexture(texture);
    }
    SDL_Quit();
}


// void Initialise(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture *texture){
//     if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) !=0){
//         printf("error in intialization of SDL : %s\n", SDL_GetError());
//         return;
//     }

//     window = SDL_CreateWindow("Mouvement du sprite",
//                                SDL_WINDOWPOS_CENTERED,
//                                SDL_WINDOWPOS_CENTERED,
//                                larg_fenetre,
//                                haut_fenetre,
//                                0 );
//     if (window==NULL){
//         printf("error in creation of SDL window : %s\n", SDL_GetError());
//         SDL_Quit();
//         return;
//     }
//     Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ;
//     renderer = SDL_CreateRenderer(window, -1, flags);

//     if (renderer==NULL){
//         printf("error in creation of SDL renderer : %s\n", SDL_GetError());
//         destroy(window,NULL,NULL);
//         return;
//     }

//     SDL_Surface *surface =NULL;
//     surface = IMG_Load("././img/sprites/Kiki_sprite_sheet.png");
//     if (surface==NULL){
//         printf("error in creation of SDL surface : %s\n", SDL_GetError());
//         destroy(window,renderer,NULL);
//         return;
//     }

//     texture = SDL_CreateTextureFromSurface(renderer, surface);
//     SDL_FreeSurface(surface);

//     if (texture==NULL){
//         printf("error in creation of SDL texture : %s\n", SDL_GetError());
//         destroy(window,renderer,NULL);
//         return;
//     }
//     return;

// }

direction *create_direction(void){
    direction *dir = malloc(sizeof(direction));
    dir->down =false;
    dir->up = false;
    dir->left = false;
    dir->right = false;
    return dir;
}

personnage *create_personnage(void){
    personnage *perso = malloc(sizeof(personnage));

    perso ->position_x = 0;
    perso ->position_y = 0;

    perso->vitesse_x = 0;
    perso->vitesse_y = 0;

    perso->SpriteHeight = 0;
    perso->SpriteWidth = 0;

    SDL_Rect hitbox;
    perso->hitbox = hitbox;
    
    return perso;
}
