//
// Created by kabel on 2023.04.21..
//

#include "SDL_Objektum.h"
#include "SDL_Error.h"

namespace SDL {
    int SDL_Objektum::objektumszamlalo = 0;

    void SDL_Objektum::indit() {
///        Az SDL indítása.
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
            throw SDL::SDL_Error("SDL nem tudott elindulni!");
        }

///        Optimalizálási lehetőség, csak warning, ha nem sikerült beállítani.
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            SDL_Log("W: lineáris képszűrés nem engedélyezett\n");
        }
    }

    void SDL_Objektum::bezar() {
        SDL_Quit();
    }

/// Az első class indítja az SDL-t.
    SDL_Objektum::SDL_Objektum() {
        if(objektumszamlalo == 0) indit();

        objektumszamlalo++;
    }

/// Az utolsó pedig kilép belőle.
    SDL_Objektum::~SDL_Objektum() {
        objektumszamlalo--;

        if(objektumszamlalo == 0) bezar();
    }
} // SDL