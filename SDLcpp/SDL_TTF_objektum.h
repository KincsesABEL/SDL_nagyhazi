//
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

namespace SDL {

    class SDL_TTF_objektum : SDL_Objektum{
    private:
        static int objektumszamlalo;

        static void indit();
        static void bezar();

    public:
        SDL_TTF_objektum();
        SDL_TTF_objektum(const SDL_TTF_objektum&){ objektumszamlalo++;}
        ~SDL_TTF_objektum();
    };

} // SDL

#endif //SDL_ATIRAT2_0_SDL_TTF_OBJEKTUM_H
