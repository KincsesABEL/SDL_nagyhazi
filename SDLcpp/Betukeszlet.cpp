//
// Created by kabel on 2023.04.23..
//

#include "Betukeszlet.h"
#include "SDL_Error.h"

namespace SDL {
    Betukeszlet::Betukeszlet(const std::string& font, int betumeret) {
//        font betöltése
        mFont = TTF_OpenFont(font.c_str(), betumeret);

        if(mFont == nullptr) throw SDL_Error("Nem sikerült megnyitni a " + font + " betűkészletet!");
    }

    Betukeszlet::~Betukeszlet() {
//        font bezárása
        TTF_CloseFont(mFont);

    }
} // SDL