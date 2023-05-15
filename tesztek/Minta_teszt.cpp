//Kincses Ábel SORHOJ
/// @file Minta_teszt.cpp A Minta class tesztelő programja.

#include <iostream>
#include <stdexcept>
#include "Ablak.h"
#include "Minta.h"

/// Egy kép pixeleinek kizöldítésére szolgáló függvény.

/// A működése elég egyszerű, két forciklussal végigmegy a kép minden pixelén, és ha a kép piros komponense nagyobb a zöldnél,
/// a két értéket kicseréli. Ehhez a kép [i][j]-vel indexelt elemét SDL_Color-rá alakítja, azzal elvégzi a műveletet,
/// majd a kép ugyanezen elemét a színnel egyenlővé teszi.
/// @param kep A kép referenciája, amit átszínezünk.
void zoldit(SDL::Minta& kep){

    for (int i = 0; i < kep.getSzelesseg(); ++i) {
        for (int j = 0; j < kep.getMagassag(); ++j) {
            SDL_Color szin = kep[i][j];

            if(szin.r > szin.g){
                int temp = szin.g;
                szin.g = szin.r;
                szin.r = temp;
            }

            kep[i][j] = szin;
        }
    }
}

/// Egy kép pixeleinek kikékítésére szolgáló függvény.

/// A működése elég egyszerű, két forciklussal végigmegy a kép minden pixelén, és ha a kép piros komponense nagyobb a kéknél,
/// a két értéket kicseréli. Ehhez a kép [i][j]-vel indexelt elemét annak komponenseinek fordított felsorolásával teszi egyenlővé.
/// Ez a függvény GCC alatt lefordul, viszont nem biztos, hogy ez a megvalósítás szabványos.
/// @param kep A kép, amit átszínezünk.
/// @returns Az átszerkesztett képet adja vissza.
SDL::Minta kekit(SDL::Minta kep){

    for (int i = 0; i < kep.getSzelesseg(); ++i) {
        for (int j = 0; j < kep.getMagassag(); ++j) {
            auto szin = kep[i][j];

            if(szin.r() > szin.b()){
                szin = {szin.b(), szin.g(), szin.r()};
            }
        }
    }

    return kep;
}

int main() try {
    /// A main függvényben először létrehozunk két ablakot. A másodiknál nem kell, hogy a renderer szinkronizálva legyen a képernyő frissítésével.
    SDL::Ablak ablak1("zöldmadár", 700, 700), ablak2("kékmadár", 700, 700, true, false);

    /// Létrehozzuk a három kép objektumot, ami meg fog jelenni a képernyőn.
    SDL::Minta kep1(ablak1), kep2(ablak2), kep3(ablak1);

    /// Betöltjük az átlátszó hátterű képet, ahol megadjuk, hogy melyik színt tekintse átlátszónak az SDL.
    kep1.betolt("atlatszohatter.png", {0,255,255});//"atlatszohatter.png"
    /// Utána a kettes számú képet ezzel egyenlővé tesszük, így a második ablakban is meg tudjuk jeleníteni.
    kep2 = kep1;

    /// Betöltjük az eredeti, nem átlátszó hátterű képet,
    kep3.betolt("1pzh.jpg");
    /// majd félig átlátszóvá tesszük.
    kep3.setAtlatszosag(120);

    /// Létrehozunk egy olyan téglalapot, ami ezeken a képeken a madár szeme körül helyezkedik el.
    SDL_Rect premierplan = {100, 150, 280, 200};

    int szog = 0, forgas = 0;

    bool kilep = false;
    SDL_Event e;

    while(not kilep){
        while (SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
//                kilépünk a programból
                kilep = true;

            } else if(e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym) {
                    case SDLK_SPACE:
///                        Ha SPACE-t nyomtak a program futása közben,
                        if (e.window.windowID == ablak1.getAblakAzonosito()) {
///                          és ez az első ablakban történt, akkor az első madarat zöldítjük,
                            zoldit(kep1);
                        } else if (e.window.windowID == ablak2.getAblakAzonosito()) {
///                          egyébként a másik madarat kékítjük.
                            kep2 = kekit(kep2);
                        }
                        break;

//                        a kékké változtatható madár fejét lehet forgatni
                    case SDLK_RETURN:
                        szog = 0;
                        break;

                    case SDLK_RIGHT:
                        forgas += 2;
                        break;

                    case SDLK_LEFT:
                        forgas -= 2;
                        break;
                }
            }

//            ha valamelyik ablak kimarad az event handling-ből, azt nem lehet bezárni
            ablak1.handleEvent(e);
            ablak2.handleEvent(e);
        }
        ablak1.torol();
        ablak2.torol();

        /// Kirajzoljuk a képeket az első ablakba.
        kep1.rajzol(100, 100, nullptr, 0, 1.4, 1, nullptr, SDL_FLIP_VERTICAL);
        kep3.rajzol(20, 20, nullptr, 0, 0.5, 1.1);

        /// A második ablakba ugyanazt a képet rajzoljuk kétszer, csak másodszorra a madárnak csak a szemét jajzoljuk, megfelel szöggel elforgatva.
        kep2.rajzol(0,0);
        kep2.rajzol(100, 150, &premierplan, szog += forgas);

        ablak1.rajzol();
        ablak2.rajzol();
    }

    /// Kilépéskor elmentjük az így elkészített képeket a kétféle mentéssel.
    kep1.JPGmentes("eredmenyek/zoldmadar.jpg");
    kep2.PNGmentes("eredmenyek/kekmadar.png");

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