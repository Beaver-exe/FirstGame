#ifndef TILESET_H
#define TILESET_H

#include <cstdint>
#include <string>

class TileSet {
public:
    TileSet(
        uint32_t firstGid,
        uint32_t tileWidth,
        uint32_t tileHeight,
        uint32_t tileCount,
        uint32_t columns,
        uint32_t imageWidth,
        uint32_t imageHeight,
        const std::string& imagePath,
        unsigned int textureID
    )
        : firstGid(firstGid),
          tileWidth(tileWidth),
          tileHeight(tileHeight),
          tileCount(tileCount),
          columns(columns),
          imageWidth(imageWidth),
          imageHeight(imageHeight),
          imagePath(imagePath),
          textureID(textureID)
    {
    }

    uint32_t getLastGid() const
    {
        return firstGid + tileCount - 1;
    }

    uint32_t firstGid = 0;

    uint32_t tileWidth = 0;
    uint32_t tileHeight = 0;

    uint32_t tileCount = 0;
    uint32_t columns = 0;

    uint32_t imageWidth = 0;
    uint32_t imageHeight = 0;

    std::string imagePath;

    unsigned int textureID = 0;
};

#endif