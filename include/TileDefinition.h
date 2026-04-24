#ifndef TILEDEFINITION_H
#define TILEDEFINITION_H

#include <string>


class TileDefinition{

public:
    TileDefinition(
        const std::string& tileTexture,
        bool isWalkable,
        bool isBreakable,
        bool isSolid
    )
        : textureName(tileTexture),
        walkable(isWalkable),
        breakable(isBreakable),
        solid(isSolid)
    {
    }

    TileDefinition() {};

private:
    std::string textureName = "awesomeface";
    bool walkable = true;
    bool breakable = false;
    bool solid = true;

};


#endif