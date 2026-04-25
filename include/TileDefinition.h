#ifndef TILEDEFINITION_H
#define TILEDEFINITION_H

#include <string>


class TileDefinition{

public:
    TileDefinition(
        int id,
        const std::string& tileName,
        const std::string& tileTexture,
        bool isWalkable,
        bool isBreakable,
        bool isSolid
    )
        : tileId(id),
        tileName(tileName),
        textureName(tileTexture),
        walkable(isWalkable),
        breakable(isBreakable),
        solid(isSolid)
    {
    }

private:
    int tileId = -1;
    std::string tileName = "missing_texture";
    std::string textureName = "awesomeface";
    bool walkable = true;
    bool breakable = false;
    bool solid = true;
};


#endif