//Kincses Ábel SORHOJ
/// @file A SzovegesMinta osztály tesztelése.

#include <iostream>
#include <stdexcept>
#include "Ablak.h"
#include "SzovegesMinta.h"


int main() try {
    /// Létrehozunk két ablakot,
    SDL::Ablak ablak1("ablak1", 700, 700), ablak2("ablak2", 700, 700);

    /// majd ezekbe az ablakokba a szövegeket.
    SDL::SzovegesMinta szoveg(ablak1), szoveg2(ablak1), szoveg3(ablak2);

    /// Utána létrehozzuk, és ezzel betöltjük a betűkészletet.
    SDL::Betukeszlet nagybetu("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 30), kisbetu("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 20);

    /// A betűkészlet segítségével elkészítjük a két kiírni kívánt szöveg képét.
    szoveg.kiir("Helló TTF!", {255,255,255}, nagybetu);
    szoveg2.kiir("Ez most már egy kisebb szöveg!", {0,0,0}, kisbetu);

    /// A második szöveget félig átlátszóvá tesszük,
    szoveg2.setAtlatszosag(120);

    /// utána az első szöveg tartalmát a harmadikba átmásoljuk, hogy az a második képernyőn is megjelenjen.
    szoveg3 = szoveg;

    /// Ezt a képet utána a komponensei átskálázásával pirossá színezzük,
    szoveg3.setSzinKomponens(0xFF,0x00,0x00);

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

        /// végül pedig mindhárom szöveget kirajzoljuk a képernyőre, opcionálisan elforgatva és tükrözve.
        szoveg.rajzol(20,20);
        szoveg2.rajzol(200,200, nullptr, 30, 1, 2, nullptr, SDL_FLIP_VERTICAL);
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