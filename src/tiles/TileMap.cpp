#include "tiles/TileMap.h"

#include <algorithm>

TileMap::TileMap(int mapWidth, int mapHeight, int tileWidth, int tileHeight)
    : mapWidth(mapWidth),
      mapHeight(mapHeight),
      tileWidth(tileWidth),
      tileHeight(tileHeight)
{
    tileGIDs.reserve(mapWidth * mapHeight);
}

uint32_t TileMap::getTile(int x, int y) const {
    int index = y * mapWidth + x;
    return tileGIDs[index];
}

void TileMap::setTile(int x, int y, uint32_t tileGID) {
    int index = y * mapWidth + x;
    tileGIDs[index] = tileGID;
}

void TileMap::setTiles(const std::vector<uint32_t>& newTiles) {
    tileGIDs = newTiles;
}

const std::vector<uint32_t>& TileMap::getTiles() const {
    return tileGIDs;
}

void TileMap::addTileSet(std::shared_ptr<TileSet> tileset) {
    tilesets.push_back(tileset);
}

const std::vector<std::shared_ptr<TileSet>>& TileMap::getTileSets() const {
    return tilesets;
}

std::shared_ptr<TileSet> TileMap::getTileSetForGid(uint32_t gid) const {
    for (const auto& tileset : tilesets) {
        if (gid >= tileset->firstGid &&
            gid <= tileset->getLastGid())
        {
            return tileset;
        }
    }

    return nullptr;
}

int TileMap::getWidth() const {
    return mapWidth;
}

int TileMap::getHeight() const {
    return mapHeight;
}

int TileMap::getTileWidth() const {
    return tileWidth;
}

int TileMap::getTileHeight() const {
    return tileHeight;
}