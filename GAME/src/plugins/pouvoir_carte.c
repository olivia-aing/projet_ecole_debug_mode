#include "pouvoir_carte.h"

void afficher_carte_astar(SDL_Renderer* pRenderer, int **carte_id, chemin *c){
    for (int i=0; i<NOMBRE_TILE_HAUTEUR; i++){
        for (int j=0; j<NOMBRE_TILE_LARGEUR; j++){
            SDL_Rect tile = { .h = LARGEUR_TILE,
                              .w = HAUTEUR_TILE,
                              .x = j * LARGEUR_TILE,
                              .y = i * HAUTEUR_TILE,
                            };

            if(carte_id[i][j] == 1 || carte_id[i][j] == -1){
                SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
            } else if (carte_id[i][j] > 1){
                SDL_SetRenderDrawColor(pRenderer, 253, 63, 146, 255);
            } else if (carte_id[i][j] < -1){
                SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);
            } else if (present(j,i,c)) {
                SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
            } else {
                SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
            }    

            SDL_RenderFillRect(pRenderer, &tile);
        }
    }
}

SDL_Texture* pouvoir_astar(SDL_Renderer* renderer, int **map,chemin *c){
    // chemin *c=astar(src,dst,map);
    
    SDL_Surface* surface = SDL_CreateRGBSurface(0,NOMBRE_TILE_LARGEUR*LARGEUR_TILE,NOMBRE_TILE_HAUTEUR*HAUTEUR_TILE,32,0x00FF0000,0x0000FF00,0x000000FF,0xFF000000);
    SDL_FillRect(surface, NULL,SDL_MapRGB(surface->format,0,0,0)); // Fill the surface with black color

    SDL_Rect rect;
    rect.w=LARGEUR_TILE;
    rect.h=HAUTEUR_TILE;

    for (int y=0; y<NOMBRE_TILE_HAUTEUR;y++){
        for (int x=0;x<NOMBRE_TILE_LARGEUR;x++){
            rect.x=x*LARGEUR_TILE;
            rect.y=y*HAUTEUR_TILE;

            if (map[y][x]==1 || map[y][x]==-1){
                SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0,0,0)); //white for wall but don't see the walls
            } else if (map[y][x]>1) {
                SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,253,63,146)); //interrupteur pour changer de carte
            } else if (map[y][x]<-1){
                SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,255,255,0)); // interrupteurs de changements de murs
            } else if (present(x,y,c)) {
                SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0,255,0));
            } else {
                SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0,0,0)); //black for empty space
            }
        }
    }
    // free_chemin(c);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return texture;
}
