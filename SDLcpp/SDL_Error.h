//
// Created by kabel on 2023.04.22..
//

#ifndef SDL_ATIRAT2_0_SDL_ERROR_H
#define SDL_ATIRAT2_0_SDL_ERROR_H

#include <stdexcept>
#include <string>

namespace SDL {

//    Automatikusan hívja az SDL_GetError()-t ezért csak akkor dobjuk, ha valamely SDL függvény hibával tért vissza. Ezen kívül teljesen domain_error.
    class SDL_Error : public std::domain_error{
    public:
        explicit SDL_Error(const std::string &uzenet);
    };

} // SDL

#endif //SDL_ATIRAT2_0_SDL_ERROR_H
