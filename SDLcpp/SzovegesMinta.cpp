//
// Created by kabel on 2023.04.23..
//

#include "SzovegesMinta.h"
#include "SDL_Error.h"

namespace SDL {

    SzovegesMinta::SzovegesMinta(Ablak &ablak) : mAblak(ablak){
        minta = nullptr;
        keppontok = nullptr;
        szelesseg = 0;
        magassag = 0;
    }

    void SzovegesMinta::kiir(const std::string& szoveg, SDL_Color betuszin, Betukeszlet &betukeszlet) {
        torol();

//        képpé alakítás a font segítségével
        SDL_Surface* kiirtkep = TTF_RenderUTF8_Solid(betukeszlet.getFont(), szoveg.c_str(), betuszin);
        if(kiirtkep == nullptr) throw SDL_Error("Nem sikerült képet csinálni a "+ szoveg +" szövegből!");

//        texture-ré alakítás
        minta = SDL_CreateTextureFromSurface(-mAblak, kiirtkep);
        if(minta == nullptr) throw SDL_Error("Nem sikerült mintává alakítani a "+ szoveg +" képét!");

//        felkészülés a használatra
        szelesseg = kiirtkep->w;
        magassag = kiirtkep->h;
        keppontok = kiirtkep;
    }

    void SzovegesMinta::torol() {
        szelesseg = magassag = 0;

//        minta felszabadítása
        if(minta != nullptr){
            SDL_DestroyTexture(minta);
            minta = nullptr;
        }
//        képpontok felszabadítása
        if(keppontok != nullptr){
            SDL_FreeSurface(keppontok);
            keppontok = nullptr;
        }
    }

    SzovegesMinta::~SzovegesMinta() {
        torol();
    }

    void SzovegesMinta::rajzol(int x, int y, SDL_Rect *kivagas, double forgatasszog, double vizszintesNyujtas,
                               double fuggolegesNyujtas, SDL_Point *kozeppont, SDL_RendererFlip tukrozes) {

//    a képernyőn lévő helye
        SDL_Rect celpont = {x, y, szelesseg, magassag};

        if(kivagas != nullptr){
            celpont.w = kivagas->w;
            celpont.h = kivagas->h;

//            ha a kivágás kilóg a képből, megakadályozzuk a kép akaratlan nyújtását
            if(kivagas->w + kivagas->x > szelesseg) celpont.w = szelesseg - kivagas->x;
            if(kivagas->h + kivagas->y > magassag) celpont.h = magassag - kivagas->y;
        }


//    kép nyújtása
        celpont.w *= vizszintesNyujtas;
        celpont.h *= fuggolegesNyujtas;

//    rajzolás
        SDL_RenderCopyEx(-mAblak, minta, kivagas, &celpont, forgatasszog, kozeppont, tukrozes);
    }

    SzovegesMinta &SzovegesMinta::operator=(const SzovegesMinta &masik) {
        if(this == &masik) return *this;

        torol();
//        ha nincs mit másolni
        if(masik.keppontok == nullptr) return *this;

//        képpontok átmásolása
        keppontok = SDL_CreateRGBSurfaceWithFormatFrom(masik.keppontok->pixels, masik.keppontok->w, masik.keppontok->h,
                                                       masik.keppontok->format->BitsPerPixel, masik.keppontok->pitch, masik.keppontok->format->format);
        if(keppontok == nullptr) throw SDL::SDL_Error("Nem sikerült a képet lemásolni!");

//        színpaletta átmásolása
        if(SDL_SetPaletteColors(keppontok->format->palette, masik.keppontok->format->palette->colors, 0, masik.keppontok->format->palette->ncolors) < 0){
            throw SDL_Error("Nem sikerült a színpaletta átmásolása!");
        }

        //        háttérszín átlátszóvá tétele
        SDL_Color hatterszin = keppontok->format->palette->colors[0];
        SDL_SetColorKey(keppontok, SDL_TRUE, SDL_MapRGB(keppontok->format, hatterszin.r, hatterszin.g, hatterszin.b));

        //        texture-ré alakítás
        minta = SDL_CreateTextureFromSurface(-mAblak, keppontok);
        if(minta == nullptr) throw SDL_Error("Másoláskor nem sikerült a mintává alakítás!");

//        felkészülés a használatra
        szelesseg = keppontok->w;
        magassag = keppontok->h;

        return *this;
    }

    SzovegesMinta::SzovegesMinta(const SzovegesMinta &masik) : mAblak(masik.mAblak){
        keppontok = nullptr;
        minta = nullptr;

        *this = masik;
    }
} // SDL