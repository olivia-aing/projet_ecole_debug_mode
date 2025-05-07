#include "window_display.h"
#include "carte.h"

// Ouverture de la boîte de dialogue (noir et blanc)
void dialogue_box_nb(SDL_Window* gWindow, SDL_Renderer* gRenderer){

    // Récupération de l'écran et de sa taille
    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    int w = gScreen->w;
    int h = gScreen->h;

    int box_h = (int)floor(0.25*h);


    // Création de la surface copie (utilisée plus tard)    
    /*SDL_Surface* copie = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA8888);

    if (copie==NULL){
        printf("Echec de surface, %s \n", SDL_GetError());
    }*/
    

    SDL_Rect rect;
    rect.x = 0;
    rect.y = h-box_h;
    rect.h = box_h;
    rect.w = w;

    /*
    SDL_PixelFormat *format;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
    Uint32 blanc = SDL_MapRGB(format, 255, 255, 255);
    Uint32 fond_diag = SDL_MapRGB(format, 0, 0, 0);*/
    /*r g b*/

    // On garde dans copie ce qu'il y a actuellement sur l'écran
    //SDL_BlitSurface(gScreen, NULL, copie, NULL);
    /*
    // On réinitialise le Renderer
    SDL_RenderClear(gRenderer);
    // On remet sur l'écran ce qu'il y avait
    SDL_BlitSurface(copie, NULL, gScreen, NULL);
    // On update la fenêtre de jeu
    SDL_UpdateWindowSurface(gWindow);
    */

    // Des couleurs et des formes, à chaque fois qu'on change de couleur, il faut faire un RenderPresent
    
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(gRenderer, &rect);
    SDL_RenderPresent(gRenderer);

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &rect);
    SDL_RenderPresent(gRenderer);

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

    

    //SDL_FreeFormat(format);

    // Ne pas oublier de free la surface de l'écran, on n'en a plus besoin !
    SDL_FreeSurface(gScreen);

    // On renvoie la copie de l'écran de base en mémoire, ça nous servira pour tout refermer
    return;

}

// Ouverture de la boîte de terminal (noir et blanc)
void terminal_box_nb(SDL_Window* gWindow, SDL_Renderer* gRenderer){

    // Récupération de l'écran et de sa taille
    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    int w = gScreen->w;
    int h = gScreen->h;

    /*
    SDL_Surface* copie2 = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA8888);

    if (copie2==NULL){
        printf("Echec de surface, %s \n", SDL_GetError());
    }
    */
    

    /*SDL_PixelFormat *format;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
    Uint32 blanc = SDL_MapRGB(format, 255, 255, 255);
    Uint32 fond_diag = SDL_MapRGB(format, 0, 0, 0);*/
    
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = h;
    rect.w = w;

    /*
    SDL_Rect rectbot;
    rectbot.x = 1;
    rectbot.y = h-bot_h;
    rectbot.h = bot_h-1;
    rectbot.w = w-2;

    SDL_Rect rectup;
    rectup.x = 1;
    rectup.y = 1;
    rectup.h = h-bot_h-2;
    rectup.w = w-2;
    */

    /*
    SDL_BlitSurface(gScreen, NULL, copie2, NULL);
    SDL_RenderClear(gRenderer);
    SDL_BlitSurface(copie2, NULL, gScreen, NULL);
    SDL_UpdateWindowSurface(gWindow);
    */

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 50);
    SDL_RenderFillRect(gRenderer, &rect);
    SDL_RenderPresent(gRenderer);

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &rect);
    SDL_RenderPresent(gRenderer);

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);


    /*SDL_FillRect(gScreen, &rect, blanc);
    SDL_FillRect(gScreen, &rectbot, fond_diag);
    SDL_FillRect(gScreen, &rectup, fond_diag);*/

    //SDL_FreeFormat(format);
    SDL_FreeSurface(gScreen);

    return;

}

// Ouverture de la boîte de dialogue (couleur)
void dialogue_box_colour(SDL_Window* gWindow, SDL_Renderer* gRenderer){
    // Récupération de l'écran et de sa taille
    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    int w = gScreen->w;
    int h = gScreen->h;

    int box_h = (int)floor(0.25*h);

    
    /*SDL_Surface* copie = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA8888);

    if (copie==NULL){
        printf("Echec de surface, %s \n", SDL_GetError());
    }*/
    

    SDL_Rect rect;
    rect.x = 0;
    rect.y = h-box_h;
    rect.h = box_h;
    rect.w = w;


    /*SDL_PixelFormat *format;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
    Uint32 blanc = SDL_MapRGB(format, 255, 255, 255);
    Uint32 fond_diag = SDL_MapRGB(format, 0, 0, 0);*/
    /*r g b*/

    /*
    SDL_BlitSurface(gScreen, NULL, copie, NULL);
    SDL_RenderClear(gRenderer);
    SDL_BlitSurface(copie, NULL, gScreen, NULL);
    SDL_UpdateWindowSurface(gWindow);
    */

    SDL_SetRenderDrawColor(gRenderer, 0, 10, 50, 50);
    SDL_RenderFillRect(gRenderer, &rect);
    SDL_RenderPresent(gRenderer);

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &rect);
    SDL_RenderPresent(gRenderer);

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

    

    //SDL_FreeFormat(format);
    SDL_FreeSurface(gScreen);

    return;

}

// Ouverture de la boîte de terminal (couleur)
void terminal_box_colour(SDL_Window* gWindow, SDL_Renderer* gRenderer){
    // Récupération de l'écran et de sa taille
    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    int w = gScreen->w;
    int h = gScreen->h;


    /*
    SDL_Surface* copie2 = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA8888);

    if (copie2==NULL){
        printf("Echec de surface, %s \n", SDL_GetError());
    }*/
    

    /*SDL_PixelFormat *format;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
    Uint32 blanc = SDL_MapRGB(format, 255, 255, 255);
    Uint32 fond_diag = SDL_MapRGB(format, 0, 0, 0);*/
    
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = h;
    rect.w = w;

    /*
    SDL_Rect rectbot;
    rectbot.x = 1;
    rectbot.y = h-bot_h;
    rectbot.h = bot_h-1;
    rectbot.w = w-2;

    SDL_Rect rectup;
    rectup.x = 1;
    rectup.y = 1;
    rectup.h = h-bot_h-2;
    rectup.w = w-2;
    */

    /*
    SDL_BlitSurface(gScreen, NULL, copie2, NULL);
    SDL_RenderClear(gRenderer);
    SDL_BlitSurface(copie2, NULL, gScreen, NULL);
    SDL_UpdateWindowSurface(gWindow);
    */

    SDL_SetRenderDrawColor(gRenderer, 0, 10, 50, 50);
    SDL_RenderFillRect(gRenderer, &rect);
    SDL_RenderPresent(gRenderer);
    
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &rect);
    SDL_RenderPresent(gRenderer);

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);


    /*SDL_FillRect(gScreen, &rect, blanc);
    SDL_FillRect(gScreen, &rectbot, fond_diag);
    SDL_FillRect(gScreen, &rectup, fond_diag);*/

    //SDL_FreeFormat(format);
    SDL_FreeSurface(gScreen);

    return;

}


// Fermeture de fenêtre (peu importe la taille)
void box_destroy(int** carte, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText){
    SDL_RenderClear(gRenderer);
    afficher_carte(gRenderer, carte) ;
    SDL_RenderCopy(gRenderer, spriteText, &spriteRect, &destRect);
    SDL_RenderPresent(gRenderer);

}



