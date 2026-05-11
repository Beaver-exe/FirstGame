#include "loader/MapLoader.h"
#include "loader/TileSetLoader.h"

#include "tiles/TileMap.h"

#include <fstream>
#include <iostream>

#include <external/json.hpp>
using json = nlohmann::json;

std::shared_ptr<TileMap>
MapLoader::load(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Failed to open TMJ: " << path << "\n";
        return nullptr;
    }

    json tmj;
    file >> tmj;

    auto map = std::make_shared<TileMap>(
        tmj["width"],
        tmj["height"],
        tmj["tilewidth"],
        tmj["tileheight"]
    );

    const std::string assetRoot = "assets/";

    for (const auto& ts : tmj["tilesets"])
    {
        uint32_t firstgid = ts["firstgid"];

        std::string source = ts["source"].get<std::string>();
        std::string tsxPath = assetRoot + source;

        auto tileset = TileSetLoader::load(tsxPath, firstgid);

        if (tileset) {
            map->addTileSet(tileset);
            std::cout << "Loaded tileset: " << tsxPath << "\n";
       }
    }

    std::vector<uint32_t> tiles;

    tiles.reserve(tmj["width"].get<int>() * tmj["height"].get<int>());

    for (const auto& layer : tmj["layers"]) {
        if (layer["type"] != "tilelayer") {
            continue;
        }

        const auto& data = layer["data"];

        for (const auto& gid : data) {
            tiles.push_back(gid.get<uint32_t>());
        }
    }

    map->setTiles(tiles);

    return map;
}