#include "world/World.h"
#include "loader/MapLoader.h"
#include "entities/Player.h"

World::World(const std::string& pathName, const glm::ivec2& position, bool active)
    : map(MapLoader::load(pathName)), player(Player(position, active))
{
}

TileMap& World::getMap() {
    return map;
}

Player& World::getPlayer() {
    return player;
}