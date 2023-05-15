//Kincses Ábel SORHOJ
/// @file ablak_teszt.cpp Az Ablak osztály főbb funkciójinak tesztelése.

#include <iostream>
#include <stdexcept>
#include "Ablak.h"

/// Ebben a kódban csak main függvény van.
int main() try {
    /// Két ablakot hozunk létre. Mivel az egyik ablak átméretezhető lesz, ehhez pedig nem érdemes a képfrissítéshez szinkronizálni a rajzolást.
    SDL::Ablak egyik("egyik", 640, 480, false, false), masik("másik", 640, 480, true, false);

    /// A main loop két fő változója, a kilépésért felelő boolean, és az SDL_Event típusú, eseménykezeléshez szükséges e nevű változó.
    bool kilep = false;
    SDL_Event e;

    while(not kilep){
        while (SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                kilep = true;
            }

            /// Az eseménykezelésben muszáj meghívni az ablakok eseményét, különben nem lehet kilépni a programból.
            egyik.handleEvent(e);
            masik.handleEvent(e);
        }

        /// Ezek után tisztára töröljük a két ablak hátterét,
        egyik.torol();
        masik.torol();

        /// majd a rajzolás színét beállítva az egyikre egy vonalat, a másikra egy téglalapot rajzolunk.
        egyik.setRenderColor({0, 255, 0});
        SDL_RenderDrawLine(-egyik, 10, 10, 400, 400);

        SDL_Rect negyzet = {30, 50, 200, 200};
        masik.setRenderColor({255, 0, 0});
        SDL_RenderFillRect(-masik, &negyzet);

        /// A main loop végén mindkét ablaknak meg kell hívni a rajzol függvényét, hogy az ablak tartalmát kirajzoljuk a számítógép képernyőjére.
        egyik.rajzol();
        masik.rajzol();
    }

    return 0;
}
catch (std::exception& error){
    std::cout << "Error a main-ben: " << error.what() << std::endl;
    return 1;
}
catch (...){
    std::cout << "Ismeretlen error a main-ben!\n";
    return 1;
}