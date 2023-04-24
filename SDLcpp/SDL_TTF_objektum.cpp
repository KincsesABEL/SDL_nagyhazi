//
// Created by kabel on 2023.04.22..
//

#include "SDL_TTF_objektum.h"
#include "SDL_Error.h"

namespace SDL {
    int SDL_TTF_objektum::objektumszamlalo = 0;

    void SDL_TTF_objektum::indit() {
//        SDLttf indítása
        if(TTF_Init() == -1){
            throw SDL_Error("SDL ttf nem tudott elindulni!");
        }

    }

    void SDL_TTF_objektum::bezar() {
//        kilépés a ttf-ből
        TTF_Quit();
    }

    SDL_TTF_objektum::SDL_TTF_objektum() {
        if(objektumszamlalo == 0) indit();

        objektumszamlalo++;
    }

    SDL_TTF_objektum::~SDL_TTF_objektum() {
        objektumszamlalo--;

        if(objektumszamlalo == 0) bezar();
    }
} // SDL