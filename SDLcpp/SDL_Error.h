//
// Created by kabel on 2023.04.22..
//

#ifndef SDL_ATIRAT2_0_SDL_ERROR_H
#define SDL_ATIRAT2_0_SDL_ERROR_H

#include <stdexcept>
#include <string>

/// @file SDL_Error.h Az SDL_Error osztály deklarálása.

namespace SDL {
///    Csak SDL specifikus error dobására.

///    Automatikusan hívja az SDL_GetError()-t, ezért CSAK AKKOR dobjuk, ha valamely SDL függvény hibával tért vissza. Ezen kívül teljesen domain_error.
    class SDL_Error : public std::domain_error{
    public:
///        Error dobása üzenettel.

///        @param uzenet Az üzenet, ami tartalmazza, hogy mi lehet a hiba oka.
        explicit SDL_Error(const std::string &uzenet);
    };

} // SDL

#endif //SDL_ATIRAT2_0_SDL_ERROR_H
