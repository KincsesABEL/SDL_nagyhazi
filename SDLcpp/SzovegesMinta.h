//Kincses Ábel SORHOJ
// Created by kabel on 2023.04.23..
//

#ifndef SDL_ATIRAT2_0_SZOVEGESMINTA_H
#define SDL_ATIRAT2_0_SZOVEGESMINTA_H


#include "SDL_TTF_objektum.h"
#include "Betukeszlet.h"
#include "Ablak.h"

/// @file SzovegesMinta.h A SzovegesMinta osztály deklarálása.

namespace SDL {
/// Feliratok megjelenítése a képernyőn.

/// A Minta objektumhoz hasonló a használata, viszont annál sokkal kevesebbet tud.
    class SzovegesMinta : private SDL_TTF_objektum{
    private:
///        Az ablak, amibe rajzol.
        Ablak& mAblak;

///        A kép tárolója a GPU-n való használatra.
        SDL_Texture* minta;
///        A kép tárolója a CPU-n szerkesztés céljából.
        SDL_Surface* keppontok;

///        A kép szélessége.
        int szelesseg;
///        A kép magassága.
        int magassag;
    public:
///        Szöveges minta létrehozása.

///        @param ablak Az ablak, amibe rajzol. (Később nem változtatható meg!)
        explicit SzovegesMinta(Ablak& ablak);

///        Másoló konstruktor, a kép másolata ugyanabban az ablakban lesz, mint az eredeti.

///        @throws SDL_Error Amikor nem sikerül valami a másoláskor.
        SzovegesMinta(const SzovegesMinta& masik);

///        Minták másolása egymásba.

///        Különböző ablakban lévő mintákra is működik, így érdemes valamit több ablakban is megjeleníteni.
///        @throws SDL_Error Amikor nem sikerül valami a másoláskor.
        SzovegesMinta& operator=(const SzovegesMinta& masik);

///        Ha szükséges, felszabadítja a képnek lefoglalt memóriát.
        ~SzovegesMinta();

///        Szöveg képpé alakítása.

///        @param szoveg A kiírandó felirat.
///        @param betuszin A felirat színe.
///        @param betukeszlet SDL::Betukeszlet típusú előre betöltött font.
///        @throws SDL_Error Amikor nem sikerül a kiírás.
        void kiir(const std::string& szoveg, SDL_Color betuszin, Betukeszlet& betukeszlet);

///        Kép rajzolása a képernyőre

///        @param x X koordináta
///        @param y Y koordináta
///        @param kivagas A kép az a része, amit rajzolni szeretnénk. Ha NULL, akkor az egész.
///        @param forgatasszog Forgatási szög fokban, az óramutató járásával megegyezően.
///        @param vizszintesNyujtas A kép vízszintes nyújtása.
///        @param fuggolegesNyujtas A kép függőleges nyújtása.
///        @param kozeppont Középpont, ami körül forgatjuk.
///        @param tukrozes A tükrözés fajtái: https://wiki.libsdl.org/SDL2/SDL_RendererFlip
        void rajzol(int x, int y, SDL_Rect* kivagas = nullptr, double forgatasszog = .0, double vizszintesNyujtas = 1.0, double fuggolegesNyujtas = 1.0, SDL_Point* kozeppont = nullptr, SDL_RendererFlip tukrozes = SDL_FLIP_NONE);

///        Kitörli a tárolt képet.

///        A destruktor automatikusan meghívja, ezért nem szükséges használni.
        void torol();

///    Színkomponensek megváltoztatására.

///    A kép színeit ezekkel a számokkal felskálázza. Ha r=0, akkor a kép piros pixelei nem fognak megjelenni.
///    Hogyha mindegyik 255, akkor normálisan jelenik meg a kép.
        void setSzinKomponens(Uint8 r, Uint8 g, Uint8 b){ SDL_SetTextureColorMod( minta, r, g, b);}

///    Azt állítja, hogy nem teljesen átlátszó képet hogyan rajzoljon a képernyőre.

///    Több információ: https://wiki.libsdl.org/SDL2/SDL_BlendMode
        void setBlendMode(SDL_BlendMode rajzolas){ SDL_SetTextureBlendMode( minta, rajzolas);}

///        Átlátszóvá tehető a kép.

///        mennyire_atlatszo = 0x00: semennyire - 0xFF: teljesen
        void setAtlatszosag(Uint8 mennyire_atlatszo){ SDL_SetTextureAlphaMod( minta, mennyire_atlatszo);}

///        A kép szélessége.
        [[nodiscard]] int getSzelesseg() const{ return szelesseg;}
///        A kép magassága.
        [[nodiscard]] int getMagassag() const{ return magassag;}
    };

} // SDL

#endif //SDL_ATIRAT2_0_SZOVEGESMINTA_H
