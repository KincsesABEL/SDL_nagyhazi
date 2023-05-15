//Kincses Ábel SORHOJ
/// @file SDL_io_teszt.cpp Az SDL_io függvényeinek kiprbálása.

#include <iostream>
#include <stdexcept>
#include <sstream>
#include "SDL_io.h"

/// Ebben a programban csak main függvény van.
int main() try {
    /// Létrehozunk néhány SDL-es beépített típusú változót.
    SDL_Rect t = {0,20, 100, 200};
    SDL_Color szin;
    SDL_Point pont = {30, 30};

    /// Létrehozunk egy stringstreamet, hogy szimuláljuk az adatok beolvasását.
    std::stringstream adatok;

    /// Kiírjuk a téglalap tartalmát.
    std::cout << t << std::endl;

    /// Kiírjuk a pont tartalmát.
    std::cout << pont << std::endl;

    /// Megtöltjük a stringstream tartalmát.
    adatok.str("30 31 32 33 "
               "255 255 255 5");

    /// Téglalap adatainak beolvasása.
    adatok >> t;

    /// Szín adatainak beolvasása.
    adatok >> szin;

    /// A beolvasott adatok kiírása, hogy valóban jól működött-e a dolog.
    std::cout << szin << std::endl;
    std::cout << t << std::endl;

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