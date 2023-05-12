//
// Created by kabel on 2023.04.23..
//

#ifndef SDL_ATIRAT2_0_BETUKESZLET_H
#define SDL_ATIRAT2_0_BETUKESZLET_H

#include <string>
#include "SDL_TTF_objektum.h"

/// @file Betukeszlet.h A Betukeszlet osztály deklarálása.

namespace SDL {
///    Fontok (betűtípusok) betöltésére használható osztály.

/// A TTF_Font segítségével tölt be true type font betíkészletet.
    class Betukeszlet : private SDL_TTF_objektum{
    private:
///        A fontot tároló TTF_Font pointer.
        TTF_Font* mFont;

    public:
///        Betűkészlet betöltése.

///        @param font A betűkészlet elérési útja és neve.
///        @param betumeret Ebben a méretben tölti be az SDL_ttf a fontot.
        Betukeszlet(const std::string& font, int betumeret);
///        Betűkészlet memóriájának felszabadítása.
        ~Betukeszlet();

///        Egy font csak egyszer szerepeljen a memóriában, ezért nem lehet másolni.
        Betukeszlet(const Betukeszlet&) = delete;
///        Egy font csak egyszer szerepeljen a memóriában, ezért nem lehet másolni.
        Betukeszlet& operator=(const Betukeszlet&) = delete;

///        A háttérben álló TTF_Font típusú pointert adja vissza.
        TTF_Font *getFont(){ return mFont;}
    };

} // SDL

#endif //SDL_ATIRAT2_0_BETUKESZLET_H
