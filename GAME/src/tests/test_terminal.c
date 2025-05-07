/*Ajout des bibliothèques*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "./../plugins/terminal.h"

int window_height = 600;
int window_width = 800;



int main(int argc, char *argv[])
{
    /*Initialisation, vérification que tout fonctionne*/
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] init > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window* gWindow = NULL ;
    gWindow = SDL_CreateWindow("\\debug_mode",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);   
    SDL_Renderer* gRenderer = NULL ;
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gWindow == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] gWindow > %s", SDL_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    if (gRenderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] gRenderer > %s", SDL_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    if (IMG_Init(IMG_INIT_PNG)==0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] IMG_Init > %s", SDL_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        IMG_Quit();    
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    if (TTF_Init()==-1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] TTF_Init > %s", TTF_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        TTF_Quit();
        IMG_Quit();    
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    TTF_Font* PTPixel = NULL;
    PTPixel = TTF_OpenFont("img/assets/Puzzle-Tale-Pixel-Regular.ttf",20);
    TTF_SetFontStyle(PTPixel, TTF_STYLE_NORMAL);
    TTF_SetFontHinting(PTPixel, TTF_HINTING_NORMAL);

    if(PTPixel==NULL)
    {
        printf("Erreur de création de la police : %s", TTF_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] TTF_Init > %s", TTF_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        TTF_CloseFont(PTPixel);
        TTF_Quit();
        IMG_Quit();    
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    TTF_Font* GrandPixel = NULL;
    GrandPixel = TTF_OpenFont("img/assets/Grand9K-Pixel.ttf",20);
    TTF_SetFontStyle(GrandPixel, TTF_STYLE_NORMAL);
    TTF_SetFontHinting(GrandPixel, TTF_HINTING_NORMAL);

    if(GrandPixel==NULL)
    {
        printf("Erreur de création de la police : %s", TTF_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] TTF_Init > %s", TTF_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        TTF_CloseFont(PTPixel);
        TTF_CloseFont(GrandPixel);
        TTF_Quit();
        IMG_Quit();    
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

    /*
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    */
    

    SDL_Event events;
    bool isOpen = true ;
    int story_progress = 0;
    int recall;

    char textinput[30];
    textinput[0]='\0';
    int i = 0;
    SDL_Surface *text;
    SDL_Texture *textTexture;
    SDL_Color textColor = {255, 255, 255, 255};
    int w;
    int h;


    SDL_Surface* gScreen = SDL_GetWindowSurface(gWindow) ;
    int a = gScreen->w;
    int b = gScreen->h;

    int bot_h = (int)floor(0.1*b);

    SDL_Rect rectbot;
    rectbot.x = 1;
    rectbot.y = h-bot_h;
    rectbot.h = bot_h-1;
    rectbot.w = w-2;

    //non initialisés mais c'est pour que ca marche
    int carte1[NOMBRE_TILE_HAUTEUR][NOMBRE_TILE_LARGEUR];
    SDL_Rect spriteRect;
    SDL_Rect destRect;
    SDL_Texture* spriteText;

    bool terminal_open = false;
  
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
                case (SDL_TEXTINPUT):
                    if (terminal_open){

                        if (events.text.text[0]!='\0'){
                        textinput[i]=events.text.text[0];
                        textinput[i+1] ='\0';
                        }
                        else{
                            printf('erreur ici');
                        }
                        text = TTF_RenderText_Solid(GrandPixel,textinput, textColor);
                        if (text ==NULL ){
                            printf("aaaaaaaah");
                            isOpen = false;
                        }
                        w = text->w;
                        h = text->h;
                        textTexture = SDL_CreateTextureFromSurface(gRenderer, text);
                        if (textTexture == NULL) {
                            printf("Failed to create texture from surface! SDL Error: %s\n", SDL_GetError());
                            isOpen= false;
                        }
                        SDL_FreeSurface(text);
                        i++;
                        break;
                    }
                    break;
                
                case SDL_KEYDOWN:
                switch (events.key.keysym.sym) {
                    case SDLK_LSHIFT:
                        open_terminal(story_progress,gWindow,gRenderer, events, GrandPixel);
                        terminal_open = true;
                        break;
                    case SDLK_UP:
                        story_progress = 20;
                    break;
                    case SDLK_DOWN:
                        story_progress = 0;
                    break;
                    case SDLK_RETURN:
                        if (textinput[0]=='\\' && textinput[1]=='c' && textinput[2]=='l' && textinput[3]=='o' && textinput[4]=='s' && textinput[5]=='e'){
                            //box_destroy(carte1,gWindow,gRenderer,spriteRect, destRect, spriteText);
                            printf("je ferme la fenêtre");
                            i=0;
                            terminal_open = false;
                            
                            
                        }
                        if (textinput[0]=='\\' && textinput[1]=='s' && textinput[2]=='a' && textinput[3]=='v' && textinput[4]=='e'){
                            printf("je sauvegarde le jeu");
                            
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

                        }
                        if (textinput[0]=='\\' && textinput[1]=='m' && textinput[2]=='a' && textinput[3]=='p'){
                            printf("j'ouvre la carte");
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
                        }
                         if (textinput[0]=='\\' && textinput[1]=='c' && textinput[2]=='l' && textinput[3]=='o' && textinput[4]=='s' && textinput[5]=='e' && textinput[6]=='_' && textinput[7]=='m' && textinput[8]=='a' && textinput[9]=='p'){
                            printf("je ferme la carte");
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
                        }
                        if (textinput[0]=='\\' && textinput[1]=='d' && textinput[2]=='e' && textinput[3]=='b' && textinput[4]=='u' && textinput[5]=='g' && textinput[6]=='_' && textinput[7]=='m' && textinput[8]=='o' && textinput[9]=='d' && textinput[10]=='e' && story_progress==20){ //20 au pif ici et dans les 2 suivants
                            printf("debug_mode activé");
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
                        }
                        if (textinput[0]=='\\' && textinput[1]=='n' && textinput[2]=='o' && textinput[3]=='r' && textinput[4]=='m' && textinput[5]=='a' && textinput[6]=='l' && textinput[7]=='_' && textinput[8]=='m' && textinput[9]=='o' && textinput[10]=='d' && textinput[11]=='e' && story_progress==20){
                            printf("debug_mode désactivé");
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
                        }
                        
                    break;
                    case SDLK_BACKSPACE:
                        if (textinput[0]!='\0' && textinput[1]!='\0'){
                            //printf("he: %d\n",i);
                            text = TTF_RenderText_Solid(GrandPixel,textinput,textColor);
                            if (text ==NULL ){
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
                        }
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
                        }
                   
                }
                break;

            }
           
        }
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(PTPixel);
    TTF_CloseFont(GrandPixel);
    TTF_Quit();
    IMG_Quit();    
    SDL_Quit(); 
    return EXIT_SUCCESS;
}