#include "TileMap.h"

#include <algorithm>

TileMap::TileMap(int width, int height)
    : mapWidth(width),
      mapHeight(height),
      tiles(width * height)
{
}

int TileMap::getTile(int x, int y) const {
    int index = y * mapWidth + x;
    return tiles[index];
}

void TileMap::setTile(int x, int y, int tileId) {
    int index = y * mapWidth + x;
    tiles[index] = tileId;
}

void TileMap::generateMap() {
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            int index = y * mapWidth + x;
            tiles[index] = ((x + y) % 2 == 0) ? 1 : 2;
        }
    }
}

int TileMap::getWidth() const {
    return mapWidth;
}

int TileMap::getHeight() const {
    return mapHeight;
}