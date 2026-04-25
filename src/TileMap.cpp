#include "TileMap.h"

#include <algorithm>

TileMap::TileMap(int width, int height)
    : mapWidth(width),
      mapHeight(height),
      tiles(width * height)
{
}

int TileMap::getTile(int x, int y) {
    int index = y * mapWidth + x;
    return tiles[index];
}

void TileMap::setTile(int x, int y, int tileId) {
    int index = y * mapWidth + x;
    tiles[index] = tileId;
}

void TileMap::generateMap() {
    std::fill(tiles.begin(), tiles.end(), 1);
}
