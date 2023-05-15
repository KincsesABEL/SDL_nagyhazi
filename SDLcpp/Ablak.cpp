//Kincses Ábel SORHOJ
// Created by kabel on 2023.04.21..
//

#include "Ablak.h"
#include "SDL_Error.h"

namespace SDL {
    int Ablak::ablakszamlalo = 0;

    Ablak::Ablak(const std::string& nev, int szelesseg, int magassag, bool allandomeret, bool szinkronizaltrenderer) {
///        A pointerek kezdetben jobb, ha NULL-ra vannak állítva.
        ablakpointer = nullptr;
        renderer = nullptr;

///    Adatok átvétele.
        this->szelesseg = szelesseg;
        this->magassag = magassag;

///    Ablak létrehozása, a user kérésének megfelelő paraméterekkel.
        Uint32 ablakflag = SDL_WINDOW_SHOWN;
        if(!allandomeret) ablakflag |= SDL_WINDOW_RESIZABLE;
        ablakpointer = SDL_CreateWindow(nev.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, szelesseg, magassag, ablakflag);

        if(ablakpointer == nullptr) throw SDL::SDL_Error("Az " + nev + " ablakot nem sikerült létrehozni!");
///    Ablak flag-ek beállítása. Ezek később megváltozhatnak.
        eger_rajta = true;
        billentyuzet_rajta = true;

///    Renderer létrehozása a megfelelő paraméterek szerint.
        Uint32 rendererflag = SDL_RENDERER_ACCELERATED;
        if(szinkronizaltrenderer) rendererflag |= SDL_RENDERER_PRESENTVSYNC;
        renderer = SDL_CreateRenderer(ablakpointer, -1, rendererflag);

        if(renderer == nullptr){
            SDL_DestroyWindow(ablakpointer);
            throw SDL::SDL_Error("A renderert nem sikerült létrehozni!");
        }

///    Ablak előkészítése a további használathoz.
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        azonositoszam = SDL_GetWindowID(ablakpointer);

        latszik = true;
        ablakszamlalo++;
    }

    Ablak::~Ablak() {
///    A renderer és az ablak felszámolása.
        if(renderer != nullptr){
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }

        if(ablakpointer != nullptr){
            SDL_DestroyWindow(ablakpointer);
            ablakpointer = nullptr;
        }
    }

    void Ablak::handleEvent(SDL_Event &e) {
///        Csak azt az eseményt vizsgáljuk, ami erre az ablakra vonatkozik.
        if(e.type == SDL_WINDOWEVENT && e.window.windowID == azonositoszam){
            switch (e.window.event) {
                case SDL_WINDOW_SHOWN:
///                    Látható lett az ablak a képernyőn.
                    latszik = true;
                    break;

                case SDL_WINDOWEVENT_HIDDEN:
///                    Elrejtették az ablakot.
                    latszik = false;
                    break;

                case SDL_WINDOWEVENT_SIZE_CHANGED:
///                    Új méretei lettek az ablaknak.
                    szelesseg = e.window.data1;
                    magassag = e.window.data2;
                    SDL_RenderPresent(renderer);
                    break;

                case SDL_WINDOWEVENT_EXPOSED:
///                    Ablakot kirakták a képernyőre.
                    SDL_RenderPresent(renderer);
                    break;

                case SDL_WINDOWEVENT_ENTER:
///                    Az egér bejött az ablak fölé.
                    eger_rajta = true;
                    break;

                case SDL_WINDOWEVENT_LEAVE:
///                    Az egér elhagyta az ablakot.
                    eger_rajta = false;
                    break;

                case SDL_WINDOWEVENT_FOCUS_GAINED:
///                    A billentyűzet fókusza az ablakon van.
                    billentyuzet_rajta = true;
                    break;

                case SDL_WINDOWEVENT_FOCUS_LOST:
///                    A billentyűzet már nem az ablakba ír.
                    billentyuzet_rajta = false;
                    break;

                case SDL_WINDOWEVENT_MINIMIZED:
///                    Az ablakot a tálcára tették.
                    eltuntetett = true;
                    break;

                case SDL_WINDOWEVENT_MAXIMIZED:
                case SDL_WINDOWEVENT_RESTORED:
///                    Újra látható az ablak.
                    eltuntetett = false;
                    break;

                case SDL_WINDOWEVENT_CLOSE:
///                    Megnyomták az X-et az ablak felső sarkán.
                    SDL_HideWindow(ablakpointer);
                    ablakszamlalo--;

///                    Ha ez volt az utolsó ablak, SDL_QUIT-et teszünk az eseménylistára.
                    if(ablakszamlalo <= 0){
                        SDL_Event kilepo;
                        kilepo.type = SDL_QUIT;
                        SDL_PushEvent(&kilepo);
                    }
                    break;
            }
        }
    }

    void Ablak::torol(const SDL_Color& szin) {
        SDL_SetRenderDrawColor(renderer, szin.r, szin.g, szin.b, szin.a);
        SDL_RenderClear(renderer);
    }

    void Ablak::setRenderColor(const SDL_Color &szin) {
///        Beállítjuk a renderer színét.
        SDL_SetRenderDrawColor(renderer, szin.r, szin.g, szin.b, szin.a);
    }
} // SDL