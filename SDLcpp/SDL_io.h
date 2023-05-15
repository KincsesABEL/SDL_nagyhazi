//Kincses Ábel SORHOJ
// Created by kabel on 2023.05.05..
//

#ifndef SDL_ATIRAT2_0_SDL_IO_H
#define SDL_ATIRAT2_0_SDL_IO_H


#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <iostream>

/// @file SDL_io.h A beépített SDL típusok kiírását és beolvasását segíti elő.

/// Az SDL_Point, SDL_Rect és SDL_Color típusokat lehet így egyszerűen írni.


/// @name Kiíró függvények
/// beépített SDL típusok kiírására.
/// @{


/// Pont kiírása

/// @param ki A kiíró stream.
/// @param pont A kiírandó SDL pont.
std::ostream& operator<<(std::ostream& ki, SDL_Point pont);


/// Téglalap kiírása.

/// @param ki A kiíró stream.
/// @param teglalap A kiírandó téglalap.
std::ostream& operator<<(std::ostream& ki, SDL_Rect teglalap);


/// Szín kiírása.

/// @param ki A kiíró stream.
/// @param szin A kiírandó szín.
std::ostream& operator<<(std::ostream& ki, SDL_Color szin);


/// @}


/// @name Beolvasó függvények
/// beépített SDL típusok beolvasására.
/// @{


/// Pont beolvasása.

/// @param be A bejövő stream.
/// @param pont A beolvasandó pont.
std::istream& operator>>(std::istream& be, SDL_Point& pont);


/// Téglalap beolvasása.

/// @param be A bejövő stream.
/// @param teglalap A beolvasandó téglalap.
std::istream& operator>>(std::istream& be, SDL_Rect& teglalap);


/// Szín beolvasása.

/// Figyelem, az SDL_Color RGBA formátumú, azaz van egy negyedik, átlátszósági komponense is.
/// @param be A bejövő stream.
/// @param szin A beolvasandó szín.
std::istream& operator>>(std::istream& be, SDL_Color& szin);


/// @}

#endif //SDL_ATIRAT2_0_SDL_IO_H
