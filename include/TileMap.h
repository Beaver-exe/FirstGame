#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>


class TileMap {

public:
    TileMap(int width, int height);
    int getTile(int x, int y);
    void setTile(int x, int y, int tileId);
    void generateMap();

private:
    int mapHeight;
    int mapWidth;
    std::vector<int> tiles;

};

#endif