//
// Created by kabel on 2023.04.21..
//

#include "SDL_image_objektum.h"
#include "SDL_Error.h"

namespace SDL {
    int SDL_image_objektum::objektumszamlalo = 0;

    void SDL_image_objektum::indit() {
        int sdl_image_flagek = IMG_INIT_PNG | IMG_INIT_JPG;
        if(!(IMG_Init(sdl_image_flagek) & sdl_image_flagek )){
            throw SDL::SDL_Error("SDL image nem tudott elindulni!");
        }
    }

    void SDL_image_objektum::bezar() {
        IMG_Quit();
    }

    SDL_image_objektum::SDL_image_objektum() {
        if(objektumszamlalo == 0) indit();

        objektumszamlalo++;
    }

    SDL_image_objektum::~SDL_image_objektum() {
        objektumszamlalo--;

        if(objektumszamlalo == 0) bezar();
    }
} // SDL