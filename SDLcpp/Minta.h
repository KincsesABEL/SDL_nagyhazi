//
// Created by kabel on 2023.04.21..
//

#ifndef SDL_ATIRAT2_0_MINTA_H
#define SDL_ATIRAT2_0_MINTA_H


#include "SDL_image_objektum.h"
#include "Ablak.h"

/// @file Minta.h A Minta osztály deklarálása.

namespace SDL {

/// Képek betöltése és szerkesztése.

/// JPG és PNG típusú képeket lehet betölteni, szerkeszteni, és elmenteni vele.
    class Minta : private SDL_image_objektum {
    private:
///        Az ablak, amibe rajzol.
        Ablak& mAblak;
///        Az átlátszóvá tett háttérszín.
        SDL_Color hatterszin;

///        A kép tárolója a CPU-n szerkesztés céljából.
        SDL_Surface* keppontok;
///        A kép tárolója a GPU-n való használatra.
        SDL_Texture* minta;

///        A kép szélessége.
        int szelesseg;
///        A kép magassága.
        int magassag;

///        Jelzi, hogy frissíteni kell-e a GPU-n a texture-t.
        bool frissitesszukseges;

///        A memóriában levő pontok tárolási szélessége.
        Uint32 getPixelszelesseg32();
///        A memóriában levő Uint32 típusú képpontok helye.
        Uint32* getKeppontok32();

    public:
///        Pixelek szerkesztéséhez tartozó segédosztály.
        class Pixeloszlop;
///        Pixelek szerkesztéséhez tartozó segédosztály.
        class RGB_Pixel;

///        Minta objektum létrehozása.

///        @param ablak Az ablak, amibe rajzol. (Később nem változtatható meg!)
        explicit Minta(Ablak& ablak);

///        Másoló konstruktor, a kép másolata ugyanabban az ablakban lesz, mint az eredeti.
        Minta(const Minta& masik);

///        Ha szükséges, felszabadítja a képnek lefoglalt memóriát.
        ~Minta();

///        Minták másolása egymásba.

///        Különböző ablakban lévő mintákra is működik, így érdemes valamit több ablakban is megjeleníteni.
        Minta& operator=(const Minta& masik);

///        Kép betöltése. (JPG vagy PNG)

///        @param eleresi_ut A kép neve (elérési úttal, ha más mappában található).
///        @param hatterszin Ez a szín átlátszóvá lesz kódolva, nem lesz látható.
///        @throws SDL_Error Amikor nem sikerül betölteni a képet.
        void betolt(const std::string& eleresi_ut, SDL_Color hatterszin = {0xFF, 0xFF, 0xFF});

///        Kép mentése JPG formátumban.

///        @param nev A fájl neve (esetleges elérési úttal).
///        @param minoseg A kép minősége 0-100-ig terjedő skálán (jpg tömörítés).
///        @throws SDL::SDL_Error Ha nem sikerült a mentés.
        void JPGmentes(const std::string& nev, int minoseg = 60);

///        Kép mentése PNG formátumban.

///        @param nev A fájl neve (esetleges elérési úttal).
///        @throws SDL::SDL_Error Ha nem sikerült a mentés.
        void PNGmentes(const std::string& nev);

///        Ha szerkesztették a kép pixeleit, rajzoláskor automatikusan frissíti a mintát a GPU-n.
        void pixelfrissites();

///        Kép pixeljeinek elérése.

///        Ha rossz a koordináta, nem történik semmi baj.
///        @param x A szerkeszteni kívánt pixel x koordinátája a képben.
        Pixeloszlop operator[](int x);

///        Kitörli a tárolt képet.

///        A destruktor automatikusan meghívja, ezért nem szükséges használni.
        void torol();

///        Kép rajzolása a képernyőre

///        @param x X koordináta
///        @param y Y koordináta
///        @param kivagas A kép az a része, amit rajzolni szeretnénk. Ha NULL, akkor az egész.
///        @param forgatasszog Forgatási szög fokban, az óramutató járásával megegyezően.
///        @param vizszintesNyujtas A kép vízszintes nyújtása.
///        @param fuggolegesNyujtas A kép függőleges nyújtása.
///        @param kozeppont Középpont, ami körül forgatjuk.
///        @param tukrozes A tükrözés fajtái: https://wiki.libsdl.org/SDL2/SDL_RendererFlip
        void rajzol(int x, int y, SDL_Rect* kivagas = nullptr, double forgatasszog = .0, double vizszintesNyujtas = 1.0,
                    double fuggolegesNyujtas = 1.0, SDL_Point* kozeppont = nullptr, SDL_RendererFlip tukrozes = SDL_FLIP_NONE);

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

///        A kép szélessége
        [[nodiscard]] int getSzelesseg() const{ return szelesseg;}
///        A kép magassága
        [[nodiscard]] int getMagassag() const{ return magassag;}
    };

///    Egyetlen konstruktora és operátor[] tagfüggvénye van, ahol az adott pixel y koordinátáját kell megadni.
    class Minta::Pixeloszlop{
    public:

///        Pixeloszlop létrehozása.

///        @param x Az előzőleg beírt, és ellenőrzött X koordináta a képen.
///        @param pixelszelesseg A képnek foglalt terület jellemzője a memóriában, általában egy kicsit nagyobb, mint a kép szélessége.
///        @param pixelmagassag A kép magassága.
///        @param pixelek A kép pixeljeinek helye a memóriában.
///        @param formatum A kép Pixeljeinek tárolási formátuma.
        Pixeloszlop(int x, Uint32 pixelszelesseg, int pixelmagassag, Uint32* pixelek, SDL_PixelFormat* formatum);

///        Kép pixeljeinek elérése.

///        Ha rossz a koordináta, nem történik semmi baj.
///        @param y A szerkeszteni kívánt pixel y koordinátája a képben.
        RGB_Pixel operator[] (int y);

    private:
///        A képpont x koordinátája.
        int x;
///        A memóriában foglalt kép szélessége.
        Uint32 pixelszelesseg;
///        A kép magassága.
        int pixelmagassag;
///        A memóriában levő Uint32 típusú képpontok helye.
        Uint32* pixelek;
///        A képpontok tárolásának formátuma.
        SDL_PixelFormat* formatum;
    };

///    SDL_Color típussá alakítható, és azzal állitható be.
    class Minta::RGB_Pixel{
    private:
///        Az osztály által szerkesztett pixel helye a memóriában.
        Uint32* szerkesztettpixel;
///        A pixel tárolási formátuma.
        SDL_PixelFormat* formatum;

///        A pixel RGB adatainak tárolása kiolvasás után.
        Uint8 mR, mG, mB;

    public:
///        RGB_Pixel létrehozása.

///        @param szerkesztettpixel A szerkeszteni kívánt pixel helye a memóriában.
///        @param formatum A pixel tárolási formátuma.
        explicit RGB_Pixel(Uint32* szerkesztettpixel, SDL_PixelFormat* formatum);

///        Nincs szükség a másoló konstruktorra.
        RGB_Pixel(const RGB_Pixel&) = delete;
        /*RGB_Pixel(RGB_Pixel&&) = delete;
        Minta::RGB_Pixel& operator=(Minta::RGB_Pixel&&) = delete;*/

///        Pixelek közvetlen másolására.

///        Másoláskor a pixel azonnal megváltozik.
        Minta::RGB_Pixel& operator=(const Minta::RGB_Pixel& masik);

///        Pixelek színének beállítására.

///        Ekkor a pixel a memóriában azonnal megváltozik.
        Minta::RGB_Pixel& operator=(SDL_Color szin);

///        Színné lehet konvertálni.
        operator SDL_Color() const;

///        Pixel piros komponense.
        [[nodiscard]] Uint8 r()const{return mR;}
///        Pixel zöld komponense.
        [[nodiscard]] Uint8 g()const{return mG;}
///        Pixel kék komponense.
        [[nodiscard]] Uint8 b()const{return mB;}

    };

} // SDL

#endif //SDL_ATIRAT2_0_MINTA_H
