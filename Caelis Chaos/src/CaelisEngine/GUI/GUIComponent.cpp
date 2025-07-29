#include "GUIComponent.h"

SDL_Point operator*(const SDL_Point& p1, const SDL_Point& p2)
{
    return {p1.x * p2.x, p1.y * p2.y};
}

SDL_Point GUIComponent::translateRelativeToAbsolute(SDL_FPoint point, SDL_Point windowResolution) const
{
    SDL_Point absPoint = {(point.x * windowResolution.x) , (point.y * windowResolution.y)};
    return  absPoint;
}
