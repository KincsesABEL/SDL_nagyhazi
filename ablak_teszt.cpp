//Kincses Ábel SORHOJ
// Created by kabel on 2023.04.18..
//
#include <iostream>
#include <stdexcept>
#include "Ablak.h"

int main() try {
    Ablak egyik("egyik", 640, 480, false, false), masik("másik", 640, 480, true, false);

    bool kilep = false;
    SDL_Event e;

    while(not kilep){
        while (SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                kilep = true;
            }
            egyik.handleEvent(e);
            masik.handleEvent(e);
        }

        egyik.torol();
        masik.torol();

        egyik.setRenderColor({0, 255, 0});
        SDL_RenderDrawLine(-egyik, 10, 10, 400, 400);

        SDL_Rect negyzet = {30, 50, 200, 200};
        masik.setRenderColor({255, 0, 0});
        SDL_RenderFillRect(-masik, &negyzet);

        egyik.rajzol();
        masik.rajzol();
    }

    return 0;
}
catch (exception& error){
    cout << "Error a main-ben: " << error.what() << endl;
    return 1;
}
catch (...){
    cout << "Ismeretlen error a main-ben!\n";
    return 1;
}
