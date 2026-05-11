#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <memory>
#include <string>

class TileMap;

class MapLoader {
public:
    static std::shared_ptr<TileMap> load(const std::string& path);

};

#endif