#ifndef TILEMAP_H
#define TILEMAP_H

#include "tiles/TileSet.h"
#include "tiles/TileLayer.h"

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

    void addLayer(const TileLayer& layer);

    const std::vector<TileLayer>& getLayers() const;

    const TileLayer* getLayer(const std::string& name) const;

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

    std::vector<TileLayer> layers;
    std::vector<std::shared_ptr<TileSet>> tilesets;
};

#endif