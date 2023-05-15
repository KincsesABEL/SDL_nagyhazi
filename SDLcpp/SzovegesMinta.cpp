//Kincses Ábel SORHOJ
// Created by kabel on 2023.04.23..
//

#include "SzovegesMinta.h"
#include "SDL_Error.h"

namespace SDL {

///  Minden változó nullázása, és az mAblak beállítása.
    SzovegesMinta::SzovegesMinta(Ablak &ablak) : mAblak(ablak){
        minta = nullptr;
        keppontok = nullptr;
        szelesseg = 0;
        magassag = 0;
    }

    void SzovegesMinta::kiir(const std::string& szoveg, SDL_Color betuszin, Betukeszlet &betukeszlet) {
///        Ha nem üres a szöveg, törlés.
        torol();

///        Képpé alakítás a font segítségével,
        SDL_Surface* kiirtkep = TTF_RenderUTF8_Solid(betukeszlet.getFont(), szoveg.c_str(), betuszin);
        if(kiirtkep == nullptr) throw SDL_Error("Nem sikerült képet csinálni a "+ szoveg +" szövegből!");

///        majd texture-ré alakítás,
        minta = SDL_CreateTextureFromSurface(-mAblak, kiirtkep);
        if(minta == nullptr) throw SDL_Error("Nem sikerült mintává alakítani a "+ szoveg +" képét!");

///        végül felkészülés a használatra.
        szelesseg = kiirtkep->w;
        magassag = kiirtkep->h;
        keppontok = kiirtkep;
    }

    void SzovegesMinta::torol() {
        szelesseg = magassag = 0;

///        Minta felszabadítása,
        if(minta != nullptr){
            SDL_DestroyTexture(minta);
            minta = nullptr;
        }
///        és a képpontok felszabadítása.
        if(keppontok != nullptr){
            SDL_FreeSurface(keppontok);
            keppontok = nullptr;
        }
    }

    SzovegesMinta::~SzovegesMinta() {
///        A végén fel kell szabadítani a memóriát.
        torol();
    }

    void SzovegesMinta::rajzol(int x, int y, SDL_Rect *kivagas, double forgatasszog, double vizszintesNyujtas,
                               double fuggolegesNyujtas, SDL_Point *kozeppont, SDL_RendererFlip tukrozes) {

///    A képernyőn lévő helye.
        SDL_Rect celpont = {x, y, szelesseg, magassag};

        if(kivagas != nullptr){
            celpont.w = kivagas->w;
            celpont.h = kivagas->h;

///            Ha a kivágás kilóg a képből, megakadályozzuk a kép akaratlan nyújtását.
            if(kivagas->w + kivagas->x > szelesseg) celpont.w = szelesseg - kivagas->x;
            if(kivagas->h + kivagas->y > magassag) celpont.h = magassag - kivagas->y;
        }


///    Kép nyújtása,
        celpont.w *= vizszintesNyujtas;
        celpont.h *= fuggolegesNyujtas;

///    végül a rajzolás.
        SDL_RenderCopyEx(-mAblak, minta, kivagas, &celpont, forgatasszog, kozeppont, tukrozes);
    }

    SzovegesMinta &SzovegesMinta::operator=(const SzovegesMinta &masik) {
///        Ha nem kell másolni semmit, visszaadjuk a this-t.
        if(this == &masik) return *this;

///        Felszabadítjuk az új képnek a helyet.
        torol();
///        Ha nincs mit kimásolni a másik képből.
        if(masik.keppontok == nullptr) return *this;

///        Először a képpontok átmásolása,
        keppontok = SDL_CreateRGBSurfaceWithFormatFrom(masik.keppontok->pixels, masik.keppontok->w, masik.keppontok->h,
                                                       masik.keppontok->format->BitsPerPixel, masik.keppontok->pitch, masik.keppontok->format->format);
        if(keppontok == nullptr) throw SDL::SDL_Error("Nem sikerült a képet lemásolni!");

///        utána a színpaletta átmásolása jön.
        if(SDL_SetPaletteColors(keppontok->format->palette, masik.keppontok->format->palette->colors, 0, masik.keppontok->format->palette->ncolors) < 0){
            throw SDL_Error("Nem sikerült a színpaletta átmásolása!");
        }

///        A háttérszín átlátszóvá tétele fontos, mert eredetileg ilyen a szöveg képe, csak a  másolásnál ez elromlik.
        SDL_Color hatterszin = keppontok->format->palette->colors[0];
        SDL_SetColorKey(keppontok, SDL_TRUE, SDL_MapRGB(keppontok->format, hatterszin.r, hatterszin.g, hatterszin.b));

///        Végül a texture-ré alakítás következik és
        minta = SDL_CreateTextureFromSurface(-mAblak, keppontok);
        if(minta == nullptr) throw SDL_Error("Másoláskor nem sikerült a mintává alakítás!");

///        felkészülés a további használatra.
        szelesseg = keppontok->w;
        magassag = keppontok->h;

        return *this;
    }

    SzovegesMinta::SzovegesMinta(const SzovegesMinta &masik) : mAblak(masik.mAblak){
///        A szükséges két változót beállítjuk NULL-ra,
        keppontok = nullptr;
        minta = nullptr;

///        így már biztonsággal hívható az operator=.
        *this = masik;
    }
} // SDL