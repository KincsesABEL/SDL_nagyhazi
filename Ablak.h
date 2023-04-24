//
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

namespace SDL {

    class Ablak : private SDL_Objektum {
    public:
        explicit Ablak(const std::string& nev = "SDL ablak", int szelesseg = 640, int magassag = 480, bool allandomeret = true, bool szinkronizaltrenderer = true);
        ~Ablak();

//    Ablakot másolni nem lehet, átadni is csak referenciában vagy pointerrel
        Ablak(const Ablak&) = delete;
        Ablak& operator= (const Ablak&) = delete;

        void handleEvent(SDL_Event& e);

        void torol(const SDL_Color& szin = {0xFF, 0xFF, 0xFF, 0xFF});
        void rajzol(){ SDL_RenderPresent(renderer);}

        void setRenderColor(const SDL_Color& szin = {0xFF, 0xFF, 0xFF, 0xFF});

//    A renderer getterfüggvényéhez praktikus a - operátor használata
        SDL_Renderer *getRenderer(){ return renderer;}
        SDL_Renderer *operator-(){ return renderer;}

//    végtelen sok getterfüggvény
        [[nodiscard]] Uint32 getAblakAzonosito() const{ return azonositoszam;}
        [[nodiscard]] int getSzelesseg() const{ return szelesseg;}
        [[nodiscard]] int getMagassag() const{ return magassag;}
        [[nodiscard]] bool egerRajtaVan_e() const{ return eger_rajta;}
        [[nodiscard]] bool billentyuzetRajtaVan_e() const{ return billentyuzet_rajta;}
        [[nodiscard]] bool teljesKepernyo_e() const{ return teljes_kepernyo;}
        [[nodiscard]] bool talcaraTettek_e() const{ return eltuntetett;}
        [[nodiscard]] bool latszik_e() const{ return latszik;}

        SDL_Window* getAblakPointer(){ return ablakpointer;}

    private:
        SDL_Window* ablakpointer;
        SDL_Renderer* renderer;

        Uint32 azonositoszam;

        int szelesseg, magassag;

        bool eger_rajta, billentyuzet_rajta, teljes_kepernyo{}, eltuntetett{}, latszik;

        static int ablakszamlalo;
    };

} // SDL

#endif //SDL_ATIRAT2_0_ABLAK_H
