#include "sounds.h"

/* event = "main_menu", "overworld", ... -> faire correspondre les noms de fichiers sans '.ogg'
lance le son à l'inf et renvoie 0 si tt va bien ou 1 si y'a eu un problème */
Mix_Music* loadBGmusic(char* event) {
    Mix_Music* music = NULL ;
    char file[40] = "" ; char* beg = "./audio/BGM/" ; char* end = ".ogg" ;
    strcat(file, beg) ;
    strcat(file, event) ;
    strcat(file, end) ;
    // printf("\n%s\n\n", file) ;
    music = Mix_LoadMUS(file); 
    if (music == NULL) {
        printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
    }

    // Play the sound effect
    Mix_PlayMusic(music, -1);
    return music ;
}

/* `char* event` = "bump", "Kiki_dialogue", "Tutoriel_Dialogue", ... -> faire correspondre les noms de fichiers sans '.ogg'
renvoie 0 si tt va bien ou 1 si y'a eu un problème */
Mix_Chunk* loadSoundEffect(char* event) {
    Mix_Chunk* sound = NULL ;
    char file[40] = "" ; char* beg = "./audio/SE/" ; char* end = ".ogg" ;
    strcat(file, beg) ;
    strcat(file, event) ;
    strcat(file, end) ;
    // printf("\n%s\n\n", file) ;
    sound = Mix_LoadWAV(file); 
    if (sound == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    return sound ;
}
