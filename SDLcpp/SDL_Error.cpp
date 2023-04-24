//
// Created by kabel on 2023.04.22..
//

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "SDL_Error.h"

namespace SDL {

    SDL_Error::SDL_Error(const std::string &uzenet) : domain_error(uzenet + " SDL error: " + SDL_GetError()) {

    }
} // SDL