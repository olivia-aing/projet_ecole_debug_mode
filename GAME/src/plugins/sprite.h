#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL2_imageFilter.h>
// #include <SDL2/SDL2_gfxPrimitives_font.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>

#define larg_fenetre 967
#define haut_fenetre 544
#define vitesse 299

typedef struct _direction{
    bool up;
    bool down;
    bool right;
    bool left;
} direction;

direction *create_direction(void);
void destroy(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture *texture);


typedef struct _personnage{
    int SpriteWidth ;
    int SpriteHeight;

    int position_x ;
    int position_y ;

    int vitesse_x ;
    int vitesse_y ;

    SDL_Rect hitbox;
} personnage;

personnage *create_personnage(void);



