//Kincses Ábel SORHOJ
// Created by kabel on 2023.04.21..
//

#ifndef SDL_ATIRAT2_0_SDL_IMAGE_OBJEKTUM_H
#define SDL_ATIRAT2_0_SDL_IMAGE_OBJEKTUM_H

#ifdef _WIN32
#include <SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

#include "SDL_Objektum.h"

/// @file SDL_image_objektum.h Az SDL_image_objektum osztály deklarálása.

namespace SDL {

///Az SDL_image alrendszereinek indítására szolgál, az összes osztály, ami IMG-t használ, örökli.

/// Mivel automatikusan, és csak egyszer indítja és zárja az SDL_image alrendszereit, ezért minden osztálynak, ami ezt használja, örökölnie kell,
/// különben kétszer hívódik meg az IMG_Init, vagy az IMG_Quit!
    class SDL_image_objektum : private SDL_Objektum {
    private:
///        Számontartja az objektumokat.
        static int objektumszamlalo;

///        Elindítja az SDL_Image-t.

///        @throws SDL_Error Sikertelen indítás esetén.
        static void indit();
///        Bezárja az SDL_Image-t.
        static void bezar();

    public:
///        Az objektum létrehozása.
        SDL_image_objektum();
///        Másoló konstruktor.
        SDL_image_objektum(const SDL_image_objektum&){ objektumszamlalo++;}
///        Az objektum megszüntetése
        ~SDL_image_objektum();
    };

} // SDL

#endif //SDL_ATIRAT2_0_SDL_IMAGE_OBJEKTUM_H
