#include "dialogue.h"


void cadre(SDL_Window* gWindow, SDL_Renderer* gRenderer){
    // Récupération de l'écran, pour avoir les dimensions

    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    int w = gScreen->w;
    int h = gScreen->h;

    // Rectangle utilisable de la boîte de dialogue

    int box_h = (int)floor(0.25*h);
    int margin = (int)floor(0.02*h);

    SDL_Rect rect;
    rect.x = 1 + margin;
    rect.y = h-box_h + 1 + margin;
    rect.h = box_h-2 - 2*margin;
    rect.w = w-2 - 2*margin;

    // ----------- Partie cadre --------------

    // Zone de cadre
    SDL_Rect rectport;
    rectport.x = rect.x;
    rectport.y = rect.y;
    rectport.h = rect.h;
    rectport.w = rect.h;

    // Récupération du cadre

    SDL_Surface* cSurface = NULL;
    cSurface = IMG_Load("img/assets/frame.png");
    if (cSurface == NULL){
        printf("[DEBUG] Echec de création de surface de cadre> %s", SDL_GetError());
    }

    // Création de la texture de portrait
    SDL_Texture* cTexture = NULL;
    cTexture = SDL_CreateTextureFromSurface(gRenderer, cSurface);
    if (cTexture == NULL){
        printf("[DEBUG] Echec de création de texture de cadre > %s", SDL_GetError());
    }

    // Affichage du portrait 

    SDL_SetTextureBlendMode(cTexture, SDL_BLENDMODE_ADD);
    SDL_RenderCopy(gRenderer, cTexture, NULL, &rectport);

    SDL_RenderPresent(gRenderer);

    SDL_FreeSurface(gScreen);
    SDL_DestroyTexture(cTexture);
    SDL_FreeSurface(cSurface);
    




}

void dialogue(char* name, char* expression, char* texte, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font){

    // Récupération de l'écran, pour avoir les dimensions

    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    int w = gScreen->w;
    int h = gScreen->h;

    // Rectangle utilisable de la boîte de dialogue

    int box_h = (int)floor(0.25*h);
    int margin = (int)floor(0.02*h);

    SDL_Rect rect;
    rect.x = 1 + margin;
    rect.y = h-box_h + 1 + margin;
    rect.h = box_h-2 - 2*margin;
    rect.w = w-2 - 2*margin;

    // ----------- Partie portrait --------------

    // Zone de portrait
    SDL_Rect rectport;
    rectport.x = rect.x+4;
    rectport.y = rect.y-1;
    rectport.h = rect.h-4;
    rectport.w = rect.h-8;

    // Récupération du nom du portrait


    char* portrait_link = NULL;

    if  (strcmp(name,"Kiki")==0){
        if (strcmp(expression,"base")==0){
            portrait_link = "img/portraits/Kiki_base.png";
        }
        if (strcmp(expression,"angy")==0){
            portrait_link = "img/portraits/Kiki_angy.png";
        }
        if (strcmp(expression,"sed")==0){
            portrait_link = "img/portraits/Kiki_sed.png";
        }
    }
    if  (strcmp(name,"Tutoriel")==0){
        if (strcmp(expression,"base")==0){
            portrait_link = "img/portraits/Tutoriel_base.png";
        }
        if (strcmp(expression,"sed")==0){
            portrait_link = "img/portraits/Tutoriel_sed.png";
        }
        if (strcmp(expression,"uwu")==0){
            portrait_link = "img/portraits/Tutoriel_uwu.png";
        }
    }



    // Récupération du portrait
    SDL_Surface* pSurface = NULL;
    pSurface = IMG_Load(portrait_link);
    if (pSurface == NULL){
        printf("[DEBUG] Echec de création de surface de portrait > %s\n", SDL_GetError());
    }

    // Création de la texture de portrait
    SDL_Texture* pTexture = NULL;
    pTexture = SDL_CreateTextureFromSurface(gRenderer, pSurface);
    if (pTexture == NULL){
        printf("[DEBUG] Echec de création de texture de portrait > %s\n", SDL_GetError());
    }

    // Affichage du portrait 

    SDL_SetTextureBlendMode(pTexture, SDL_BLENDMODE_ADD);
    SDL_RenderCopy(gRenderer, pTexture, NULL, &rectport);


    
    // ----------- Partie texte -----------------

    // Zone de texte disponible
    SDL_Rect rectext;
    rectext.x = rect.x + margin + rectport.w;
    rectext.y = rect.y;
    rectext.h = rect.h;
    rectext.w = rect.w - rectport.w - margin;

    // Adaptation de la taille du texte en fonction de la taille de fenêtre
    TTF_SetFontSize(font,rect.h*0.25);
    
    // Couleur de texte
    SDL_Color textColor = {255, 255, 255, 255};

    // Création de la surface texte
    SDL_Surface* tSurface = NULL;

    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, texte, textColor,rectext.w);
    if (tSurface == NULL){
        printf("[DEBUG] Echec de création de surface de texte > %s\n", TTF_GetError());
    }

    // Création de la texture à partir du texte
    SDL_Texture* tTexture = NULL;
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);
    if (tTexture == NULL){
        printf("[DEBUG] Echec de création de texture de texte > %s", SDL_GetError());
    }

    
    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_ADD);

    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    SDL_Rect dstrect;
    dstrect.x = rectext.x;
    dstrect.y = rectext.y;
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    /*
    
    // Récupération du nom du se

    char* begin_link2 = "audio/SE/";
    char* end_link2 = "_dialogue.ogg";
    size_t numchar2 = strlen(begin_link2) + strlen(name) + strlen(end_link2);
    char* se_link = NULL;
    se_link = (char*) calloc(numchar2,sizeof(char));
    
    i = 0;
    j = 0;
    for (j=0;j<strlen(begin_link2);j++){
        se_link[i] = begin_link2[j];
        i++;
    }
    for (j=0;j<strlen(name);j++){
        se_link[i] = name[j];
        i++;
    }
    for (j=0;j<strlen(end_link2);j++){
        se_link[i] = end_link2[j];
        i++;
    }

    // Récupération du son
    Mix_Chunk* se = NULL;
    se = Mix_LoadWAV(se_link);
    if (se == NULL){
        printf("[DEBUG] Echec de création de load du sound effect > %s\n", Mix_GetError());
    }

    // Joue le son
    Mix_PlayChannel( -1, se, 0 );
    
    // Libère tout
    Mix_FreeChunk(se);
    se = NULL;
    free(se_link);
    se_link = NULL;
    
    
    */


    // Libère tout

    SDL_FreeSurface(pSurface);
    SDL_DestroyTexture(pTexture);
    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    SDL_FreeSurface(gScreen);


    return ;
}

void dialogue_prog(char* name, char* expression, char* texte, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font){

    // Récupération de l'écran, pour avoir les dimensions

    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    int w = gScreen->w;
    int h = gScreen->h;

    // Rectangle utilisable de la boîte de dialogue

    int box_h = (int)floor(0.25*h);
    int margin = (int)floor(0.02*h);

    SDL_Rect rect;
    rect.x = 1 + margin;
    rect.y = h-box_h + 1 + margin;
    rect.h = box_h-2 - 2*margin;
    rect.w = w-2 - 2*margin;

    // ----------- Partie portrait --------------

    // Zone de portrait
    SDL_Rect rectport;
    rectport.x = rect.x+4;
    rectport.y = rect.y-1;
    rectport.h = rect.h-4;
    rectport.w = rect.h-8;

    // Récupération du nom du portrait

    char* portrait_link = NULL;

    if  (strcmp(name,"Kiki")==0){
        if (strcmp(expression,"base")==0){
            portrait_link = "img/portraits/Kiki_base.png";
        }
        if (strcmp(expression,"angy")==0){
            portrait_link = "img/portraits/Kiki_angy.png";
        }
        if (strcmp(expression,"sed")==0){
            portrait_link = "img/portraits/Kiki_sed.png";
        }
    }
    if  (strcmp(name,"Tutoriel")==0){
        if (strcmp(expression,"base")==0){
            portrait_link = "img/portraits/Tutoriel_base.png";
        }
        if (strcmp(expression,"sed")==0){
            portrait_link = "img/portraits/Tutoriel_sed.png";
        }
        if (strcmp(expression,"uwu")==0){
            portrait_link = "img/portraits/Tutoriel_uwu.png";
        }
    }


    // Récupération du portrait
    SDL_Surface* pSurface = NULL;
    pSurface = IMG_Load(portrait_link);
    if (pSurface == NULL){
        printf("[DEBUG] Echec de création de surface de portrait > %s\n", SDL_GetError());
    }

    // Création de la texture de portrait
    SDL_Texture* pTexture = NULL;
    pTexture = SDL_CreateTextureFromSurface(gRenderer, pSurface);
    if (pTexture == NULL){
        printf("[DEBUG] Echec de création de texture de portrait > %s\n", SDL_GetError());
    }

    // Affichage du portrait 

    SDL_SetTextureBlendMode(pTexture, SDL_BLENDMODE_ADD);
    SDL_RenderCopy(gRenderer, pTexture, NULL, &rectport);


    
    // ----------- Partie texte -----------------

    // Zone de texte disponible
    SDL_Rect rectext;
    rectext.x = rect.x + margin + rectport.w;
    rectext.y = rect.y;
    rectext.h = rect.h;
    rectext.w = rect.w - rectport.w - margin;

    // Adaptation de la taille du texte en fonction de la taille de fenêtre
    TTF_SetFontSize(font,rect.h*0.15);
    
    // Couleur de texte
    SDL_Color textColor = {255, 255, 255, 255};

    // Création de la surface texte
    SDL_Surface* tSurface = NULL;

    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, texte, textColor,rectext.w);
    if (tSurface == NULL){
        printf("[DEBUG] Echec de création de surface de texte > %s\n", TTF_GetError());
    }

    // Création de la texture à partir du texte
    SDL_Texture* tTexture = NULL;
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);
    if (tTexture == NULL){
        printf("[DEBUG] Echec de création de texture de texte > %s", SDL_GetError());
    }

    
    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_ADD);

    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    SDL_Rect dstrect;
    dstrect.x = rectext.x;
    dstrect.y = rectext.y;
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    /*
    
    // Récupération du nom du se

    char* begin_link2 = "audio/SE/";
    char* end_link2 = "_dialogue.ogg";
    size_t numchar2 = strlen(begin_link2) + strlen(name) + strlen(end_link2);
    char* se_link = NULL;
    se_link = (char*) calloc(numchar2,sizeof(char));
    
    i = 0;
    j = 0;
    for (j=0;j<strlen(begin_link2);j++){
        se_link[i] = begin_link2[j];
        i++;
    }
    for (j=0;j<strlen(name);j++){
        se_link[i] = name[j];
        i++;
    }
    for (j=0;j<strlen(end_link2);j++){
        se_link[i] = end_link2[j];
        i++;
    }

    // Récupération du son
    Mix_Chunk* se = NULL;
    se = Mix_LoadWAV(se_link);
    if (se == NULL){
        printf("[DEBUG] Echec de création de load du sound effect > %s\n", Mix_GetError());
    }

    // Joue le son
    Mix_PlayChannel( -1, se, 0 );
    
    // Libère tout
    Mix_FreeChunk(se);
    se = NULL;
    free(se_link);
    se_link = NULL;
    
    
    */


    // Libère tout

    SDL_FreeSurface(pSurface);
    SDL_DestroyTexture(pTexture);
    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    SDL_FreeSurface(gScreen);


    return ;
}

void narration(char* texte, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font){

    

    // Récupération de l'écran, pour avoir les dimensions

    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    int w = gScreen->w;
    int h = gScreen->h;

    // Rectangle utilisable de la boîte de dialogue

    int box_h = (int)floor(0.25*h);
    int margin = (int)floor(0.02*h);

    SDL_Rect rect;
    rect.x = 1 + margin;
    rect.y = h-box_h + 1 + margin;
    rect.h = box_h-2 - 2*margin;
    rect.w = w-2 - 2*margin;

    // Adaptation de la taille du texte en fonction de la taille de fenêtre
    TTF_SetFontSize(font,rect.h*0.25);
    
    // Couleur de texte
    SDL_Color textColor = {255, 255, 255, 255};

    // Création de la surface texte
    SDL_Surface* tSurface = NULL;

    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, texte, textColor,rect.w);
    if (tSurface == NULL){
        printf("[DEBUG] Echec de création de surface de texte > %s\n", TTF_GetError());
    }

    // Création de la texture à partir du texte
    SDL_Texture* tTexture = NULL;
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);
    if (tTexture == NULL){
        printf("[DEBUG] Echec de création de texture de texte > %s", SDL_GetError());
    }

    
    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_ADD);

    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    SDL_Rect dstrect;
    dstrect.x = rect.x;
    dstrect.y = rect.y;
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);


    // Libère tout
    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    SDL_FreeSurface(gScreen);


    return ;
}

void narration_prog(char* texte, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font){

    

    // Récupération de l'écran, pour avoir les dimensions

    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    int w = gScreen->w;
    int h = gScreen->h;

    // Rectangle utilisable de la boîte de dialogue

    int box_h = (int)floor(0.25*h);
    int margin = (int)floor(0.02*h);

    SDL_Rect rect;
    rect.x = 1 + margin;
    rect.y = h-box_h + 1 + margin;
    rect.h = box_h-2 - 2*margin;
    rect.w = w-2 - 2*margin;

    // Adaptation de la taille du texte en fonction de la taille de fenêtre
    TTF_SetFontSize(font,rect.h*0.15);
    
    // Couleur de texte
    SDL_Color textColor = {255, 255, 255, 255};

    // Création de la surface texte
    SDL_Surface* tSurface = NULL;

    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, texte, textColor,rect.w);
    if (tSurface == NULL){
        printf("[DEBUG] Echec de création de surface de texte > %s\n", TTF_GetError());
    }

    // Création de la texture à partir du texte
    SDL_Texture* tTexture = NULL;
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);
    if (tTexture == NULL){
        printf("[DEBUG] Echec de création de texture de texte > %s", SDL_GetError());
    }

    
    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_ADD);

    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    SDL_Rect dstrect;
    dstrect.x = rect.x;
    dstrect.y = rect.y;
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);


    // Libère tout
    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    SDL_FreeSurface(gScreen);


    return ;
}
