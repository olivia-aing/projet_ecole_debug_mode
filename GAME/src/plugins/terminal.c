#include "terminal.h"


void open_terminal(int variable_histoire, SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Event events, TTF_Font* font){
    // On ouvre la fenêtre de terminal

    /*
    if (variable_histoire > 4) // nombre arbitraire où on débloque le bleu
    {
        terminal_box_colour(gWindow, gRenderer);
    }
    else{
        terminal_box_nb(gWindow, gRenderer);
        
    }
    */
    // On a que le terminal noir
    terminal_box_nb(gWindow, gRenderer);    

    // On affiche les commandes sur la fenêtre de terminal
    affiche_commandes(variable_histoire, gWindow, gRenderer, font);

    return;
}



void affiche_commandes(int variable_histoire, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font){
    char* commandes_dispo1 = "\\close ou \\c : Ferme le terminal\n\\save : Sauvegarde le fichier de jeu\n\\map : Ouvre la carte\n\\close_map : Ferme la carte";
    char* commandes_dispo2 = "\\debug_mode : Permet de traverser tous les éléments de la carte\n\\normal_mode : Permet d'intéragir de nouveau avec le monde";

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

    // Création de la surface et texture de texte
    SDL_Surface* tSurface = NULL;
    SDL_Texture* tTexture = NULL;


    // Les commandes de base s'affichent

    // Si on ne met pas le Wrapped, alors il ignore les sauts à la ligne le saligaut
    tSurface = TTF_RenderUTF8_Solid_Wrapped(font, commandes_dispo1, textColor, rect.w);
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

    if(variable_histoire > 4 ) // Encore une fois, un magnifique nombre pour le moment arbitraire
    {
        int olh = textH;

        SDL_FreeSurface(tSurface);
        SDL_DestroyTexture(tTexture);
        tSurface = NULL;
        tTexture = NULL;

        tSurface = TTF_RenderUTF8_Solid_Wrapped(font, commandes_dispo2, textColor, rect.w);
        tTexture = SDL_CreateTextureFromSurface(gRenderer, tSurface);
        
        SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_NONE);

        SDL_QueryTexture(tTexture, NULL, NULL, &textW, &textH);

        dstrect.y = dstrect.y + olh;
        dstrect.w = textW;
        dstrect.h = textH;

        SDL_RenderCopy(gRenderer, tTexture, NULL, &dstrect);

        SDL_RenderPresent(gRenderer);

    }



    // LA LIBERTEEEEE
    SDL_FreeSurface(tSurface);
    SDL_DestroyTexture(tTexture);
    SDL_FreeSurface(gScreen);


}


/* fonction à part pour le terminal */
int terminal (SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* GrandPixel, Save* sauvegarde,int *debug_mod, int *pouvoir_carte,int *compteur_astar) {

    SDL_RenderClear(gRenderer) ; 
    SDL_RenderFillRect(gRenderer, NULL);
    bool terminal_open = true ;
    
    
    bool isOpen = 0 ;
    SDL_Event events;
    int story_progress = sauvegarde->avancement;
    int recall;

    char textinput[300];
    textinput[0]='\0';
    int i = 0;
    SDL_Surface *text;
    SDL_Texture *textTexture;
    SDL_Color textColor = {255, 255, 255, 255};
    int w;
    int h;

    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    if (gScreen == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] gScreen > %s", SDL_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }
    int a = gScreen->w;
    int b = gScreen->h;

    open_terminal(story_progress,gWindow,gRenderer, events, GrandPixel);

    while (terminal_open) {
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT: /* Le cas où on appuie sur la croix, pour fermer la fenêtre */
                    terminal_open = false ;
                    isOpen = 1 ; // dans le main -> on quitte aussi le jeu (pas que le terminal)
                break;
                
                case (SDL_TEXTINPUT):
                    if (events.text.text[0]!='\0'){
                        textinput[i]=events.text.text[0];
                        textinput[i+1] ='\0';
                    }
                    else{
                        printf("erreur SDL_TEXTINPUT");
                    }
                    text = TTF_RenderText_Solid(GrandPixel,textinput, textColor); 
                    if (text ==NULL ){
                        printf("aaaaaaaah");
                        terminal_open = false ;
                        isOpen = 1 ;
                    }
                    w = text->w;
                    h = text->h;
                    textTexture = SDL_CreateTextureFromSurface(gRenderer, text); // texture de texte pour l'afficher
                    if (textTexture == NULL) {
                        printf("Failed to create texture from surface! SDL Error: %s\n", SDL_GetError());
                        terminal_open = false ;
                        isOpen= 1;
                    }
                    SDL_FreeSurface(text);
                    i++;
                break; // fin du case (SDL_TEXTINPUT):

                case SDL_KEYDOWN:
                    switch (events.key.keysym.sym) {
                        case SDLK_RETURN:
                            if (textinput[0]=='\\' && textinput[1]=='c' && textinput[2]=='l' && textinput[3]=='o' && textinput[4]=='s' && textinput[5]=='e'){
                                i=0;
                                terminal_open = false;
                            } // fin cas "\close" pour fermer le terminal
                            if (textinput[0]=='\\' && textinput[1]=='c'){
                                i=0;
                                terminal_open = false;
                            } // fin cas "\c" pour fermer le terminal

                            if (textinput[0]=='\\' && textinput[1]=='s' && textinput[2]=='a' && textinput[3]=='v' && textinput[4]=='e'){
                                saveGame(sauvegarde);

                                text = TTF_RenderText_Solid(GrandPixel,textinput, textColor);
                                if (text ==NULL ){
                                    printf("aaaaaaaah :%s\n",SDL_GetError());
                                    isOpen = false;
                                }
                                w = text->w;
                                h = text->h;
                                //SDL_SetRenderDrawColor(gRenderer,255,0,0,255);
                                SDL_Rect dstRect = {10, b-50, w, h};
                                //SDL_RenderFillRect(gRenderer,&dstRect);
                                open_terminal(story_progress,gWindow,gRenderer, events, GrandPixel);
                                textTexture = SDL_CreateTexture(gRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,w,h);
                                SDL_FreeSurface(text);
                                i=0;
                            } // fin "\save"

                            if (textinput[0]=='\\' && textinput[1]=='m' && textinput[2]=='a' && textinput[3]=='p'){
                                // printf("j'ouvre la carte");
                                *pouvoir_carte=1;
                                *compteur_astar=10;

                                text = TTF_RenderText_Solid(GrandPixel,textinput, textColor);
                                if (text ==NULL ){
                                    printf("aaaaaaaah :%s\n",SDL_GetError());
                                    isOpen = false;
                                }
                                w = text->w;
                                h = text->h;
                                //SDL_SetRenderDrawColor(gRenderer,255,0,0,255);
                                SDL_Rect dstRect = {10, b-50, w, h};
                                //SDL_RenderFillRect(gRenderer,&dstRect);
                                open_terminal(story_progress,gWindow,gRenderer, events, GrandPixel);
                                textTexture = SDL_CreateTexture(gRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,w,h);
                                SDL_FreeSurface(text);
                                i=0;
                            } // fin "\map"

                            if (textinput[0]=='\\' && textinput[1]=='c' && textinput[2]=='l' && textinput[3]=='o' && textinput[4]=='s' && textinput[5]=='e' && textinput[6]=='_' && textinput[7]=='m' && textinput[8]=='a' && textinput[9]=='p'){
                                // printf("je ferme la carte");
                                *pouvoir_carte=0;
                                text = TTF_RenderText_Solid(GrandPixel,textinput, textColor);
                                if (text ==NULL ){
                                    printf("aaaaaaaah :%s\n",SDL_GetError());
                                    isOpen = false;
                                }
                                w = text->w;
                                h = text->h;
                                //SDL_SetRenderDrawColor(gRenderer,255,0,0,255);
                                SDL_Rect dstRect = {10, b-50, w, h};
                                //SDL_RenderFillRect(gRenderer,&dstRect);
                                open_terminal(story_progress,gWindow,gRenderer, events, GrandPixel);
                                textTexture = SDL_CreateTexture(gRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,w,h);
                                SDL_FreeSurface(text);
                                i=0;
                            } // fin "\close"

                            if (textinput[0]=='\\' && textinput[1]=='d' && textinput[2]=='e' && textinput[3]=='b' && textinput[4]=='u' && textinput[5]=='g' && textinput[6]=='_' && textinput[7]=='m' && textinput[8]=='o' && textinput[9]=='d' && textinput[10]=='e'){
                                *debug_mod=1;
                                text = TTF_RenderText_Solid(GrandPixel,textinput, textColor);
                                if (text ==NULL ){
                                    printf("aaaaaaaah :%s\n",SDL_GetError());
                                    isOpen = false;
                                }
                                w = text->w;
                                h = text->h;
                                //SDL_SetRenderDrawColor(gRenderer,255,0,0,255);
                                SDL_Rect dstRect = {10, b-50, w, h};
                                //SDL_RenderFillRect(gRenderer,&dstRect);
                                open_terminal(story_progress,gWindow,gRenderer, events, GrandPixel);
                                textTexture = SDL_CreateTexture(gRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,w,h);
                                SDL_FreeSurface(text);
                                i=0;
                            } // fin "\debug_mode"

                            if (textinput[0]=='\\' && textinput[1]=='n' && textinput[2]=='o' && textinput[3]=='r' && textinput[4]=='m' && textinput[5]=='a' && textinput[6]=='l' && textinput[7]=='_' && textinput[8]=='m' && textinput[9]=='o' && textinput[10]=='d' && textinput[11]=='e'){
                                *debug_mod=0;
                                text = TTF_RenderText_Solid(GrandPixel,textinput, textColor);
                                if (text ==NULL ){
                                    printf("aaaaaaaah :%s\n",SDL_GetError());
                                    isOpen = false;
                                }
                                w = text->w;
                                h = text->h;
                                //SDL_SetRenderDrawColor(gRenderer,255,0,0,255);
                                SDL_Rect dstRect = {10, b-50, w, h};
                                //SDL_RenderFillRect(gRenderer,&dstRect);
                                open_terminal(story_progress,gWindow,gRenderer, events, GrandPixel);
                                textTexture = SDL_CreateTexture(gRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,w,h);
                                SDL_FreeSurface(text);
                                i=0;
                            } // fin "\normal_mode"
                        break; // fin du cas 'Return'

                        case SDLK_BACKSPACE:
                            if (textinput[0]!='\0' && textinput[1]!='\0'){
                                //printf("he: %d\n",i);
                                text = TTF_RenderText_Solid(GrandPixel,textinput,textColor);
                                if (text ==NULL ) {
                                    printf("aaaaaaaah :%s\n",SDL_GetError());
                                    isOpen = false;
                                }
                                w = text->w;
                                h = text->h;
                                // SDL_SetRenderDrawColor(gRenderer,255,255,0,255);
                                SDL_Rect dstRect = {10, b-50, w, h};
                                // SDL_RenderFillRect(gRenderer,&dstRect);
                                open_terminal(story_progress,gWindow,gRenderer, events, GrandPixel);
                                textTexture = SDL_CreateTexture(gRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,w,h);
                                SDL_FreeSurface(text);
                                SDL_RenderCopy(gRenderer, textTexture, NULL, &dstRect);
                                SDL_RenderPresent(gRenderer);

                                i=i-1;
                                textinput[i]='\0';
                                text = TTF_RenderText_Solid(GrandPixel,textinput,textColor);
                                if (text ==NULL ){
                                    printf("aaaaaaaah :%s\n",SDL_GetError());
                                    isOpen = false;
                                    }
                                w = text->w;
                                h = text->h;
                                textTexture= SDL_CreateTextureFromSurface(gRenderer, text);
                                if (textTexture == NULL) {
                                    printf("Failed to create texture from surface! SDL Error: %s\n", SDL_GetError());
                                    isOpen= false;
                                }
                                SDL_FreeSurface(text);
                                break;
                            } // fin du if 

                            if (textinput[0]!='\0' && textinput[1]=='\0'){
                                //printf("hu: %d\n",i);
                                text = TTF_RenderText_Solid(GrandPixel,textinput, textColor);
                                if (text ==NULL ){
                                    printf("aaaaaaaah :%s\n",SDL_GetError());
                                    isOpen = false;
                                }
                                w = text->w;
                                h = text->h;
                                //SDL_SetRenderDrawColor(gRenderer,255,0,0,255);
                                SDL_Rect dstRect = {10, b-50, w, h};
                                SDL_RenderFillRect(gRenderer,&dstRect);
                                open_terminal(story_progress,gWindow,gRenderer, events, GrandPixel);
                                textTexture = SDL_CreateTexture(gRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,w,h);
                                SDL_FreeSurface(text);
                                i=0;
                                break;
                            } // fin du 2e if 
                        // fin case SDLK_BACKSPACE

                    } // fin du switch
                    
                break; // fin du case (SDL_KEYDOWN):

            } // fin switch (events.type)

            //affiche_commandes(story_progress,gWindow,gRenderer,GrandPixel);
            SDL_Rect dstRect = {10, b-50, w, h};// Position to render the text
            SDL_RenderCopy(gRenderer, textTexture, NULL, &dstRect);
            SDL_RenderPresent(gRenderer);
            
        } // fin de la boucle de vérif des évents
        //SDL_RenderClear(gRenderer);
        
        
        
    } // fin de la boucle du terminal ouvert
    // destroy(NULL,gRenderer,NULL);
    // SDL_CreateRenderer(gWindow, -1, flags2);
    return isOpen ;

}
