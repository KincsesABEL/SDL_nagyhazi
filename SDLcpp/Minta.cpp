//Kincses Ábel SORHOJ
// Created by kabel on 2023.04.21..
//

#include "SDL_Error.h"
#include "Minta.h"

namespace SDL {
///  Minden változó nullázása, és az mAblak beállítása.
    Minta::Minta(Ablak &ablak) : mAblak(ablak) {
        minta = nullptr;
        keppontok = nullptr;
        szelesseg = magassag = 0;
        frissitesszukseges = false;
    }

    void Minta::betolt(const std::string &eleresi_ut, SDL_Color hatterszin) {
///        Ha nem üres a szöveg, törlés.
        torol();

///    Az új minta helye.
        SDL_Texture *ujminta;
///        Betöltés SDL_image segítségével.
        keppontok = IMG_Load(eleresi_ut.c_str());

        if(keppontok == nullptr) throw SDL::SDL_Error("Nem sikerült betölteni a " + eleresi_ut + " képet!");

///        A képpontok felkészítése az esetleges felülírásra.
        keppontok = SDL_ConvertSurfaceFormat(keppontok, SDL_GetWindowPixelFormat(mAblak.getAblakPointer()), 0);
        if(keppontok == nullptr) throw SDL::SDL_Error("Nem sikerült a " + eleresi_ut + " pixeljeit konvertálni!");

///        Háttérszín átlátszóvá tétele.
        SDL_SetColorKey(keppontok, SDL_TRUE, SDL_MapRGB(keppontok->format, hatterszin.r, hatterszin.g, hatterszin.b));

///    Mintakészítés a betöltött fájlból, hogy a GPU gyorsan tudja rajzolni a képernyőre,
        ujminta = SDL_CreateTextureFromSurface(-mAblak, keppontok);
        if(ujminta == nullptr) throw SDL::SDL_Error("Nem sikerült mintát csinálni a " + eleresi_ut + " képből!");

///    és a további használatra való felkészülés.
        szelesseg = keppontok->w;
        magassag = keppontok->h;

        this->hatterszin = hatterszin;
        frissitesszukseges = false;

        minta = ujminta;
    }

    void Minta::torol() {
        szelesseg = magassag = 0;

        if(minta != nullptr){
///        Minta felszabadítása,
            SDL_DestroyTexture(minta);
            minta = nullptr;
        }

///        és a képpontok felszabadítása.
        if(keppontok != nullptr){
            SDL_FreeSurface(keppontok);
            keppontok = nullptr;
        }
    }

    void
    Minta::rajzol(int x, int y, SDL_Rect *kivagas, double forgatasszog, double vizszintesNyujtas, double fuggolegesNyujtas,
                  SDL_Point *kozeppont, SDL_RendererFlip tukrozes) {

///        Ha szerkesztették a pixeljeit, akkor frissítjük a GPU-n levő változatot.
        if(frissitesszukseges) pixelfrissites();

///    A képernyőn lévő helye a képnek.
        SDL_Rect celpont = {x, y, szelesseg, magassag};

        if(kivagas != nullptr){
            celpont.w = kivagas->w;
            celpont.h = kivagas->h;

///            Ha a kivágás kilóg a képből, megakadályozzuk a kép akaratlan nyújtását.
            if(kivagas->w + kivagas->x > szelesseg) celpont.w = szelesseg - kivagas->x;
            if(kivagas->h + kivagas->y > magassag) celpont.h = magassag - kivagas->y;
        }


///    A kép nyújtása,
        celpont.w *= vizszintesNyujtas;
        celpont.h *= fuggolegesNyujtas;

///    végül a rajzolás.
        SDL_RenderCopyEx(-mAblak, minta, kivagas, &celpont, forgatasszog, kozeppont, tukrozes);
    }

    Minta::~Minta() {
///        Törlés, hogy ne maradjon kép a memóriában.
        torol();
    }

    void Minta::pixelfrissites() {
///        Flag visszaállítása.
        frissitesszukseges = false;

///        Ha nincs miből frissíteni.
        if(keppontok == nullptr) return;

///        Háttérszín átlátszóvá tétele.
        SDL_SetColorKey(keppontok, SDL_TRUE, SDL_MapRGB(keppontok->format, hatterszin.r, hatterszin.g, hatterszin.b));

///        Frissítjük a texture-t.
        minta = SDL_CreateTextureFromSurface(-mAblak, keppontok);
        if(minta == nullptr) throw SDL::SDL_Error("Nem sikerült mintát csinálni a pixelekből!");
    }

    Uint32 Minta::getPixelszelesseg32() {
        if(keppontok == nullptr) return 0;

///        Mivel a pitch byte-ban adja meg, és a típus (Uint32) 32 bites, ezért osztani kell néggyel.
        return keppontok->pitch/4;
    }

    Uint32 *Minta::getKeppontok32() {
        if(keppontok == nullptr) return nullptr;

///        A void*-ot visszaalakítjuk rendes típussá.
        return (Uint32*) keppontok->pixels;
    }

    Minta::Pixeloszlop Minta::operator[](int x) {
///        Ha rossz a koordináta, NULL-al adjuk át.
        if(x < 0 || x >= szelesseg) return {x, getPixelszelesseg32(), magassag, nullptr, SDL_GetWindowSurface(mAblak.getAblakPointer())->format};

///        Különben szerkszthetik a pixelt, szóval frissíteni kell majd a képet.
        frissitesszukseges = true;
        return {x, getPixelszelesseg32(), magassag, getKeppontok32(), SDL_GetWindowSurface(mAblak.getAblakPointer())->format};
    }

    void Minta::JPGmentes(const std::string &nev, int minoseg) {

        if(keppontok == nullptr) {
///            Egy warningot kiírunk, ha nincs mit elmenteni, de a program azért ne haljon meg.
            SDL_Log("W: Nincs mit elmenteni!\n");
            return;
        }
///        Pixelek mentése.
        if(IMG_SaveJPG(keppontok, nev.c_str(), minoseg) < 0){
            throw SDL::SDL_Error("Nem sikerült elmenteni a " + nev + " képet!");
        }

    }

///    A másolás csak a képet másolja, az ablak nem lesz más.
    Minta &Minta::operator=(const Minta &masik) {
///        Ha ugyanazok, nem másolunk, mert abból baj lesz.
        if(this == &masik) return *this;

///        Törlés a memória felszabadításához.
        torol();
///        Ha nincs mit másolni, nem csinálunk semmit.
        if(masik.keppontok == nullptr) return *this;

///        A képpontok átmásolása,
        keppontok = SDL_CreateRGBSurfaceFrom(masik.keppontok->pixels, masik.keppontok->w, masik.keppontok->h,
                                             32, masik.keppontok->pitch, 0, 0, 0, 0);

        if(keppontok == nullptr) throw SDL::SDL_Error("Nem sikerült a képet lemásolni!");

///        utána a képpontok felkészítése az esetleges felülírásra
        keppontok = SDL_ConvertSurfaceFormat(keppontok, SDL_GetWindowPixelFormat(mAblak.getAblakPointer()), 0);
        if(keppontok == nullptr) throw SDL::SDL_Error("Másolásnál nem sikerült a kép pixeljeit konvertálni!");

///        végül a használatra való felkészítés.
        szelesseg = keppontok->w;
        magassag = keppontok->h;
        hatterszin = masik.hatterszin;

///        A GPU-hoz tartozó mintát a pixelfrissítés majd elvégzi, és ezzel beállítja a flag-et is.
        pixelfrissites();

        return *this;
    }

    Minta::Minta(const Minta &masik) : mAblak(masik.mAblak){
///        Alapértékek beállítása
        minta = nullptr;
        keppontok = nullptr;
        szelesseg = magassag = 0;

///        Így már biztonságosan hívható az operator=.
        *this = masik;
    }

    void Minta::PNGmentes(const std::string &nev) {
        if(keppontok == nullptr) {
///            Egy warningot kiírunk, ha nincs mit elmenteni, de a program azért ne haljon meg.
            SDL_Log("W: Nincs mit elmenteni!\n");
            return;
        }
///        A pixelek mentése.
        if(IMG_SavePNG(keppontok, nev.c_str()) < 0){
            throw SDL::SDL_Error("Nem sikerült elmenteni a " + nev + " képet!");
        }
    }

    Minta::Pixeloszlop::Pixeloszlop(int x, Uint32 pixelszelesseg, int pixelmagassag, Uint32 *pixelek, SDL_PixelFormat* formatum) {
///        Az adatok beállítása.
        this->x = x;
        this->pixelszelesseg = pixelszelesseg;
        this->pixelmagassag = pixelmagassag;
        this->pixelek = pixelek;
        this->formatum = formatum;
    }

    Minta::RGB_Pixel Minta::Pixeloszlop::operator[](int y) {
///        Ha rossz a koordináta, NULL-t adunk tovább.
        if(y < 0 || y >= pixelmagassag || pixelek == nullptr) return Minta::RGB_Pixel(nullptr, formatum);
        return Minta::RGB_Pixel(&pixelek[y * pixelszelesseg + x], formatum);
    }

    Minta::RGB_Pixel::RGB_Pixel(Uint32 *szerkesztettpixel, SDL_PixelFormat* formatum) {
///        Adatok rögzítése a saját változókba.
        this->szerkesztettpixel = szerkesztettpixel;
        this->formatum = formatum;

///        Ha nem létezik a pixel, nem csinál semmit.
        if(szerkesztettpixel != nullptr) {
            SDL_GetRGB(*szerkesztettpixel, formatum, &mR, &mG, &mB);
        }
    }

    Minta::RGB_Pixel &Minta::RGB_Pixel::operator=(SDL_Color szin) {
///        Adatok rögzítése.
        mR = szin.r;
        mG = szin.g;
        mB = szin.b;

///        A változtatások rögzítése a kép pixeljében, ha az arra mutató pointer nem NULL.
        if(szerkesztettpixel != nullptr) {
            *szerkesztettpixel = SDL_MapRGB(formatum, mR, mG, mB);
        }

        return *this;
    }

    Minta::RGB_Pixel::operator SDL_Color() const {
///        Az SDL_Color-rá alakítás legegyszerűbb módja.
        return {mR, mG, mB};
    }

    Minta::RGB_Pixel &Minta::RGB_Pixel::operator=(const Minta::RGB_Pixel &masik) {
///        Adatok rögzítése.
        mR = masik.mR;
        mG = masik.mG;
        mB = masik.mB;

///        A változtatások rögzítése a kép pixeljében, ha az arra mutató pointer nem NULL.
        if(szerkesztettpixel != nullptr) {
            *szerkesztettpixel = SDL_MapRGB(formatum, mR, mG, mB);
        }
        return *this;
    }
} // SDL