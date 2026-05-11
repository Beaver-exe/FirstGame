#ifndef TILESETLOADER_H
#define TILESETLOADER_H

#include <memory>
#include <string>
#include <cstdint>

class TileSet;

class TileSetLoader {
public:
    static std::shared_ptr<TileSet> load(const std::string& tsxPath, uint32_t firstGid);

};

#endif