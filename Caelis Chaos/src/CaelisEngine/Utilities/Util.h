#ifndef UTIL_H
#define UTIL_H

#include "SDL3/SDL.h"
#include <cmath>

inline SDL_Point SDLPoint(int x, int y) {
	SDL_Point p = {x, y};
    return p;
}

inline SDL_FPoint SDLFPoint(float x, float y) {
    SDL_FPoint p = {x, y};
    return p;
}

inline SDL_FPoint SDLFPoint(SDL_FPoint otherPoint) {
    SDL_FPoint p = {otherPoint.x, otherPoint.y};
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

inline float calculateDistance(SDL_FPoint p1, SDL_FPoint p2)
{
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

#endif
