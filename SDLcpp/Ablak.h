//Kincses Ábel SORHOJ
// Created by kabel on 2023.04.21..
//

#ifndef SDL_ATIRAT2_0_ABLAK_H
#define SDL_ATIRAT2_0_ABLAK_H


#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <string>
#include "SDL_Objektum.h"

/// @file Ablak.h Az Ablak osztály deklarálása.

namespace SDL {
///    Ablak, ami meg fog jelenni a képernyőn.
    class Ablak : private SDL_Objektum {
    public:
///        Ablak létrehozása a képernyőn.

///        @param nev Az ablak tetjén megjelenő cím.
///        @param szelesseg Az ablak szélessége (pixelben).
///        @param magassag Az ablak magassága (pixelben).
///        @param allandomeret Ha hamis, meg lehet változtatni az ablak méretét, és tejles képernyőre lehet tenni.
///        @param szinkronizaltrenderer Ha igaz, akkor az ablak képfrissítése (Ablak::rajzol) megvárja a számítógép képernyőjének frissítését.
///        @throws SDL::SDL_Error Ha nem sikerült az ablakot létrehozni.
        explicit Ablak(const std::string& nev = "SDL ablak", int szelesseg = 640, int magassag = 480, bool allandomeret = true, bool szinkronizaltrenderer = true);

///        Ablakhoz tartozó SDL memória felszabadítása.

///        Megszünteti a renderert, és az SDL ablakot, majd beállítja a pointereket NULL-ra.
        ~Ablak();

///    Ablakot másolni nem lehet. Átadni is csak referenciában vagy pointerrel érdemes, hiszen csak egy jelenik meg a képernyőn.
        Ablak(const Ablak&) = delete;
///    Ablakot másolni nem lehet. Átadni is csak referenciában vagy pointerrel érdemes, hiszen csak egy jelenik meg a képernyőn.
        Ablak& operator= (const Ablak&) = delete;

///        Minden létrehozott ablaknál mindig meg kell hívni az eseménykezelésben!

///        Az ablak a saját magára vonatkozó eseményeket kezeli (méretváltoztatás, tálcára tétel).
///        @param e Az SDL_Event típusú esemény. Az SDL_PollEvent segítségével hívható. SDL_Event: https://wiki.libsdl.org/SDL2/SDL_Event
        void handleEvent(SDL_Event& e);

///        Az ablak hátterének kitöltése egyszínűre.

///        @param szin A háttér ilyen színű lesz, alapból fehér.
        void torol(const SDL_Color& szin = {0xFF, 0xFF, 0xFF, 0xFF});

///        Az ablak tartalmának megjelenítése a képernyőn, e nélkül nem jelenik meg semmi sem.

///        Ha a renderer szinkronizált (alapból az), akkor itt megvárja a képernyő frissítését.
        void rajzol(){ SDL_RenderPresent(renderer);}

///        Beállítja, hogy milyen színnel rajzoljon az ablak.

///        @param szin Az ezután rajzolt vonalak ilyen színűek lesznek.
        void setRenderColor(const SDL_Color& szin = {0xFF, 0xFF, 0xFF, 0xFF});

///        Az ablakhoz tartozó SDL_Renderer-t adja vissza. Praktikus a - operátor használata.
        SDL_Renderer *getRenderer(){ return renderer;}
///        Az ablakhoz tartozó SDL_Renderer-t adja vissza.
        SDL_Renderer *operator-(){ return renderer;}

//         végtelen sok getterfüggvény
///        Az ablak azonosítóját adja vissza.

///        event.window.windowID == ablak.getAblakAzonosito() akkor igaz, ha az esemény az adott ablakra vonatkozik.
        [[nodiscard]] Uint32 getAblakAzonosito() const{ return azonositoszam;}
///        Az ablak szélessége.
        [[nodiscard]] int getSzelesseg() const{ return szelesseg;}
///        Az ablak magassága.
        [[nodiscard]] int getMagassag() const{ return magassag;}
///        Igaz, ha az egér az ablak felett tartózkodik.
        [[nodiscard]] bool egerRajtaVan_e() const{ return eger_rajta;}
///        Igaz, ha a billentyűzet az adott ablakba ír.
        [[nodiscard]] bool billentyuzetRajtaVan_e() const{ return billentyuzet_rajta;}
///        Teljes képernyőn van-e az ablak.
        [[nodiscard]] bool teljesKepernyo_e() const{ return teljes_kepernyo;}
///        Tálcára tették-e az ablakot.
        [[nodiscard]] bool talcaraTettek_e() const{ return eltuntetett;}
///        Látható-e az ablak a képernyőn.
        [[nodiscard]] bool latszik_e() const{ return latszik;}

///        Visszatéríti az ablakhoz tartozó SDL_Window pointert.
        SDL_Window* getAblakPointer(){ return ablakpointer;}

    private:
///        Az ablakhoz tartozó SDL_Window pointer.
        SDL_Window* ablakpointer;
///        Az ablakhoz tartozó SDL_Renderer pointer.
        SDL_Renderer* renderer;

///        Az ablak azonosítószáma, windowID-je.
        Uint32 azonositoszam;

///        Az ablak szélessége és magassága.
        int szelesseg, magassag;

///        Az ablak állapotának flag-jei. Pontosabb leírás a getterfüggvényeknél található.
        bool eger_rajta, billentyuzet_rajta, teljes_kepernyo{}, eltuntetett{}, latszik;

///        Az ablakokat tartja számon.

///        Ha egy ablak bezárásánál 0, akkor az SDL_QUIT eseményt generál, ezzel könnyítve az eseménykezelést.
        static int ablakszamlalo;
    };

} // SDL

#endif //SDL_ATIRAT2_0_ABLAK_H
