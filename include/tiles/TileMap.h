#ifndef TILEMAP_H
#define TILEMAP_H

#include "tiles/TileSet.h"

#include <vector>
#include <cstdint>
#include <memory>

class TileMap {
public:
    TileMap(
        int width,
        int height,
        int tileWidth,
        int tileHeight
    );

    uint32_t getTile(int x, int y) const;
    void setTile(int x, int y, uint32_t tileGID);

    void setTiles(const std::vector<uint32_t>& newTiles);
    const std::vector<uint32_t>& getTiles() const;

    void addTileSet(std::shared_ptr<TileSet> tileset);
    const std::vector<std::shared_ptr<TileSet>>& getTileSets() const;

    std::shared_ptr<TileSet> getTileSetForGid(uint32_t gid) const;

    int getWidth() const;
    int getHeight() const;

    int getTileWidth() const;
    int getTileHeight() const;

private:
    int mapWidth;
    int mapHeight;

    int tileWidth;
    int tileHeight;

    std::vector<uint32_t> tileGIDs;
    std::vector<std::shared_ptr<TileSet>> tilesets;
};

#endif