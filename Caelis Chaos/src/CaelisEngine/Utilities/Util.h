#ifndef UTIL_H
#define UTIL_H

#include "SDL3/SDL.h"

inline SDL_Point SDLPoint(int x, int y) {
	SDL_Point p = {x, y};
    return p;
}

inline SDL_FPoint SDLFPoint(float x, float y) {
    SDL_FPoint p = {x, y};
    return p;
}

inline SDL_Color SDLColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_Color c = {r, g, b, a};
    return c;
}

inline SDL_FRect SDLFRect(float x, float y, float w, float h) {
	SDL_FRect r = {x, y, w, h};
    return r;
}

inline bool operator==(const SDL_FPoint& pointA, const SDL_FPoint& pointB) {
    return pointA.x == pointB.x && pointA.y == pointB.y;
}

#endif
