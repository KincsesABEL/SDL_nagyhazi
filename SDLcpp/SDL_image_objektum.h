//
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

namespace SDL {

    class SDL_image_objektum : private SDL_Objektum {
    private:
        static int objektumszamlalo;

        static void indit();
        static void bezar();

    public:
        SDL_image_objektum();
        SDL_image_objektum(const SDL_image_objektum&){ objektumszamlalo++;}
        ~SDL_image_objektum();
    };

} // SDL

#endif //SDL_ATIRAT2_0_SDL_IMAGE_OBJEKTUM_H
