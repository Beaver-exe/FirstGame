#ifndef WORLD_H
#define WORLD_H

#include "tiles/TileMap.h"
#include "entities/Player.h"

class World {
public:
    World(const std::string& pathName, const glm::ivec2& startTile, bool active);
    TileMap& getMap();
    Player& getPlayer();

private:
    TileMap map;
    Player player;
};

#endif