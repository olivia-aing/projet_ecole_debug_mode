# include "story_event.h"

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------
// ---------------------EVENEMENTS GENERAUX--------------------------------------------
// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------

int call_event(int variable_histoire, int** carte, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events2, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText){
    int vh = variable_histoire;
    SDL_Event events;
    switch(vh)
        {
            /*case -1 :
                vh = event_test(vh, gWindow, gRenderer, events, font);
                break;
            */

            // Introduction, cutscene, déplacement (story_progress = 0)
            case 0 :
                vh = intro_cutscene(carte, gWindow, gRenderer, events, font, spriteRect, destRect, spriteText);
                //vh = prologue(carte, gWindow,gRenderer,events,font,spriteRect,destRect,spriteText);
                break;
            
            // Présentation du terminal (story_progress = 1 || story_progress = 2)
            case 1 : case 2 :
                vh = ep12(vh,carte,gWindow,gRenderer,events,font,fontProg, spriteRect, destRect, spriteText);
                break;

            // Accès au debug_mode, carte de Zoé (story_progress = 3 || story_progress = 4)
            case 3 : case 4 :
                vh = ep34(vh,carte,gWindow,gRenderer,events,font,fontProg, spriteRect, destRect, spriteText);
                break;

            // Spirale (story_progress = 5 || story_progress = 6)
            case 5 : case 6 :
                vh = ep56(vh,carte,gWindow,gRenderer,events,font,fontProg, spriteRect, destRect, spriteText);
                break;

            // Post spirale, rouge (story_progress = 7 || story_progress = 8)
            case 7 : case 8 :
                vh = ep78(vh,carte,gWindow,gRenderer,events,font,fontProg, spriteRect, destRect, spriteText);
                break;

            // Carte noire de fin (story_progress = 9 || story_progress = 10)
            case 9 : case 10 :
                vh = ep910(vh,carte,gWindow,gRenderer,events,font,fontProg, spriteRect, destRect, spriteText);
                break;

            default :
                printf("Qu'est-ce que tu fais ici ? C'est en dehors de la démo !\n");
            break;
            
        }

    SDL_RenderClear(gRenderer);
    
    return vh;

}

int vh_increment(int variable_histoire, bool gentil){
    bool pair = (variable_histoire % 2 == 0);
    if (pair){
        if (gentil){
            return 2;
        }
        else{
            return 1;
        }
    }
    else{
        if (gentil){
            return 3;
        }
        else{
            return 2;
        }
    }


}

int skippeable(int skip, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font){

    char* skip_text; 

    if (skip == 50){
        return 50;
    }
    else{

        int nbskip = (int) floor(skip/5);
        switch (nbskip){

            case 1:
                skip_text = "Maintenir [ESPACE] pour sauter la cutscene -                             ";
            break;
            case 2:
                skip_text = "Maintenir [ESPACE] pour sauter la cutscene - -                           ";
            break;
            case 3:
                skip_text = "Maintenir [ESPACE] pour sauter la cutscene - - -                         ";
            break;
            case 4:
                skip_text = "Maintenir [ESPACE] pour sauter la cutscene - - - -                       ";
            break;
            case 5:
                skip_text = "Maintenir [ESPACE] pour sauter la cutscene - - - - -                     ";
            break;
            case 6:
                skip_text = "Maintenir [ESPACE] pour sauter la cutscene - - - - - -                   ";
            break;
            case 7:
                skip_text = "Maintenir [ESPACE] pour sauter la cutscene - - - - - - -                 ";
            break;
            case 8:
                skip_text = "Maintenir [ESPACE] pour sauter la cutscene - - - - - - - -               ";
            break;
            case 9:
                skip_text = "Maintenir [ESPACE] pour sauter la cutscene - - - - - - - - -             ";
            break;
            case 10:
                skip_text = "Maintenir [ESPACE] pour sauter la cutscene - - - - - - - - - -           ";
            break;

            default:
                skip_text = "Maintenir [ESPACE] pour sauter la cutscene                               ";
            break;
        }

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

        tSurface = TTF_RenderUTF8_Solid(font, skip_text, textColor);
        if (tSurface == NULL){
            printf("[DEBUG] Echec de création de surface de texte > %s\n", TTF_GetError());
        }

        // Création de la texture à partir du texte
        SDL_Texture* tTexture = NULL;
        tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);
        if (tTexture == NULL){
            printf("[DEBUG] Echec de création de texture de texte > %s", SDL_GetError());
        }

        
        SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);

        int textW = 0;
        int textH = 0;
        SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);

        // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

        SDL_Rect dstrect;
        dstrect.x = margin;
        dstrect.y = margin;
        dstrect.w = textW;
        dstrect.h = textH;

        SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

        SDL_RenderPresent(gRenderer);

        SDL_FreeSurface(tSurface);
        SDL_DestroyTexture(tTexture);
        SDL_FreeSurface(gScreen);

        return skip+1;


    }
}

void remise_surface(int variable_histoire, bool frame, int** carte, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText, SDL_Window* gWindow, SDL_Renderer* gRenderer){
    
    SDL_RenderClear(gRenderer);
    
    // Récupération de l'écran et de sa taille
    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    int w = gScreen->w;
    int h = gScreen->h;

    int box_h = (int)floor(0.25*h);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = h-box_h;
    rect.h = box_h;
    rect.w = w;
    
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(gRenderer, &rect);
    SDL_RenderPresent(gRenderer);

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

    if (variable_histoire > BLEU && variable_histoire < 9){
        dialogue_box_colour(gWindow,gRenderer);
    }
    else{
        dialogue_box_nb(gWindow,gRenderer);
    }
    if (frame){
        cadre(gWindow,gRenderer);
    }

    SDL_FreeSurface(gScreen);

    return;
}

void entrer(SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font){

    char* skip_text; 
    skip_text ="Appuyer sur [ ENTREE ] pour continuer";

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

        tSurface = TTF_RenderUTF8_Solid(font, skip_text, textColor);
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
        dstrect.x = margin;
        dstrect.y = margin;
        dstrect.w = textW;
        dstrect.h = textH;

        SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

        SDL_RenderPresent(gRenderer);

        SDL_FreeSurface(tSurface);
        SDL_DestroyTexture(tTexture);
        SDL_FreeSurface(gScreen);

        return ;

}

// Bonjour monsieur l'événement test

int event_test(int variable_histoire, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font){
    int vh = variable_histoire;
    int event_progress = 0;
    int skip = 0;
    bool event_pending = true;
    dialogue_box_nb(gWindow, gRenderer);
    cadre(gWindow, gRenderer);
    skippeable(skip, gWindow,  gRenderer, events, font);
    dialogue("Kiki", "base", "Il est grand temps d'essayer avec un texte un peu plus long.\n Comme celui-ci, par exemple.\n", gWindow, gRenderer, font);
    event_progress++;

    while (event_pending){
        while (SDL_PollEvent(&events))
            {
                switch (events.type)
                {
                    case SDL_KEYDOWN:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_RETURN:
                                    switch(event_progress)
                                        {
                                            case 1 :
                                                dialogue("Kiki", "base", "Et ça, c'est le second dialogue !\n\n\n\n", gWindow, gRenderer, font);
                                                event_progress++;
                                                break;
                                            case  2 :
                                                dialogue_box_nb(gWindow, gRenderer);
                                                narration("Et ça, c'est ce que ça donne sans portrait !\n\n\n",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;
                                            case 3 :
                                                event_progress++;
                                                vh++;
                                                event_pending = false;
                                                break;
                                        }
                            break;

                            case SDLK_SPACE:
                                if (skip == 50){
                                    printf("Cutscene skip\n");
                                    vh++;
                                    event_pending = false;
                                    
                                }
                                else{
                                    skip = skippeable(skip, gWindow, gRenderer, events, font);
                                }

                            
                            break;

                            }
                    break;

                    case SDL_KEYUP:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_SPACE:
                                skip = 0;
                                skippeable(skip, gWindow,  gRenderer, events, font);
                                break;
                            }
                        break;
                        
                    case SDL_QUIT:
                    /*Le cas où on appuie sur la croix, pour fermer la fenêtre*/
                        event_pending = false;
                        break;
                }
            }
    }

    //SDL_RenderClear(gRenderer);;

    //SDL_FreeSurface(box) // Il est free dans le box_destroy;
    return 0;

}

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------
// -------------------------EVENEMENTS INDIVIDUELS-------------------------------------
// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------

// [DONE] L'introduction de base, on fait tout apparaître
int intro_cutscene(int** carte,SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText){
    // L'écran noir de début
    SDL_RenderClear(gRenderer);

    // Ne pas oublier la variable histoire à renvoyer à la fin
    int vh;
    int i; // j'en aurai besoin

    // Fixer les paramètres de texte
    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow);
    int h = gScreen->h;
    int w = gScreen->w;

    int box_h = (int)floor(0.25*h);
    int margin = (int)floor(0.02*h);
    int fsize = box_h-2 - 2*margin;

    TTF_SetFontSize(font,fsize*0.25);

    // Couleur de texte
    SDL_Color textColor = {255, 255, 255, 255};

    // Création de la surface texte
    SDL_Surface* tSurface = NULL;

    // Création de la texture à partir du texte
    SDL_Texture* tTexture = NULL;

    // Commençons l'écriture
    
    char* message_lancement1 = "Launching \"Les Aventures de Kiki\"";

    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_lancement1, textColor,w);
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);

    int textW = 0;
    int textH = 0;

    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);
  

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    SDL_Rect dstrect;
    dstrect.x = margin;
    dstrect.y = margin;
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(750);


    // Premier .
    
    message_lancement1 = "Launching \"Les Aventures de Kiki\".";

    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    tSurface = NULL;
    tTexture = NULL;

    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_lancement1, textColor,w);
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);
    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)
    
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(750);

    // Deuxième .

    message_lancement1 = "Launching \"Les Aventures de Kiki\"..";

    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    tSurface = NULL;
    tTexture = NULL;

    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_lancement1, textColor,w);
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);
    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);
  

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(750);

    // Troisième .

    message_lancement1 = "Launching \"Les Aventures de Kiki\"...";

    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    tSurface = NULL;
    tTexture = NULL;

    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_lancement1, textColor,w);
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);
    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);
  

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(1000);

    // Début des "erreurs", yay !

    // Erreur 1

    char* message_erreur1 = "[ERROR] > Cannot open source file SDL2/SDL.h";

    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    tSurface = NULL;
    tTexture = NULL;

    int olH = textH;
    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_erreur1, textColor,w);
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);

    textW = 0;
    textH = 0;

    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);
  

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    dstrect.y = dstrect.y + olH + margin;
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(750);





    char* message_erreur2 = "[ERROR] > IMG_Load() NOT FOUND";

    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    tSurface = NULL;
    tTexture = NULL;

    olH = textH;
    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_erreur2, textColor,w);
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);

    textW = 0;
    textH = 0;

    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);
  

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    dstrect.y = dstrect.y + olH + margin;
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(750);




    char* message_erreur3= "[ERROR] > SDL_Colors NOT DEFINED";

    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    tSurface = NULL;
    tTexture = NULL;

    olH = textH;
    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_erreur3, textColor,w);
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);

    textW = 0;
    textH = 0;

    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);
  

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    dstrect.y = dstrect.y + olH + margin;
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(750);



    char* message_erreur4= "[ERROR] > AddressSanitizer: SEGV on unknown address";

    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    tSurface = NULL;
    tTexture = NULL;

    olH = textH;
    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_erreur4, textColor,w);
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);

    textW = 0;
    textH = 0;

    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);
  

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    dstrect.y = dstrect.y + olH + margin;
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(100);

    char* message_erreur5= "HINT: this fault was caused by a dereference of a high value address";

    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    tSurface = NULL;
    tTexture = NULL;

    olH = textH;
    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_erreur5, textColor,w);
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);

    textW = 0;
    textH = 0;

    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);
  

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    dstrect.y = dstrect.y + olH + margin;
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(100);

    char* message_erreur6= "Dissassemble the provided PC to learn which register was used.";

    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    tSurface = NULL;
    tTexture = NULL;

    olH = textH;
    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_erreur6, textColor,w);
    tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

    SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);

    textW = 0;
    textH = 0;

    SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);
  

    // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

    dstrect.y = dstrect.y + olH + margin;
    dstrect.w = textW;
    dstrect.h = textH;

    SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(1000);


    char* message_erreur_last = "AdressSanitizer:DEADLYSIGNAL";

    for (i=0;i<10;i++){
        olH = textH;

        SDL_FreeSurface(tSurface);
        SDL_DestroyTexture(tTexture);
        tSurface = NULL;
        tTexture = NULL;
        tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_erreur_last, textColor,w);
        tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

        SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);

        textW = 0;
        textH = 0;

        SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);
    

        // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)

        dstrect.y = dstrect.y + olH + margin;
        dstrect.w = textW;
        dstrect.h = textH;

        SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

        SDL_RenderPresent(gRenderer);

        SDL_Delay(300);
    }

    SDL_RenderClear(gRenderer);

    char* message_lancement_end = "Launching \"debug_mode\"";
    char* message_lancement2;

    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    tSurface = NULL;
    tTexture = NULL;

    // C'est parti

    for(i=0;i<strlen(message_lancement_end)+3;i++){

        switch (i)
        {
            case 0:
                message_lancement2 = "L";
            break;
            case 1:
                message_lancement2 = "La";
            break;
            case 2:
                message_lancement2 = "Lau";
            break;
            case 3:
                message_lancement2 = "Laun";
            break;
            case 4:
                message_lancement2 = "Launc";
            break;
            case 5:
                message_lancement2 = "Launch";
            break;
            case 6:
                message_lancement2 = "Launchi";
            break;
            case 7:
                message_lancement2 = "Launchin";
            break;
            case 8:
                message_lancement2 = "Launching";
            break;
            case 9:
                message_lancement2 = "Launching \"";
            break;
            case 10:
                message_lancement2 = "Launching \"d";
            break;
            case 11:
                message_lancement2 = "Launching \"de";
            break;
            case 12:
                message_lancement2 = "Launching \"deb";
            break;
            case 13:
                message_lancement2 = "Launching \"debu";
            break;
            case 14:
                message_lancement2 = "Launching \"debug";
            break;
            case 15:
                message_lancement2 = "Launching \"debug_";
            break;
            case 16:
                message_lancement2 = "Launching \"debug_m";
            break;
            case 17:
                message_lancement2 = "Launching \"debug_mo";
            break;
            case 18:
                message_lancement2 = "Launching \"debug_mod";
            break;
            case 19:
                message_lancement2 = "Launching \"debug_mode";
            break;
            case 20:
                message_lancement2 = "Launching \"debug_mode\"";
            break;
            case 21:
                message_lancement2 = "Launching \"debug_mode\".";
            break;
            case 22:
                message_lancement2 = "Launching \"debug_mode\"..";
            break;
            case 23:
                message_lancement2 = "Launching \"debug_mode\"...";
            break;
        }

        if (!(i < strlen(message_lancement_end))){
            SDL_Delay(400);
        }

        SDL_FreeSurface(tSurface);
        SDL_DestroyTexture(tTexture);
        tSurface = NULL;
        tTexture = NULL;    

        tSurface = TTF_RenderUTF8_Solid_Wrapped(font, message_lancement2, textColor,w);
        tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);

        SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);

        int textW = 0;
        int textH = 0;

        SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);
    

        // Zone de texte utilisée (pemet d'avoir du texte qui n'est pas stretch)
        dstrect.x = w/2 - textW/2;
        dstrect.y = h/2 - textH;
        dstrect.w = textW;
        dstrect.h = textH;

        SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

        SDL_RenderPresent(gRenderer);

        SDL_Delay(100);

    }

    SDL_Delay(500);

    SDL_RenderClear(gRenderer);
    SDL_RenderPresent(gRenderer);

    SDL_Delay(1000);
    

    vh = prologue(carte, gWindow, gRenderer, events, font,spriteRect,destRect,spriteText);

    SDL_FreeSurface(gScreen);
    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);

    return vh;
}

// [DONE] Le prologue, on rencontre Kiki et Tutoriel
int prologue(int** carte, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText){
    int vh = 0;
    int event_progress = 0;
    int skip = 0;
    bool event_pending= true;

    

    // ajouter ici l'apparition de la situation de départ

    dialogue_box_nb(gWindow,gRenderer);
    remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
    entrer(gWindow,gRenderer,events,font);
    dialogue("Kiki","base","??? :\n... ?",gWindow,gRenderer,font);
    event_progress++;

    while (event_pending){
        while (SDL_PollEvent(&events))
            {
                switch (events.type)
                {
                    case SDL_KEYDOWN:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_RETURN:
                                    switch(event_progress)
                                        {
                                            case 1 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Kiki","base","??? :\nQuel est cet endroit ?",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 2 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Kiki","base","??? :\nIl y a quelqu'un ?",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 3 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Kiki","sed","??? :\n...",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 4 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Kiki","sed","??? :\nEssayons de trouver quelqu'un...",gWindow,gRenderer,font);
                                                SDL_Delay(200);
                                                // Il se peut que j'aie oublié de prendre en compte le changement de portrait lol
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel","base","??? :\nBonjour Kiki !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 5 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki","base","??? :\n... ?",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 6 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel","base","??? :\nOui, c'est à toi que je parle ! Kiki ! L'araignée !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;
                                            
                                            case 7 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki","base","Kiki :\nTu... me connais ?",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;
                                            
                                            case 8 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel","base","??? :\nAbsolument pas !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 9 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel","base","??? :\nJ'ai juste lu ton nom dans les fichiers de concept !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 10 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki","base","Kiki :\nLes fichiers de concept... ?",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 11 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel","base","??? :\nNe t'en fais pas, ça ne te concerne pas. Enfin, si, mais tu n'as pas besoin de savoir !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 12 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel","base","Tutoriel :\nJe suis Tutoriel, enchanté de faire ta connaissance !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 13 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel","base","Tutoriel :\nJe suis là pour t'apprendre à jouer au jeu !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 14 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki","base","Kiki :\nAu jeu... ?",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 15 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel","base","Tutoriel :\nOui ! Enfin, ce qu'il en reste...",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 16 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel","base","Tutoriel :\nEnfin bref ! Prête à apprendre comment jouer au jeu ?",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 17 :
                                                remise_surface(vh, false, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                narration("A. \"Apprends-moi !\"\nB. Ignorer Tutoriel et continuer.",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 18 :
                                                // On attend A ou B, c'est le choix
                                                break;

                                            case 19 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel","sed","Tutoriel :\nEh, mais attends !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 20 :
                                                remise_surface(vh, false, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                narration("Tutoriel vous regarde d'un air peiné.",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 21 :
                                                vh += vh_increment(vh,false);
                                                event_progress++;
                                                event_pending = false;
                                                break;

                                            case 22 :
                                                // On s'assure qu'il ne se passe rien post fin du méchant choix
                                                break;

                                            case 23 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel","base","Tutoriel :\nAttends, quoi ?",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 24 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel","base","Tutoriel :\nTu veux que je...",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 25 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel","uwu","Tutoriel :\nT'APPRENNE ?",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 26 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel","uwu","Tutoriel :\nC'est le plus beau jour de ma vie, je ne me suis pas fait skip !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 27 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel","base","Tutoriel :\nLa base du jeu, ce sera le déplacement !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 28 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel","base","Tutoriel :\nPour te déplacer, tu peux utiliser les touches ZQSD sur un clavier [AZERTY], ou WASD sur un clavier [QWERTY] !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 29 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel","base","Tutoriel :\nBien sûr, si tu as du mal, tu peux toujours utiliser les flèches directionnelles !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 30 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Kiki","base","Kiki :\nClavier... ?",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 31 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel","base","Tutoriel :\nNe t'en fais pas, c'est un de mes amis Kiki !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 32 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel","base","Tutoriel :\nSur ce, je vais t'attendre dans la salle suivante ! A tout de suite !",gWindow,gRenderer,font);
                                                event_progress++;
                                                break;

                                            case 33 :
                                                vh += vh_increment(vh,true);
                                                event_progress++;
                                                event_pending = false;
                                                break;

                                            case 34 :
                                                // On s'assure qu'il ne se passe rien post fin du gentil choix
                                                break;

                                            

                                        }
                            break;

                            case SDLK_a:
                                if (event_progress==18)
                                {
                                    remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                    dialogue("Tutoriel","base","Tutoriel :\nJe sais que tu vas vouloir m'ignorer et...",gWindow,gRenderer,font);
                                    event_progress = 23;
                                }

                            break;

                            case SDLK_b:
                                if (event_progress==18)
                                {
                                    remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                    dialogue("Tutoriel","base","Tutoriel :\nJe sais que tu vas vouloir m'ignorer et...",gWindow,gRenderer,font);
                                    event_progress = 19;
                                }
                            break;
                                

                            case SDLK_SPACE:
                                if (skip == 50){
                                    vh = vh_increment(vh, false);
                                    event_pending = false;
                                    skip++;
                                    
                                }
                                else{ if (skip<50){
                                        skip = skippeable(skip, gWindow, gRenderer, events, font);
                                    }
                                }
                                    
                                

                            
                            break;

                            default:
                                //no queues plz
                            break;

                            }
                    break;

                    case SDL_KEYUP:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_SPACE:
                                if (skip<50){
                                    skip = 0;
                                    skippeable(skip, gWindow,  gRenderer, events, font);
                                }
                                break;

                            default:
                                //no queues plz
                            break;
                            
                            }
                    break;

                    case SDL_QUIT:
                    //Le cas où on appuie sur la croix, pour fermer la fenêtre
                        event_pending = false;
                        break;
                }
            }
    }

    SDL_RenderClear(gRenderer);

    //SDL_FreeSurface(box) // Il est free dans le box_destroy;
    return vh;
}

// [DONE] Tutoriel explique le terminal (carte 0)
int ep12(int variable_histoire, int** carte,SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText){
    int vh = variable_histoire;
    int event_progress = 0;
    int skip = 0;
    bool event_pending = true;

    

    

    dialogue_box_nb(gWindow, gRenderer);
    cadre(gWindow, gRenderer);
    skippeable(skip, gWindow,  gRenderer, events, font);
    if (vh%2==1){
        dialogue("Tutoriel", "base", "Tutoriel :\nJe sais que tu ne veux pas me lire,  mais il faut que je te parle de quelque chose...", gWindow, gRenderer, font);
    }
    else{
        dialogue("Tutoriel", "base", "Tutoriel :\nAu fait, il faut que je te parle de quelque chose avant que je n'oublie !", gWindow, gRenderer, font);
    }
    event_progress=3;

    while (event_pending){
        while (SDL_PollEvent(&events))
            {
                switch (events.type)
                {
                    case SDL_KEYDOWN:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_RETURN:
                                    switch(event_progress)
                                        {
                                            case 1 :
                                                vh += vh_increment(vh, false);
                                                event_pending = false;
                                                event_progress++;
                                            break;

                                            case 2 :
                                                // Bonjour, j'essaie de faire en sorte qu'il ne se passe pas des choses étranges
                                            break;

                                            case 3 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nPour commencer, tu peux appuyer sur [LEFT SHIFT] pour ouvrir un terminal!", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 4 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nVas-y, essaie ! Appuie sur [LEFT SHIFT] !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 5 :
                                                // Lui est vide, il est pour appuyer forcément sur X
                                            break;

                                            case 6 :
                                                dialogue_box_nb(gWindow,gRenderer);
                                                cadre(gWindow,gRenderer);
                                                dialogue_prog("Tutoriel", "base", "Tutoriel :\nJe vais te donner accès aux commandes de base, attends...", gWindow, gRenderer, fontProg);
                                                event_progress++;
                                            break;

                                            case 7 :
                                                SDL_RenderClear(gRenderer);
                                                terminal_box_nb(gWindow,gRenderer);
                                                dialogue_box_nb(gWindow,gRenderer);
                                                cadre(gWindow,gRenderer);
                                                dialogue_prog("Tutoriel", "base", "Tutoriel :\n...", gWindow, gRenderer, fontProg);
                                                SDL_Delay(500);
                                                affiche_commandes(vh, gWindow, gRenderer, fontProg);
                                                dialogue_box_nb(gWindow,gRenderer);
                                                cadre(gWindow,gRenderer);
                                                dialogue_prog("Tutoriel", "base", "Tutoriel :\n... Voilà ! Maintenant tu devrais pouvoir avoir accès à ces commandes !", gWindow, gRenderer, fontProg);
                                                event_progress++;
                                            break;

                                            case 8 :
                                                remise_surface(vh, true, carte, spriteRect, destRect,spriteText, gWindow,gRenderer);
                                                dialogue_prog("Tutoriel", "base", "Tutoriel :\nAu vu de l'état actuel des choses, je te conseillerais d'utiliser \\map !", gWindow, gRenderer, fontProg);
                                                event_progress++;
                                            break;

                                            case 9 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nÇa te permettra d'afficher à côté le chemin que tu dois suivre pour sortir de la salle !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 10 :
                                                remise_surface(vh, true, carte, spriteRect, destRect,spriteText, gWindow,gRenderer);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nSi jamais tu as la moindre question, ou le moindre souci, n'hésite pas à appuyer sur [T] pour me demander de l'aide !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 11 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nBon allez ! Sur ce, je vais t'attendre dans la salle suivante ! À tout de suite !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            // Closing case
                                            case 12 :
                                                event_progress++;
                                                vh += vh_increment(vh,true);
                                                event_pending = false;
                                                break;

                                            case 13 :
                                                // Nothing to see here
                                            break;
                                        }
                            break;

                            case SDLK_LSHIFT:
                                if (event_progress==4 || event_progress==5){
                                    SDL_RenderClear(gRenderer);
                                    terminal_box_nb(gWindow,gRenderer);
                                    SDL_Delay(500);
                                    dialogue_box_nb(gWindow,gRenderer); // Je comprends pas pourquoi il garde la barre ici, et uniquement ici, de manière aléatoire, et en mettre 2 ne règle rien
                                    cadre(gWindow,gRenderer);
                                    dialogue_prog("Tutoriel", "base", "Tutoriel :\nC'est comme ça que tu ouvres le terminal !", gWindow, gRenderer, fontProg);
                                    event_progress=6;
                                }

                            break;

                            case SDLK_SPACE:
                                if (skip == 50){
                                    remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                    dialogue("Tutoriel", "sed", "Tutoriel :\nTu peux appuyer sur T si jamais tu as besoin de mon aide...", gWindow, gRenderer, font);
                                    event_progress=1;
                                    skip++;
                                    
                                }
                                else{if (skip < 50){
                                    skip = skippeable(skip, gWindow, gRenderer, events, font);
                                    }
                                }

                            
                            break;

                            default:
                                //no queues plz
                            break;

                            }
                    break;

                    case SDL_KEYUP:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_SPACE:
                                if (skip<50){
                                    skip = 0;
                                    skippeable(skip, gWindow,  gRenderer, events, font);
                                }
                                break;
                            default:
                                //no queues plz
                            break;
                            }
                    break;
                        
                    case SDL_QUIT:
                    //Le cas où on appuie sur la croix, pour fermer la fenêtre
                        event_pending = false;
                        break;
                }
            }
    }

    SDL_RenderClear(gRenderer);

    //SDL_FreeSurface(box) // Il est free dans le box_destroy;
    return vh;
}

// [DONE] Tutoriel donne accès au debug_mode (carte 1, Zoé)
int ep34(int variable_histoire, int** carte,SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText){
    int vh = variable_histoire;
    int event_progress = 0;
    int skip = 0;
    bool event_pending = true;


    

    dialogue_box_nb(gWindow, gRenderer);
    cadre(gWindow, gRenderer);
    skippeable(skip, gWindow,  gRenderer, events, font);

    // La première ligne de dialogue peut toujours changer selon si le PJ a été gentil avec Tutoriel précédemment ou non
    if (vh%2==1){
        dialogue("Tutoriel", "base", "Tutoriel :\nTu en as mis du temps !", gWindow, gRenderer, font);
    }
    else{
        dialogue("Tutoriel", "base", "Tutoriel :\nRe-coucou Kiki ! Content de voir que tu t'en es sortie !", gWindow, gRenderer, font);
    }
    event_progress=1;

    while (event_pending){
        while (SDL_PollEvent(&events))
            {
                switch (events.type)
                {
                    case SDL_KEYDOWN:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_RETURN:
                                    switch(event_progress)
                                        {

                                            case 1 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "uwu", "Tutoriel :\nOh ! Tu as trouvé les murs !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 2 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "uwu", "Tutoriel :\nJe ne sais pas comment tu as fait, mais ça sera utile pour la suite !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 3 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nElle t'aidera à trouver le chemin vers la sortie ! (S'il y en a une)", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 4 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nDe mon côté, j'ai trouvé autre chose dont tu auras besoin !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 5 :
                                                remise_surface(vh, false, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                narration_prog("\\debug_mode débloqué !", gWindow, gRenderer, fontProg);
                                                event_progress++;
                                            break;

                                            case 6 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nC'est le debug_mode ! Le mode de jeu qui te permet de traverser certains murs !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 7 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "base", "Kiki :\nTraverser les murs ? Mais pourquoi... ?", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 8 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nTu vas très vite comprendre... Bon allez, je te retrouve bientôt !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            // Closing case
                                            case 9 :
                                                event_progress++;
                                                vh += vh_increment(vh,true);
                                                event_pending = false;
                                            break;

                                        }
                            break;

                            // Le skip général
                            case SDLK_SPACE:
                                if (skip == 50){
                                    vh += vh_increment(vh, false);
                                    event_pending = false;
                                    event_progress++;
                                    skip++;
                                    
                                }
                                else{if (skip < 50){
                                    skip = skippeable(skip, gWindow, gRenderer, events, font);
                                    }
                                }

                            
                            break;

                            default:
                                //no queues plz
                            break;

                            }
                    break;

                    case SDL_KEYUP:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_SPACE:
                                if (skip<50){
                                    skip = 0;
                                    skippeable(skip, gWindow,  gRenderer, events, font);
                                }
                                break;
                            default:
                                //no queues plz
                            break;
                            }
                    break;
                        
                    case SDL_QUIT:
                    //Le cas où on appuie sur la croix, pour fermer la fenêtre
                        event_pending = false;
                        break;
                }
            }
    }

    SDL_RenderClear(gRenderer);

    //SDL_FreeSurface(box) // Il est free dans le box_destroy;
    return vh;
}

// [DONE] Bleu A LA FIN, carte 2, spirale, pas debug_mode

int ep56(int variable_histoire, int** carte,SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText){
    int vh = variable_histoire;
    int event_progress = 0;
    int skip = 0;
    bool event_pending = true;

    

    dialogue_box_nb(gWindow, gRenderer);
    cadre(gWindow, gRenderer);
    skippeable(skip, gWindow,  gRenderer, events, font);

    // La première ligne de dialogue peut toujours changer selon si le PJ a été gentil avec Tutoriel précédemment ou non
    if (vh%2==1){
        dialogue("Tutoriel", "base", "Tutoriel :\nJ'ai un truc à te dire...", gWindow, gRenderer, font);
    }
    else{
        dialogue("Tutoriel", "sed", "Tutoriel :\nKiki, j'ai une mauvaise nouvelle !", gWindow, gRenderer, font);
    }
    event_progress=1;

    while (event_pending){
        while (SDL_PollEvent(&events))
            {
                switch (events.type)
                {
                    case SDL_KEYDOWN:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_RETURN:
                                    switch(event_progress)
                                        {

                                            case 1 :
                                            /*
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nMais déjà, bravo à toi pour avoir trouvé le rouge !\nTu as fait apparaître de nouveaux interrupteurs avec !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 2 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "sed", "Kiki :\nEt la mauvaise nouvelle ?", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 3 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "sed", "Tutoriel :\nJ'y viens...", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 4 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nTu te souviens des murs bizarres dont je t'ai parlé la dernière fois ?", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 5 :*/
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "sed", "Tutoriel :\nIl y a des murs qui sont infranchissables, peu importe ce que l'on fait !", gWindow, gRenderer, font);
                                                event_progress=6;
                                            break;

                                            case 6 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "angy", "Kiki :\nNe dis pas ça Tutoriel ! Je suis sûre qu'on peut arriver à les franchir !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 7 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nNon, non, je veux dire...", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 8 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "sed", "Tutoriel :\nIl y a des murs qui ne peuvent pas être traversés, même en debug mode !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 9 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "sed", "Tutoriel :\nTu as dû trouver des collisions qui ont un niveau de priorité plus élevé  ! Elles surpassent même le debug_mode auquel je peux te donner accès !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 10 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "base", "Kiki :\nMais c'est une bonne nouvelle alors, non ?", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 11 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "sed", "Tutoriel :\nComment ça... ?", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 12 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "base", "Kiki :\nÇa veut dire que notre monde est en train de se reconstruire comme il faut, non ?", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 13 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "base", "Kiki :\nOn avance pour réparer notre monde, et c'est une bonne nouvelle !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 14 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\n...", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 15 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "uwu", "Tutoriel :\nTu es vraiment incroyable, Kiki !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 16 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "uwu", "Tutoriel :\nJe suis ton fan numéro 1 ! C'est décidé !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 17 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "base", "Kiki :\nHéhé, ce n'est rien de si spécial Tutoriel... Allez, continuons de résoudre ces puzzles, et reconstruisons notre maison !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 18 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "uwu", "Tutoriel :\nOui, allons-y ! Je vais t'attendre dans la salle suivante, ce niveau me fait tourner la tête !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 19 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "uwu", "Tutoriel :\nTu peux le faire Kiki !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 20 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "sed", "Kiki :\n( Il dit qu'il est mon fan, mais il me laisse encore seule, et derrière...)", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            // Closing case
                                            case 21 :
                                                event_progress++;
                                                vh += vh_increment(vh,true);
                                                event_pending = false;
                                            break;

                                            case 22:
                                                // abujabuja
                                            break;

                                        }
                            break;

                            // Le skip général
                            case SDLK_SPACE:
                                if (skip == 50){
                                    vh += vh_increment(vh, false);
                                    event_pending = false;
                                    event_progress++;
                                    skip++;
                                    
                                }
                                else{if (skip < 50){
                                    skip = skippeable(skip, gWindow, gRenderer, events, font);
                                    }
                                }

                            
                            break;

                            default:
                                //no queues plz
                            break;

                            }
                    break;

                    case SDL_KEYUP:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_SPACE:
                                if (skip<50){
                                    skip = 0;
                                    skippeable(skip, gWindow,  gRenderer, events, font);
                                }
                                break;
                            default:
                                //no queues plz
                            break;
                            }
                    break;
                        
                    case SDL_QUIT:
                    //Le cas où on appuie sur la croix, pour fermer la fenêtre
                        event_pending = false;
                        break;
                }
            }
    }

    SDL_RenderClear(gRenderer);

    //SDL_FreeSurface(box) // Il est free dans le box_destroy;
    return vh;
}

// Toutes les salls de Lise, pas de debug mode, rouge, blu débloqués

int ep78(int variable_histoire, int** carte,SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText){
    int vh = variable_histoire;
    int event_progress = 0;
    int skip = 0;
    bool event_pending = true;

    

    dialogue_box_colour(gWindow, gRenderer);
    cadre(gWindow, gRenderer);
    skippeable(skip, gWindow,  gRenderer, events, font);

    // La première ligne de dialogue peut toujours changer selon si le PJ a été gentil avec Tutoriel précédemment ou non
    if (vh%2==1){
        dialogue("Tutoriel", "base", "Tutoriel :\nBleu ! C'est tout bleu ! Je ne pensais pas que tu y arriverais !", gWindow, gRenderer, font);
    }
    else{
        dialogue("Tutoriel", "base", "Tutoriel :\n Oh !Tu as trouvé une couleur !", gWindow, gRenderer, font);
    }
    event_progress=1;

    while (event_pending){
        while (SDL_PollEvent(&events))
            {
                switch (events.type)
                {
                    case SDL_KEYDOWN:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_RETURN:
                                    switch(event_progress)
                                        {

                                            case 1 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nC'est vraiment une belle couleur... Et je ne suis pas du tout biaisé, c'est juste comme ça qu'on m'a écrit.", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 2 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "base", "Kiki :\nQu'on t'a écrit ?", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 3 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nOui, qu'on m'a écrit ! Ne t'en fais pas Kiki, ce n'est rien de grave, ni rien de bien méchant !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 4 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "base", "Kiki :\nBon d'accord !", gWindow, gRenderer, font);
                                                event_progress=6;
                                            break;

                                            /*case 5 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nJe ne sais pas toi, mais ce niveau me fait tourner la tête !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;*/

                                            case 6 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nEt apparemment, les deux nouvelles couleurs ont amenées avec elles de nouvelles mécaniques ! Même si je n'ai pas encore trouvé ce qu'elles faisaient...", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 7 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "base", "Kiki :\nDeux ? Je pensais qu'on n'avait trouvé que le \"bleu\" ?", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 8 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nJe crois que j'ai aussi vu du rouge dans le coin ! Mais j'ai un peu trop l'habitude de me déplacer en surfant entre les lignes de codes pour pouvoir en être sûr...", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            /*case 8 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nMais je suis sûr que toi tu pourras y arriver !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;*/

                                            case 9 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nMais je suis sûr que tu trouveras comment faire pour naviguer dans cette salle !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;
                                            
                                            case 10 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nÀ la prochaine !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 11 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nEncore une fois, n'hésite pas à m'appeler avec la touche T si tu as besoin d'aide !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            // Closing case
                                            case 12 :
                                                event_progress++;
                                                vh += vh_increment(vh,true);
                                                event_pending = false;
                                            break;

                                            case 13 :
                                                // coucou
                                            break;

                                        }
                            break;

                            // Le skip général
                            case SDLK_SPACE:
                                if (skip == 50){
                                    vh += vh_increment(vh, false);
                                    event_pending = false;
                                    event_progress++;
                                    skip++;
                                    
                                }
                                else{if (skip < 50){
                                    skip = skippeable(skip, gWindow, gRenderer, events, font);
                                    }
                                }

                            
                            break;

                            default:
                                //no queues plz
                            break;

                            }
                    break;

                    case SDL_KEYUP:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_SPACE:
                                if (skip<50){
                                    skip = 0;
                                    skippeable(skip, gWindow,  gRenderer, events, font);
                                }
                                break;
                            default:
                                //no queues plz
                            break;
                            }
                    break;
                        
                    case SDL_QUIT:
                    //Le cas où on appuie sur la croix, pour fermer la fenêtre
                        event_pending = false;
                        break;
                }
            }
    }

    SDL_RenderClear(gRenderer);

    //SDL_FreeSurface(box) // Il est free dans le box_destroy;
    return vh;
}




// Fin

int ep910(int variable_histoire, int** carte,SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText){
    int vh = variable_histoire;
    int event_progress = 0;
    int skip = 0;
    bool event_pending = true;

    dialogue_box_nb(gWindow, gRenderer);
    cadre(gWindow, gRenderer);
    skippeable(skip, gWindow,  gRenderer, events, font);

    // La première ligne de dialogue peut toujours changer selon si le PJ a été gentil avec Tutoriel précédemment ou non
    if (vh%2==1){
        dialogue("Tutoriel", "sed", "Tutoriel :\nQu'est-ce que tu as ENCORE fait ?!", gWindow, gRenderer, font);
    }
    else{
        dialogue("Tutoriel", "sed", "Tutoriel :\nKiki, qu'est-ce qu'il se passe ?", gWindow, gRenderer, font);
    }
    event_progress=3;

    while (event_pending){
        while (SDL_PollEvent(&events))
            {
                switch (events.type)
                {
                    case SDL_KEYDOWN:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_RETURN:
                                    switch(event_progress)
                                        {
                                            case 1 :
                                                event_progress++;
                                                vh += vh_increment(vh,true);
                                                event_pending = false;
                                            break;

                                            case 2 :
                                                // coucou :D
                                            break;

                                            case 3 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "sed", "Tutoriel :\nTout a soudainement de nouveau disparu...", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 4 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "sed", "Tutoriel :\nEt j'ai aussi trouvé ce message...", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 5 :
                                                remise_surface(vh, false, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                narration_prog("Merci d'avoir joué à la demo de \\debug_mode !", gWindow, gRenderer, fontProg);
                                                event_progress++;
                                            break;

                                            case 6 :
                                                remise_surface(vh, false, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                narration_prog("Ce projet a été créé en SDL, avec l'aide de sang, de larmes et de sacrifice d'OS.", gWindow, gRenderer, fontProg);
                                                event_progress++;
                                            break;

                                            case 7 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "sed", "Tutoriel :\nJ'espère que ce n'est rien de trop grave, je n'arrive pas à lire le code derrière...", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 8 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "base", "Kiki :\nLe code... ? Mais il y a juste écrit que c'est la fin de la \"demo\"...", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 9 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "uwu", "Tutoriel :\nOh !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 10 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "uwu", "Tutoriel :\nFélicitations pour être arrivé au bout de la démo !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 11 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "uwu", "Tutoriel :\nOn a accompli tout ce qu'il y avait à accomplir ici Kiki !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 12 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "sed", "Kiki :\nMais pourquoi est-ce que le monde d'ici est si vide alors... ?", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 13 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nNe t'en fais pas Kiki. C'est juste une manière de nous inviter à avoir de nouvelles aventures.", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 14 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nLe \"chapitre\" est terminé, mais ça reste le début de l'histoire.", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 15 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "base", "Tutoriel :\nAlors ne te sens pas trop triste, d'accord ?", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 16 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "sed", "Kiki :\n...", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 17 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "base", "Kiki :\nD'accord !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 18 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Kiki", "base", "Kiki :\nAllons découvrir la suite de l'histoire ensemble alors, Tutoriel !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            case 19 :
                                                remise_surface(vh, true, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                                skippeable(skip, gWindow,  gRenderer, events, font);
                                                dialogue("Tutoriel", "uwu", "Tutoriel :\nJe te suis Kiki !", gWindow, gRenderer, font);
                                                event_progress++;
                                            break;

                                            // Closing case
                                            case 20 :
                                                event_progress++;
                                                vh += vh_increment(vh,true);
                                                event_pending = false;
                                            break;

                                            case 21 :
                                                // nothing here
                                            break;

                                        }
                            break;

                            // Le skip général
                            case SDLK_SPACE:
                                if (skip == 50){
                                    remise_surface(vh, false, carte, spriteRect,destRect, spriteText, gWindow, gRenderer);
                                    narration("C'est la fin de la démo, merci d'avoir joué !", gWindow, gRenderer, font);
                                    event_progress=1;
                                    skip++;
                                    
                                }
                                else{if (skip < 50){
                                    skip = skippeable(skip, gWindow, gRenderer, events, font);
                                    }
                                }

                            
                            break;

                            default:
                                //no queues plz
                            break;

                            }
                    break;

                    case SDL_KEYUP:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_SPACE:
                                if (skip<50){
                                    skip = 0;
                                    skippeable(skip, gWindow,  gRenderer, events, font);
                                }
                                break;

                            default:
                                //no queues plz
                            break;
                            }
                    break;
                        
                    case SDL_QUIT:
                    //Le cas où on appuie sur la croix, pour fermer la fenêtre
                        event_pending = false;
                        break;
                }
            }
    }

    SDL_RenderClear(gRenderer);

    //SDL_FreeSurface(box) // Il est free dans le box_destroy;
    return vh;
}

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------
// ---------------------------------ALED TUTORIEL--------------------------------------
// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------

int call_tutoriel(int variable_histoire, int** carte, int agacement, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* fontProg, SDL_Rect spriteRect, SDL_Rect destRect, SDL_Texture* spriteText){
    int graou = agacement;
    bool aled = true;
    SDL_Event events;

    if(variable_histoire%2==1){
        graou += 1;
    }

    int tuto_progress = 0;

    // Affichage de la boîte de dialogue
    if (variable_histoire > BLEU && variable_histoire < 9){
        dialogue_box_colour(gWindow,gRenderer);
    }
    else{
        dialogue_box_nb(gWindow,gRenderer);
    }

    // Texte initial

    // Branche : Tutoriel répond ou pas
    if (agacement >= 5 && agacement <= 10){
        narration_prog("Tutoriel ignore votre appel.",gWindow, gRenderer, fontProg);
        tuto_progress=1;
        graou++;
    }
    else{
        // Tutoriel répond donc il faut un cadre
        cadre(gWindow,gRenderer);
        // La réponse de Tutoriel dépend d'à quel point on l'a énervé
        if (agacement < 5){
            dialogue_prog("Tutoriel","base","Tutoriel :\n Que puis-je faire pour toi ?\nA. \"J'aurais besoin d'aide...\"\nB. \"Non, rien !\"", gWindow, gRenderer, fontProg);
        }
        else{
            dialogue_prog("Tutoriel","sed","Tutoriel :\n Qu'est-ce que tu me veux... ?\nA. \"J'ai besoin de ton aide...\"\nB. \"Non, rien !\"", gWindow, gRenderer, fontProg);
        }
    }

    // La souite

    while(aled){
        while (SDL_PollEvent(&events))
            {
                switch (events.type)
                {
                    case SDL_KEYDOWN:
                        switch (events.key.keysym.sym)
                            {
                            case SDLK_RETURN:
                                // Le cas où Tutoriel nous fait graou
                                if (agacement >= 5 && agacement <= 10){
                                aled = false;
                                }
                                else{
                                    // Aled porte très bien son nom. A l'aide.
                                    switch (variable_histoire){
                                        case 3: case 4:
                                            switch (tuto_progress){
                                                case 0:
                                                // On a demandé d'appuyer sur A ou B d'abord.
                                                break;
                                                case 1 :
                                                    aled = false;
                                                    tuto_progress++;
                                                break;
                                                case 2 :
                                                    // Nothing to see
                                                break;
                                                case 3 :
                                                    remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                                    dialogue_prog("Tutoriel","base","Tutoriel :\nPour pouvoir progresser, il faut que tu utilises une mécanique appelée le \"terminal\".",gWindow,gRenderer,fontProg);
                                                    tuto_progress++;
                                                break;
                                                case 4 :
                                                    remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                                    dialogue_prog("Tutoriel","base","Tutoriel :\nAfin d'ouvrir ce \"terminal\", il faut que tu appuies sur la touche [LEFT SHIFT].",gWindow,gRenderer,fontProg);
                                                    tuto_progress++;
                                                break;
                                                case 5 :
                                                    remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                                    dialogue_prog("Tutoriel","base","Tutoriel :\nÀ partir de là, tu peux taper les commandes affichées, pour pouvoir activer différents pouvoirs !.",gWindow,gRenderer,fontProg);
                                                    tuto_progress++;
                                                break;
                                                case 6 :
                                                    remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                                    dialogue_prog("Tutoriel","base","Tutoriel :\nPour le moment, je te conseillerais d'utiliser le pouvoir [\\map] pour pouvoir naviguer dans la pièce, et me rejoindre dans la suivante !.",gWindow,gRenderer,fontProg);
                                                    tuto_progress++;
                                                break;
                                                case 7 :
                                                    remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                                    dialogue_prog("Tutoriel","base","Tutoriel :\nÀ tout de suite Kiki !",gWindow,gRenderer,fontProg);
                                                    tuto_progress++;
                                                break;
                                                case 8 :

                                                    aled=false;
                                                    tuto_progress++;
                                                break;
                                                case 9:
                                                    //endcases :D
                                                break;
                                            }
                                        break;
                                        default:
                                            switch (tuto_progress){
                                                case 0:
                                                // On a demandé d'appuyer sur A ou B d'abord.
                                                break;
                                                case 1 :
                                                    aled = false;
                                                    tuto_progress++;
                                                break;
                                                case 2 :
                                                    // Nothing to see
                                                break;
                                                case 3 :
                                                    remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                                    dialogue_prog("Tutoriel","base","Tutoriel :\nSur quelle fonction tu as besoin d'aide ?\nA. Le terminal\nB. Annuler",gWindow,gRenderer,fontProg);
                                                    tuto_progress++;
                                                break;
                                                case 4 :
                                                    // Nothing to see
                                                break;
                                                case 5 :
                                                    remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                                    dialogue_prog("Tutoriel","base","Tutoriel :\nUne fois que c'est ouvert, tu as juste à taper une des commandes qui sont affichées pour lancer un pouvoir !",gWindow,gRenderer,fontProg);
                                                    tuto_progress++;
                                                break;
                                                case 6 :
                                                    aled=false;
                                                    tuto_progress++;
                                                break;
                                                case 7 :
                                                    // babai :D
                                                break;
                                            }
                                        break;
                                        
                                    }
                                }
                                
                            break;

                            case SDLK_a:
                                if(tuto_progress==0){
                                    switch (variable_histoire){
                                        case 3 : 
                                            remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                            dialogue_prog("Tutoriel","uwu","Tutoriel :\nDonc... tu as besoin de mon aide finalement... ?",gWindow,gRenderer,fontProg);
                                            tuto_progress = 3;
                                            graou = 0;
                                        break;
                                        case 4:
                                            remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                            dialogue_prog("Tutoriel","base","Tutoriel :\nOui, bien sûr ! Tutoriel, toujours prêt à donner un coup de main !",gWindow,gRenderer,fontProg);  
                                            tuto_progress = 3;
                                            graou = 0;                            
                                        break;
                                        default:
                                            remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                            dialogue_prog("Tutoriel","base","Tutoriel :\nDis-moi tout !",gWindow,gRenderer,fontProg);  
                                            tuto_progress = 3;
                                            graou = 0;
                                        break;
                                    
                                    }
                                }
                                if (tuto_progress==3){
                                    switch (variable_histoire)
                                    {                                    
                                    default:
                                        remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                        dialogue_prog("Tutoriel","base","Tutoriel :\nPour ouvrir un terminal, il suffit d'appuyer sur [LEFT SHIFT] !",gWindow,gRenderer,fontProg);
                                        tuto_progress=5;
                                    break;
                                    }
                                }
                                
                            break;

                            case SDLK_b:
                                if (tuto_progress==0||(tuto_progress==3)){
                                    switch(agacement){
                                        case 0 :
                                            remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                            dialogue_prog("Tutoriel","base","Tutoriel :\nOh... Je suppose que tu as mistype...",gWindow,gRenderer,fontProg);
                                        break;
                                        case 1 :
                                            remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                            dialogue_prog("Tutoriel","base","Tutoriel :\nTon doigt glisse beaucoup décidément...",gWindow,gRenderer,fontProg);
                                        break;
                                        case 2 :
                                            remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                            dialogue_prog("Tutoriel","base","Tutoriel :\n... Tu t'amuses bien ?",gWindow,gRenderer,fontProg);
                                        break;
                                        case 3 :
                                            remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                            dialogue_prog("Tutoriel","sed","Tutoriel :\nS'il te plaît, arrête... Je viens toujours aussi vite que possible, et tu ne veux jamais de moi...",gWindow,gRenderer,fontProg);
                                        break;
                                        case 4 :
                                            remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                            dialogue_prog("Tutoriel","sed","Tutoriel :\nSi c'est comme ça, je ne viendrai plus t'aider !",gWindow,gRenderer,fontProg);
                                        break;
                                        default :
                                            remise_surface(variable_histoire,true,carte,spriteRect,destRect,spriteText,gWindow,gRenderer);
                                            dialogue_prog("Tutoriel","sed","Tutoriel :\nPourquoi tu m'infliges ça...? Qu'est-ce que j'ai fait de mal pour mériter ça... ?",gWindow,gRenderer,fontProg);
                                            graou = 5;
                                        break;
                                    }
                                    tuto_progress = 1;
                                    graou ++;
                                }
                            break;
                            }
                    break;
                }

            }
                                

    }
    
    SDL_RenderClear(gRenderer);

    return graou;
}


