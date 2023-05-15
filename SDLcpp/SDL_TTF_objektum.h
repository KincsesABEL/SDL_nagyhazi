//Kincses Ábel SORHOJ
// Created by kabel on 2023.04.22..
//

#ifndef SDL_ATIRAT2_0_SDL_TTF_OBJEKTUM_H
#define SDL_ATIRAT2_0_SDL_TTF_OBJEKTUM_H

#ifdef _WIN32
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

#include "SDL_Objektum.h"

/// @file SDL_TTF_objektum.h Az SDL_TTF_objektum deklarálása.

namespace SDL {
///Az SDL_ttf alrendszereinek indítására szolgál, az összes osztály, ami TTF-et használ, örökli.

/// Fontos, hogy minden SDL_ttf-et használó osztály örökölje, különben nem lesz szinkronban a TTF indítása és leállítása.
    class SDL_TTF_objektum : SDL_Objektum{
    private:
///        Számontartja, mennyi objektum használ még SDL_ttf-et.
        static int objektumszamlalo;

///        TTF indítása.
        static void indit();
///        TTF leállítása.
        static void bezar();

    public:
///        Objektum létrehozása.
        SDL_TTF_objektum();
///        Objektum másolása
        SDL_TTF_objektum(const SDL_TTF_objektum&){ objektumszamlalo++;}
///        Destruktor.
        ~SDL_TTF_objektum();
    };

} // SDL

#endif //SDL_ATIRAT2_0_SDL_TTF_OBJEKTUM_H
