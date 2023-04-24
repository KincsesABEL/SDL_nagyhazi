//
// Created by kabel on 2023.04.21..
//

#ifndef SDL_ATIRAT2_0_MINTA_H
#define SDL_ATIRAT2_0_MINTA_H


#include "SDL_image_objektum.h"
#include "Ablak.h"

namespace SDL {

    class Minta : private SDL_image_objektum {
    protected:

        Ablak& mAblak;
        SDL_Color hatterszin;

        SDL_Surface* keppontok;
        SDL_Texture* minta;

        int szelesseg;
        int magassag;

        bool frissitesszukseges;

    private:
//        privát pixelelérő függvények
        Uint32 getPixelszelesseg32();
        Uint32* getKeppontok32();

    public:
//        pixelek szerkesztéséhez tartozó segédosztályok
        class Pixeloszlop;
        class RGB_Pixel;

        explicit Minta(Ablak& ablak);
        Minta(const Minta& masik);
        ~Minta();

        Minta& operator=(const Minta& masik);

        void betolt(const std::string& eleresi_ut, SDL_Color hatterszin = {0xFF, 0xFF, 0xFF});

        void JPGmentes(const std::string& nev, int minoseg = 60);
        void PNGmentes(const std::string& nev);

//        ha szerkesztették a kép pixeleit
        void pixelfrissites();

        Pixeloszlop operator[](int x);

        void torol();

        void rajzol(int x, int y, SDL_Rect* kivagas = nullptr, double forgatasszog = .0, double vizszintesNyujtas = 1.0, double fuggolegesNyujtas = 1.0, SDL_Point* kozeppont = nullptr, SDL_RendererFlip tukrozes = SDL_FLIP_NONE);

//    színkomponensek megváltoztatására
        void setSzinKomponens(Uint8 r, Uint8 g, Uint8 b){ SDL_SetTextureColorMod( minta, r, g, b);}

//    azt állítja, hogy nem teljesen átlátszó képet hogyan rajzoljon a képernyőre
        void setBlendMode(SDL_BlendMode rajzolas){ SDL_SetTextureBlendMode( minta, rajzolas);}

        void setAtlatszosag(Uint8 mennyire_atlatszo){ SDL_SetTextureAlphaMod( minta, mennyire_atlatszo);}

        [[nodiscard]] int getSzelesseg() const{ return szelesseg;}
        [[nodiscard]] int getMagassag() const{ return magassag;}
    };

    class Minta::Pixeloszlop{
    public:
        Pixeloszlop(int x, Uint32 pixelszelesseg, int pixelmagassag, Uint32* pixelek, SDL_PixelFormat* formatum);

        RGB_Pixel operator[] (int y);

    private:
        int x;
        Uint32 pixelszelesseg;
        int pixelmagassag;
        Uint32* pixelek;
        SDL_PixelFormat* formatum;
    };

    class Minta::RGB_Pixel{
    private:
        Uint32* szerkesztettpixel;
        SDL_PixelFormat* formatum;

        Uint8 mR, mG, mB;

    public:
        explicit RGB_Pixel(Uint32* szerkesztettpixel, SDL_PixelFormat* formatum);

        RGB_Pixel(const RGB_Pixel&) = delete;

        Minta::RGB_Pixel& operator=(const Minta::RGB_Pixel& masik);
        Minta::RGB_Pixel& operator=(SDL_Color szin);

//        színné lehessen konvertálni
        operator SDL_Color() const;

        [[nodiscard]] Uint8 r()const{return mR;}
        [[nodiscard]] Uint8 g()const{return mG;}
        [[nodiscard]] Uint8 b()const{return mB;}

    };

} // SDL

#endif //SDL_ATIRAT2_0_MINTA_H
