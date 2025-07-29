#include "GUIComponent.h"

SDL_Point GUIComponent::translateRelativeToAbsolute(SDL_FPoint relativeCoords, SDL_Point windowResolution) const
{
    return { (int)(relativeCoords.x * windowResolution.x) , (int)(relativeCoords.y * windowResolution.y) };
}
