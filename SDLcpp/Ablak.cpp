//
// Created by kabel on 2023.04.21..
//

#include "Ablak.h"
#include "SDL_Error.h"

namespace SDL {
    int Ablak::ablakszamlalo = 0;

    Ablak::Ablak(const std::string& nev, int szelesseg, int magassag, bool allandomeret, bool szinkronizaltrenderer) {
        ablakpointer = nullptr;
        renderer = nullptr;

//    adatok átvétele
        this->szelesseg = szelesseg;
        this->magassag = magassag;
//    ablak létrehozása
        Uint32 ablakflag = SDL_WINDOW_SHOWN;
        if(!allandomeret) ablakflag |= SDL_WINDOW_RESIZABLE;
        ablakpointer = SDL_CreateWindow(nev.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, szelesseg, magassag, ablakflag);

        if(ablakpointer == nullptr) throw SDL::SDL_Error("Az " + nev + " ablakot nem sikerült létrehozni!");
//    flag-ek beállítása
        eger_rajta = true;
        billentyuzet_rajta = true;

//    renderer létrehozása
        Uint32 rendererflag = SDL_RENDERER_ACCELERATED;
        if(szinkronizaltrenderer) rendererflag |= SDL_RENDERER_PRESENTVSYNC;
        renderer = SDL_CreateRenderer(ablakpointer, -1, rendererflag);

        if(renderer == nullptr){
            SDL_DestroyWindow(ablakpointer);
            throw SDL::SDL_Error("A renderert nem sikerült létrehozni!");
        }

//    ablak előkészítése a további használathoz
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        azonositoszam = SDL_GetWindowID(ablakpointer);

        latszik = true;
        ablakszamlalo++;
    }

    Ablak::~Ablak() {
//    renderer és az ablak felszámolása
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
        if(e.type == SDL_WINDOWEVENT && e.window.windowID == azonositoszam){
            switch (e.window.event) {
                case SDL_WINDOW_SHOWN:
                    latszik = true;
                    break;

                case SDL_WINDOWEVENT_HIDDEN:
                    latszik = false;
                    break;

                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    szelesseg = e.window.data1;
                    magassag = e.window.data2;
                    SDL_RenderPresent(renderer);
                    break;

                case SDL_WINDOWEVENT_EXPOSED:
                    SDL_RenderPresent(renderer);
                    break;

                case SDL_WINDOWEVENT_ENTER:
                    eger_rajta = true;
                    break;

                case SDL_WINDOWEVENT_LEAVE:
                    eger_rajta = false;
                    break;

                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    billentyuzet_rajta = true;
                    break;

                case SDL_WINDOWEVENT_FOCUS_LOST:
                    billentyuzet_rajta = false;
                    break;

                case SDL_WINDOWEVENT_MINIMIZED:
                    eltuntetett = true;
                    break;

                case SDL_WINDOWEVENT_MAXIMIZED:
                case SDL_WINDOWEVENT_RESTORED:
                    eltuntetett = false;
                    break;

                case SDL_WINDOWEVENT_CLOSE:
                    SDL_HideWindow(ablakpointer);
                    ablakszamlalo--;
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
        SDL_SetRenderDrawColor(renderer, szin.r, szin.g, szin.b, szin.a);
    }
} // SDL
