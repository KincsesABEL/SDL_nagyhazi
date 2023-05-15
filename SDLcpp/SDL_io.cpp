//Kincses Ábel SORHOJ
// Created by kabel on 2023.05.05..
//

#include "SDL_io.h"

std::ostream& operator<<(std::ostream& ki, SDL_Point pont){
    ki << pont.x << " " << pont.y;

    return ki;
}

std::ostream& operator<<(std::ostream& ki, SDL_Rect teglalap){
    ki << teglalap.x << " " << teglalap.y << " " << teglalap.w << " " << teglalap.h;

    return ki;
}

std::ostream& operator<<(std::ostream& ki, SDL_Color szin){
    ki << (int) szin.r << " " << (int) szin.g << " " << (int) szin.b << " " << (int) szin.a;

    return ki;
}

std::istream& operator>>(std::istream& be, SDL_Point& pont){
    be >> pont.x >> pont.y;

    return be;
}

std::istream& operator>>(std::istream& be, SDL_Rect& teglalap){
    be >> teglalap.x >> teglalap.y >> teglalap.w >> teglalap.h;

    return be;
}

std::istream& operator>>(std::istream& be, SDL_Color& szin){
///    Mivel az Uint8 nem egy beépített típus, int-eket olvasunk be, és abból rakjuk össze a színt.
    int r, g, b, a;
    be >> r >> g >> b >> a;

    szin = {(Uint8) r, (Uint8) g, (Uint8) b, (Uint8) a};

    return be;
}

