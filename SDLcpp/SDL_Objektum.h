//
// Created by kabel on 2023.04.21..
//

#ifndef SDL_ATIRAT2_0_SDL_OBJEKTUM_H
#define SDL_ATIRAT2_0_SDL_OBJEKTUM_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

/// @file SDL_Objektum.h Az SDL_Objektum deklarálása.

namespace SDL {
/// Az SDL alrendszereinek indítására szolgál, az összes osztály, ami SDL-t használ, örökli.

/// Fontos, hogy minden SDL-t használó osztály örökölje, különben nem lesz szinkronban az SDL indítása és leállítása.
    class SDL_Objektum {
    private:
///        Számontartja, mennyi objektum használ még SDL-t.
        static int objektumszamlalo;

///        SDL indítása.

///        @throws SDL_Error Sikertelen indítás esetén.
        static void indit();
///        SDL bezárása.
        static void bezar();

    public:
///        Objektum létrehozása.
        SDL_Objektum();
///        Másoló konstruktor.
        SDL_Objektum(const SDL_Objektum&){ objektumszamlalo++;}
        ///        Az objektum megszüntetése
        ~SDL_Objektum();
///        Operator=-ből elég az alapverzió.
    };


} // SDL

#endif //SDL_ATIRAT2_0_SDL_OBJEKTUM_H
