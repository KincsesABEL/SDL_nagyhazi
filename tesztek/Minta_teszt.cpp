#include <iostream>
#include <stdexcept>
#include "Ablak.h"
#include "Minta.h"

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
    SDL::Ablak ablak1("zöldmadár", 700, 700), ablak2("kékmadár", 700, 700);

    SDL::Minta kep1(ablak1), kep2(ablak2), kep3(ablak1);

//    betöltöm a képet, majd a másik ablakhoz tartozó mintába átrakom
    kep1.betolt("atlatszohatter.png", {0,255,255});//"atlatszohatter.png"
    kep2 = kep1;

    kep3.betolt("1pzh.jpg");
    kep3.setAtlatszosag(120);
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
//                        ha SPACE-t nyomtak
                        if (e.window.windowID == ablak1.getAblakAzonosito()) {
                            //                    első ablakban levő madarat zöldítjük
                            zoldit(kep1);
                        } else if (e.window.windowID == ablak2.getAblakAzonosito()) {
                            //                    második ablakban levő madarat kékítjük
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

        kep1.rajzol(100, 100, nullptr, 0, 1.4, 1, nullptr, SDL_FLIP_VERTICAL);
        kep3.rajzol(20, 20, nullptr, 0, 0.5, 1.1);

        kep2.rajzol(0,0);
        kep2.rajzol(100, 150, &premierplan, szog += forgas);

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