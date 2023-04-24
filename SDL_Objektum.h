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

namespace SDL {

    class SDL_Objektum {
    private:
        static int objektumszamlalo;

        static void indit();
        static void bezar();

    public:
        SDL_Objektum();
        SDL_Objektum(const SDL_Objektum&){ objektumszamlalo++;}
        ~SDL_Objektum();
//        operator= nem kell
    };


} // SDL

#endif //SDL_ATIRAT2_0_SDL_OBJEKTUM_H
