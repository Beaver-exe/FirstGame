#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>

class TileMap;

class MapLoader {
public:
    static TileMap load(const std::string& path);

};

#endif