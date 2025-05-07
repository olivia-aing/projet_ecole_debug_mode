#include "startMenu.h"


//////////////////////////////////////////////////////////// Font, Image, BG

// TTF_Font* setFont(void) {
//     TTF_Font* font = TTF_OpenFont("arial.ttf", 24); 
//     if (!font) {
//         printf("Failed to load font: %s\n", TTF_GetError());
//     }
//     return font ;
// }

SDL_Texture* loadImage(const char path[], SDL_Renderer *renderer) {
    SDL_Surface* tmp = NULL; 
    SDL_Texture* texture = NULL;
    tmp = IMG_Load(path);
    if(NULL == tmp) {
        fprintf(stderr, "Erreur SDL_IMG_Load : %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
        return NULL;
    }
    return texture;
}

void renderStartBG(SDL_Renderer *renderer, SDL_Texture* TextureBG, int step) {
    SDL_RenderClear(renderer) ; 
    int BGfullW, BGfullH ;
    if (SDL_QueryTexture(TextureBG, NULL, NULL, &BGfullW, &BGfullH)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in query texture: %s\n", SDL_GetError());
        exit(-1);
    }
    int BGw = BGfullW/2 ;
    int BGh = BGfullH/3 ;
    SDL_Rect BGrect = {.x = step%2*BGw, .y = (step/2)*BGh, .w = BGw, .h = BGh}; // printf("x = %d ; y = %d \n", BGrect.x, BGrect.y);
    if (SDL_RenderCopy(renderer, TextureBG, &BGrect, NULL)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in render copy: %s\n", SDL_GetError());
    }
}


//////////////////////////////////////////////////////////// Rectangles et clicks


void defRect (SDL_Rect* Rect1, SDL_Rect* Rect2, SDL_Rect* optionsMenu, SDL_Rect* back, SDL_Rect* save0, SDL_Rect* save1, int w, int h) {
    Rect1->x = w/3 ; Rect1->y = h/2 ;
    Rect1->w = w/3 ; Rect1->h = h/8 ;

    Rect2->x = w/3 ; Rect2->y = h/2 + h/5 ;
    Rect2->w = w/3 ; Rect2->h = h/8 ;
    
    optionsMenu->x = h/10 ; optionsMenu->y = h - w/6 ;
    optionsMenu->w = w/10 ; optionsMenu->h = w/10 ;

    back->x = w/20 ; back->y = h/20 ;
    back->w = w/10 ; back->h = h/9 ;

    save0->x = w/2 ; save0->y = h/4 ;
    save0->w = h/8 ; save0->h = h/8 ;
    save1->x = w/1.6 ; save1->y = h/4 ;
    save1->w = h/8   ; save1->h = h/8 ;
}

void checkClick (SDL_Event event, Save* sauvegarde, int* step, SDL_Rect* Rect1, SDL_Rect* Rect2, SDL_Rect* options, SDL_Rect* back, SDL_Rect* save0, SDL_Rect* save1) {
    // step : 
    // 0 : écran début              // 1 : choix de sauvegarde
    // 2 : lancement nouveau jeu    // 3 : lancement jeu sauvegardé
    // 4 : menu d'options           // 5 : crédits

    int mouseX = event.button.x ; int mouseY = event.button.y;
    if (*step==0) { // depuis le menu start
        if (mouseX > Rect1->x && mouseX < Rect1->x + Rect1->w && mouseY > Rect1->y && mouseY < Rect1->y + Rect1->h) { 
            *step = 2 ;     // lance un nouveau jeu
        } else if (mouseX > Rect2->x && mouseX < Rect2->x + Rect2->w  && mouseY > Rect2->y && mouseY < Rect2->y + Rect2->h) { 
            *step = 1 ;     // va au choix de sauvegarde
        } else if (mouseX > options->x && mouseX < options->x + options->w  && mouseY > options->y && mouseY < options->y + options->h) { 
            *step = 4 ;     // va au menu options
        }     
    }

    else if (*step==1) { // depuis le choix de sauvegarde
        if (mouseX > Rect1->x && mouseX < Rect1->x + Rect1->w && mouseY > Rect1->y && mouseY < Rect1->y + Rect1->h) { 
            bool vide = loadGame(sauvegarde, 0); // charge la sauvegarde 0
            if (vide) // si sauvegarde 0 vide -> lance nouveau jeu
                *step=2 ; 
            else 
                *step = 3 ;      // lance la sauvegarde 
        } else if (mouseX > Rect2->x && mouseX < Rect2->x + Rect2->w  && mouseY > Rect2->y && mouseY < Rect2->y + Rect2->h) { 
            bool vide = loadGame(sauvegarde, 1); // charge la sauvegarde 1
            if (vide) { // si sauvegarde 1 vide -> nouveau jeu
                *step=2 ; // lance un nouveau jeu
            }
            else {
                *step = 3 ;  // lance la sauvegarde 
            }
        } else if (mouseX > back->x && mouseX < back->x + back->w  && mouseY > back->y && mouseY < back->y + back->h) { 
            *step = 0 ;     // retourne au menu start 
        }     
    }

    else if (*step==4) { // depuis les options
        if (mouseX > back->x && mouseX < back->x + back->w  && mouseY > back->y && mouseY < back->y + back->h) {
            *step = 0 ; // retour accueil
        } else if (mouseX > save0->x && mouseX < save0->x + save0->w  && mouseY > save0->y && mouseY < save0->y + save0->h) {
            sauvegarde->num = 0 ; // sauvegarde par défaut dans sauvegarde0.txt
        } else if (mouseX > save1->x && mouseX < save1->x + save1->w  && mouseY > save1->y && mouseY < save1->y + save1->h) {
            sauvegarde->num = 1 ; // sauvegarde par défaut dans sauvegarde1.txt
        } else if (mouseX > Rect2->x && mouseX < Rect2->x + Rect2->w  && mouseY > Rect2->y && mouseY < Rect2->y + Rect2->h) {
            *step = 5 ; // va aux crédits
        }
    } 
    
    else if (*step==5) { // depuis les crédits
        if (mouseX > back->x && mouseX < back->x + back->w  && mouseY > back->y && mouseY < back->y + back->h) {
            *step = 4 ; // retour aux options
        }
    }
}


//////////////////////////////////////////////////////////// Fonction principale


int startMenu(SDL_Window** window, SDL_Renderer** renderer, Save* sauvegarde) { // retourne la valeur de quitStart dans le main 
    // printf("\n");
    // SDL_Texture* backgroundTexture = NULL ;
    SDL_Rect Rect1, Rect2, optionsMenu, back, save0, save1 ;
    // TTF_Font* font = NULL;
    SDL_Event event ;
    Mix_Music* music = NULL ;
    bool quitStart = 0 ; 
    int quitGame = 0 ;
    int startStep = 0 ; // indique dans quelle étape / menu du start on est : 

    int w, h; 
    SDL_GetWindowSize(*window, &w, &h); // changes Width & Height accordingly to the window size
    SDL_Texture* TextureBG = loadImage("./img/backgrounds/startBackgrounds.png", *renderer) ;
    defRect(&Rect1, &Rect2, &optionsMenu, &back, &save0, &save1, w, h) ; // definit les positions & tailles des 2 rectangles

    music = loadBGmusic("main_menu") ; // si pb -> quitStart = 1 & var music modifiée

    while (quitStart != 1) { 
        renderStartBG(*renderer, TextureBG, startStep) ;
        if (Mix_PlayingMusic()==0) { 
            Mix_PlayMusic(music, 0);
        }
        SDL_RenderPresent(*renderer); 
        if (startStep==3 || startStep==2) { // nouveau jeu ou sauvegarde -> sort du menu pour lancer le jeu
            SDL_Delay(700); // 0.7 sec
            quitStart = 1;
            break;
        }
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    // printf("quits idk how\n");
                    quitStart = 1;
                    quitGame = 1 ;
                    break;
                case SDL_KEYDOWN :
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        // printf("quits by ESC key\n");
                        quitStart = 1;
                        quitGame = 1 ;
                    }
                    break ;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        checkClick(event, sauvegarde, &startStep, &Rect1, &Rect2, &optionsMenu, &back, &save0, &save1) ;
                    }
                    break ;
            }
        }
    }
    if(NULL != TextureBG)
        SDL_DestroyTexture(TextureBG);
    Mix_HaltMusic() ;
    return quitGame ;
    // return 0;   
}


//////////////////////////////////////////////////////////// Quit


int Quit (SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, Mix_Music* music) {
    if(NULL != window)
        SDL_DestroyWindow(window) ;
    if(NULL != renderer) 
        SDL_DestroyRenderer(renderer);
    if (texture!=NULL)
        SDL_DestroyTexture(texture);
    if(NULL != music) 
        Mix_FreeMusic(music);
    
    SDL_Quit() ;
    IMG_Quit() ;
    Mix_CloseAudio() ; // quit SDL_mixer 

    return 0 ;
}

