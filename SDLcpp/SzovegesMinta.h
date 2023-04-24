//
// Created by kabel on 2023.04.23..
//

#ifndef SDL_ATIRAT2_0_SZOVEGESMINTA_H
#define SDL_ATIRAT2_0_SZOVEGESMINTA_H


#include "SDL_TTF_objektum.h"
#include "Betukeszlet.h"
#include "Ablak.h"

namespace SDL {

    class SzovegesMinta : private SDL_TTF_objektum{
    private:
        Ablak& mAblak;

        SDL_Texture* minta;
        SDL_Surface* keppontok;

        int szelesseg;
        int magassag;
    public:
        explicit SzovegesMinta(Ablak& ablak);
        SzovegesMinta(const SzovegesMinta& masik);
        SzovegesMinta& operator=(const SzovegesMinta& masik);
        ~SzovegesMinta();

        void kiir(const std::string& szoveg, SDL_Color betuszin, Betukeszlet& betukeszlet);

        void rajzol(int x, int y, SDL_Rect* kivagas = nullptr, double forgatasszog = .0, double vizszintesNyujtas = 1.0, double fuggolegesNyujtas = 1.0, SDL_Point* kozeppont = nullptr, SDL_RendererFlip tukrozes = SDL_FLIP_NONE);

        void torol();

//    színkomponensek megváltoztatására
        void setSzinKomponens(Uint8 r, Uint8 g, Uint8 b){ SDL_SetTextureColorMod( minta, r, g, b);}

//    azt állítja, hogy nem teljesen átlátszó képet hogyan rajzoljon a képernyőre
        void setBlendMode(SDL_BlendMode rajzolas){ SDL_SetTextureBlendMode( minta, rajzolas);}

        void setAtlatszosag(Uint8 mennyire_atlatszo){ SDL_SetTextureAlphaMod( minta, mennyire_atlatszo);}

        [[nodiscard]] int getSzelesseg() const{ return szelesseg;}
        [[nodiscard]] int getMagassag() const{ return magassag;}
    };

} // SDL

#endif //SDL_ATIRAT2_0_SZOVEGESMINTA_H
