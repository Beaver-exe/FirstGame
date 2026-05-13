#ifndef TILELAYER_H
#define TILELAYER_H

#include <vector>
#include <string>
#include <cstdint>

struct TileLayer
{
    std::string name;

    int width = 0;
    int height = 0;

    bool visible = true;
    float opacity = 1.0f;

    std::vector<uint32_t> tiles;

    uint32_t getTile(int x, int y) const { return tiles[y * width + x]; }
    void setTile(int x, int y, uint32_t gid) { tiles[y * width + x] = gid; }

};

#endif
