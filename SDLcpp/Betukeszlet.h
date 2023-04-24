//
// Created by kabel on 2023.04.23..
//

#ifndef SDL_ATIRAT2_0_BETUKESZLET_H
#define SDL_ATIRAT2_0_BETUKESZLET_H

#include <string>
#include <map>
#include "SDL_TTF_objektum.h"

namespace SDL {

    class Betukeszlet : private SDL_TTF_objektum{
    private:
        TTF_Font* mFont;

    public:
        Betukeszlet(const std::string& font, int betumeret);
        ~Betukeszlet();

//        hogy csak egyszer zárjuk be az elején megnyitott fontot
        Betukeszlet(const Betukeszlet&) = delete;
        Betukeszlet& operator=(const Betukeszlet&) = delete;

        TTF_Font *getFont(){ return mFont;}
    };

} // SDL

#endif //SDL_ATIRAT2_0_BETUKESZLET_H
