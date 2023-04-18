//Kincses Ábel SORHOJ
// Created by kabel on 2023.04.17..
//

#ifndef SDL_ATIRAT_SDL_OBJEKTUM_H
#define SDL_ATIRAT_SDL_OBJEKTUM_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class SDL_Objektum {
private:
    static int objektumszamlalo;

    static void indit();
    static void bezar();

public:
    SDL_Objektum();
    ~SDL_Objektum();
};


#endif //SDL_ATIRAT_SDL_OBJEKTUM_H
