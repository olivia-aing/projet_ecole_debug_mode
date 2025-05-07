#include "../plugins/sprite.h"

int main(void){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) !=0){
        printf("error in intialization of SDL : %s\n", SDL_GetError());
        return -1;
    }
    // SDL_Window* pWindow = NULL ;     
    // SDL_Renderer* pRenderer = NULL ;
    // if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    // {
    //     SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
    //     SDL_Quit(); 
    //     return EXIT_FAILURE;
    // }

    SDL_Window *pWindow = SDL_CreateWindow("Mouvement du sprite",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            larg_fenetre,
                                            haut_fenetre,
                                            0 );
    if (pWindow==NULL){
        printf("error in creation of SDL window : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ;
    SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow, -1, flags);

    if (pRenderer==NULL){
        printf("error in creation of SDL renderer : %s\n", SDL_GetError());
        destroy(pWindow,NULL,NULL);
        return -1;
    }


    

    SDL_Event events;
    bool isOpen = true ;

    SDL_Surface *surface =NULL;
    surface = IMG_Load("././img/sprites/Kiki_sprite_sheet.png");
    if (surface==NULL){
        printf("error in creation of SDL surface : %s\n", SDL_GetError());
        destroy(pWindow,pRenderer,NULL);
        return -1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    SDL_FreeSurface(surface);

    if (texture==NULL){
        printf("error in creation of SDL texture : %s\n", SDL_GetError());
        destroy(pWindow,pRenderer,NULL);
        return -1;
    }

    personnage *Kiki = create_personnage();

    SDL_Rect destRect;
    SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h );

    destRect.w = destRect.w /3;
    destRect.h = destRect.h /4;

    Kiki->SpriteWidth = destRect.w;
    Kiki->SpriteHeight = destRect.h;

    Kiki->position_x = (larg_fenetre - destRect.w)/2;
    Kiki->position_y = (haut_fenetre -destRect.h)/2;
    Kiki->vitesse_x = 0;
    Kiki->vitesse_y = 0;


    direction *dir = create_direction();


    int offset = 1;

    while(isOpen){
        while(SDL_PollEvent(&events)){
            switch(events.type){
                case SDL_QUIT:
                    isOpen = false;
                    break;

                case SDL_KEYDOWN:
                    switch(events.key.keysym.scancode){
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            dir->up = true;
                            offset += 1;
                            offset %=3;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            dir->left = true;
                            offset += 1;
                            offset %=3;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            dir->down = true;
                            offset += 1;
                            offset %=3;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            dir->right = true;
                            offset += 1;
                            offset %=3;
                            break;
                        default:
                            break;  
                    }
                    break;

                case SDL_KEYUP:
                    offset = 1;
                    switch(events.key.keysym.scancode){
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            dir->up = false;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            dir->left = false;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            dir->down = false;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            dir->right = false;
                            break;
                        default:
                            break;
                    }
                    break;
                }
            }

        Kiki->vitesse_x = 0;
        Kiki->vitesse_y = 0;

        if (dir->up==true && dir->down==false) {
            Kiki->vitesse_y = -vitesse;
        }
        if (dir->down==true && dir->up==false) {
            Kiki->vitesse_y = vitesse;
        }
        if (dir->left==true && dir->right==false) {
            Kiki->vitesse_x = -vitesse;
        }
        if (dir->left==false && dir->right==true) {
            Kiki->vitesse_x = vitesse;
        }
        
        Kiki->position_x = Kiki->position_x + Kiki->vitesse_x/60;
        Kiki->position_y = Kiki->position_y+ Kiki->vitesse_y/60;


        // pour quand kiki arrive au bord, la suite fais en sorte qu'elle ne sorte pas
        if (Kiki->position_x <= 0){
            Kiki->position_x = 0;
        }
        if (Kiki->position_y <= 0){
            Kiki->position_y = 0;
        }
        if (Kiki->position_x >= larg_fenetre -destRect.w){
            Kiki->position_x = larg_fenetre -destRect.w;
        }
        if (Kiki->position_y >= haut_fenetre - destRect.h){
            Kiki->position_y = haut_fenetre - destRect.h;
        }
        
        destRect.x =  Kiki->position_x;
        destRect.y =  Kiki->position_y;

        SDL_Rect spriteRect = {.x = offset*Kiki->SpriteHeight, .y = 0, .w = Kiki->SpriteWidth, .h= Kiki->SpriteHeight};

        if (dir->right){
            spriteRect.y=2*Kiki->SpriteWidth;
        }
        if (dir->left){
            spriteRect.y=Kiki->SpriteWidth;
        }
        if (dir->up){
            spriteRect.y= 3*Kiki->SpriteWidth;
        }

        SDL_RenderClear(pRenderer);


        SDL_RenderCopy(pRenderer, texture, &spriteRect, &destRect);
        SDL_RenderPresent(pRenderer);


    }


    destroy(pWindow,pRenderer, texture);
    free(dir);
    free(Kiki);
    return 0;
}
