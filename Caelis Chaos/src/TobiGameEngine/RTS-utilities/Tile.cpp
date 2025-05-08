#include "Tile.h"

Tile::Tile()
{
    ID = "0";
    sName = "Grass";

    pTexture = "res/textures/tiles/Grass1.png";
    fHeight = 1.0f;
    fWidth = 1.0f;
}

void Tile::setTexture(std::string newTexture)
{
    pTexture = newTexture;
}

void Tile::setCoords(float nX, float nY)
{
    mPosition = { nX, nY };
}

void Tile::setCoords(Vector2D nPosition)
{
    mPosition = nPosition;
}