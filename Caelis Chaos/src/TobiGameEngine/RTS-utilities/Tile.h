#ifndef TILE_H
#define TILE_H

#include <string>
#include <TMath.h>

class Tile
{
public:

    Tile();

    void setTexture(std::string newTexture);

    void setCoords(float nX, float nY);

    void setCoords(Vector2D nPosition);

    Vector2D mPosition;

    std::string ID;
    std::string pTexture;
    std::string sName;
    float fHeight;
    float fWidth;
};

#endif
