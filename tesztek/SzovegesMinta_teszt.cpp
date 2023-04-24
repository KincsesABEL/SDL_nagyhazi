#include <iostream>
#include <stdexcept>
#include "Ablak.h"
#include "SzovegesMinta.h"


int main() try {
    SDL::Ablak ablak1("ablak1", 700, 700), ablak2("ablak2", 700, 700);

    SDL::SzovegesMinta szoveg(ablak1), szoveg2(ablak1), szoveg3(ablak2);
    SDL::Betukeszlet nagybetu("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 30), kisbetu("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 20);

    szoveg.kiir("Helló TTF!", {255,255,255}, nagybetu);
    szoveg2.kiir("Ez most már egy kisebb szöveg!", {0,0,0}, kisbetu);
    szoveg3 = szoveg;

    bool kilep = false;
    SDL_Event e;

    while(not kilep){
        while (SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
//                kilépünk a programból
                kilep = true;

            }

            ablak1.handleEvent(e);
            ablak2.handleEvent(e);
        }
        ablak1.torol({0,255,0});
        ablak2.torol({255,0,255});

        szoveg.rajzol(20,20);
        szoveg2.rajzol(200,200);
        szoveg3.rajzol(0,0);

        ablak1.rajzol();
        ablak2.rajzol();
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