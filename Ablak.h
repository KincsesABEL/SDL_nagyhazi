//Kincses Ábel SORHOJ
// Created by kabel on 2023.04.17..
//

#ifndef SDL_ATIRAT_ABLAK_H
#define SDL_ATIRAT_ABLAK_H


#include <string>
#include "SDL_Objektum.h"

using namespace std;

class Ablak : private SDL_Objektum {
public:
    Ablak(string nev = "SDL ablak", int szelesseg = 640, int magassag = 480, bool allandomeret = true, bool szinkronizaltrenderer = true);
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

private:
    SDL_Window* ablakpointer;
    SDL_Renderer* renderer;

    Uint32 azonositoszam;

    int szelesseg, magassag;

    bool eger_rajta, billentyuzet_rajta, teljes_kepernyo, eltuntetett, letezik;

    static int ablakszamlalo;
};

#endif //SDL_ATIRAT_ABLAK_H
