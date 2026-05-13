#include "tiles/TileMap.h"

#include <algorithm>

TileMap::TileMap(int mapWidth, int mapHeight, int tileWidth, int tileHeight)
    : mapWidth(mapWidth),
      mapHeight(mapHeight),
      tileWidth(tileWidth),
      tileHeight(tileHeight)
{
}

void TileMap::addLayer(const TileLayer& layer) {
    layers.push_back(layer);
}

const std::vector<TileLayer>& TileMap::getLayers() const {
    return layers;
}

const TileLayer* TileMap::getLayer(const std::string& name) const {
    for (const auto& layer : layers) {
        if (layer.name == name) {
            return &layer;
        }
    }

    return nullptr;
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