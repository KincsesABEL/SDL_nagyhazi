//
// Created by kabel on 2023.04.21..
//

#include "SDL_Error.h"
#include "Minta.h"

namespace SDL {
    Minta::Minta(Ablak &ablak) : mAblak(ablak) {
        minta = nullptr;
        keppontok = nullptr;
        szelesseg = magassag = 0;
        frissitesszukseges = false;
    }

    void Minta::betolt(const std::string &eleresi_ut, SDL_Color hatterszin) {
//    előző törlése
        torol();

//    új kép helye
        SDL_Texture *ujminta;
        keppontok = IMG_Load(eleresi_ut.c_str());

        if(keppontok == nullptr) throw SDL::SDL_Error("Nem sikerült betölteni a " + eleresi_ut + " képet!");

//        képpontok felkészítése az esetleges felülírásra
        keppontok = SDL_ConvertSurfaceFormat(keppontok, SDL_GetWindowPixelFormat(mAblak.getAblakPointer()), 0);
        if(keppontok == nullptr) throw SDL::SDL_Error("Nem sikerült a " + eleresi_ut + " pixeljeit konvertálni!");

//        háttérszín átlátszóvá tétele
        SDL_SetColorKey(keppontok, SDL_TRUE, SDL_MapRGB(keppontok->format, hatterszin.r, hatterszin.g, hatterszin.b));

//    mintakészítés a betöltött fájlból
        ujminta = SDL_CreateTextureFromSurface(-mAblak, keppontok);
        if(ujminta == nullptr) throw SDL::SDL_Error("Nem sikerült mintát csinálni a " + eleresi_ut + " képből!");

//    további használatra felkészülés
        szelesseg = keppontok->w;
        magassag = keppontok->h;

        this->hatterszin = hatterszin;
        frissitesszukseges = false;

        minta = ujminta;
    }

    void Minta::torol() {
        szelesseg = magassag = 0;

        if(minta != nullptr){
//        kitöröljük az elmentett képet
            SDL_DestroyTexture(minta);
            minta = nullptr;
        }

        if(keppontok != nullptr){
            SDL_FreeSurface(keppontok);
            keppontok = nullptr;
        }
    }

    void
    Minta::rajzol(int x, int y, SDL_Rect *kivagas, double forgatasszog, double vizszintesNyujtas, double fuggolegesNyujtas,
                  SDL_Point *kozeppont, SDL_RendererFlip tukrozes) {

        if(frissitesszukseges) pixelfrissites();

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

    Minta::~Minta() {
        torol();
    }

    void Minta::pixelfrissites() {
        frissitesszukseges = false;

//        ha nincs miből frissíteni
        if(keppontok == nullptr) return;

//        háttérszín átlátszóvá tétele
        SDL_SetColorKey(keppontok, SDL_TRUE, SDL_MapRGB(keppontok->format, hatterszin.r, hatterszin.g, hatterszin.b));

//        frissítjük a texture-t
        minta = SDL_CreateTextureFromSurface(-mAblak, keppontok);
        if(minta == nullptr) throw SDL::SDL_Error("Nem sikerült mintát csinálni a pixelekből!");
    }

    Uint32 Minta::getPixelszelesseg32() {
        if(keppontok == nullptr) return 0;

        return keppontok->pitch/4;
    }

    Uint32 *Minta::getKeppontok32() {
        if(keppontok == nullptr) return nullptr;

        return static_cast<Uint32 *>(keppontok->pixels);
    }

    Minta::Pixeloszlop Minta::operator[](int x) {
//        ha rossz a koordináta, NULL-al adjuk át
        if(x < 0 || x >= szelesseg) return {x, getPixelszelesseg32(), magassag, nullptr, SDL_GetWindowSurface(mAblak.getAblakPointer())->format};

        frissitesszukseges = true;
        return {x, getPixelszelesseg32(), magassag, getKeppontok32(), SDL_GetWindowSurface(mAblak.getAblakPointer())->format};
    }

    void Minta::JPGmentes(const std::string &nev, int minoseg) {
        if(keppontok == nullptr) return;
//        pixelek mentése
        if(IMG_SaveJPG(keppontok, nev.c_str(), minoseg) < 0){
            throw SDL::SDL_Error("Nem sikerült elmenteni a " + nev + "képet!");
        }

    }

//    a másolás csak a képet másolja, az ablak nem lesz más
    Minta &Minta::operator=(const Minta &masik) {
//        ha ugyanazok, nem másolunk, mert abból baj lesz
        if(this == &masik) return *this;

        torol();
//        ha nincs mit másolni
        if(masik.keppontok == nullptr) return *this;

//        képpontok átmásolása
        keppontok = SDL_CreateRGBSurfaceFrom(masik.keppontok->pixels, masik.keppontok->w, masik.keppontok->h,
                                             32, masik.keppontok->pitch, 0, 0, 0, 0);

        if(keppontok == nullptr) throw SDL::SDL_Error("Nem sikerült a képet lemásolni!");

//        képpontok felkészítése az esetleges felülírásra
        keppontok = SDL_ConvertSurfaceFormat(keppontok, SDL_GetWindowPixelFormat(mAblak.getAblakPointer()), 0);
        if(keppontok == nullptr) throw SDL::SDL_Error("Másolásnál nem sikerült a kép pixeljeit konvertálni!");

//        használatra felkészítés
        szelesseg = keppontok->w;
        magassag = keppontok->h;
        hatterszin = masik.hatterszin;

        pixelfrissites();

        return *this;
    }

    Minta::Minta(const Minta &masik) : mAblak(masik.mAblak){
//        alapértékek átmásolása
        minta = nullptr;
        keppontok = nullptr;
        szelesseg = magassag = 0;

        *this = masik;
    }

    void Minta::PNGmentes(const std::string &nev) {
        if(keppontok == nullptr) return;
//        pixelek mentése
        if(IMG_SavePNG(keppontok, nev.c_str()) < 0){
            throw SDL::SDL_Error("Nem sikerült elmenteni a " + nev + "képet!");
        }
    }

    Minta::Pixeloszlop::Pixeloszlop(int x, Uint32 pixelszelesseg, int pixelmagassag, Uint32 *pixelek, SDL_PixelFormat* formatum) {
        this->x = x;
        this->pixelszelesseg = pixelszelesseg;
        this->pixelmagassag = pixelmagassag;
        this->pixelek = pixelek;
        this->formatum = formatum;
    }

    Minta::RGB_Pixel Minta::Pixeloszlop::operator[](int y) {
//        ha rossz a koordináta, nem csinál semmit
        if(y < 0 || y >= pixelmagassag || pixelek == nullptr) return Minta::RGB_Pixel(nullptr, formatum);
        return Minta::RGB_Pixel(&pixelek[y * pixelszelesseg + x], formatum);
    }

    Minta::RGB_Pixel::RGB_Pixel(Uint32 *szerkesztettpixel, SDL_PixelFormat* formatum) {
        this->szerkesztettpixel = szerkesztettpixel;
        this->formatum = formatum;

//        ha nem létezik a pixel, nem csinál semmit
        if(szerkesztettpixel != nullptr) {
            SDL_GetRGB(*szerkesztettpixel, formatum, &mR, &mG, &mB);
        }
    }

    Minta::RGB_Pixel &Minta::RGB_Pixel::operator=(SDL_Color szin) {
        mR = szin.r;
        mG = szin.g;
        mB = szin.b;

//        színek szerkesztése
        if(szerkesztettpixel != nullptr) {
            *szerkesztettpixel = SDL_MapRGB(formatum, mR, mG, mB);
        }

        return *this;
    }

    Minta::RGB_Pixel::operator SDL_Color() const {
        return {mR, mG, mB};
    }

    Minta::RGB_Pixel &Minta::RGB_Pixel::operator=(const Minta::RGB_Pixel &masik) {
        mR = masik.mR;
        mG = masik.mG;
        mB = masik.mB;
//        színek szerkesztése
        if(szerkesztettpixel != nullptr) {
            *szerkesztettpixel = SDL_MapRGB(formatum, mR, mG, mB);
        }
    }
} // SDL