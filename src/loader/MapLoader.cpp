#include "loader/MapLoader.h"
#include "loader/TileSetLoader.h"

#include "tiles/TileMap.h"

#include <fstream>
#include <iostream>

#include <external/json.hpp>
using json = nlohmann::json;

TileMap
MapLoader::load(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Failed to open TMJ: " << path << "\n";
        return TileMap(0, 0, 0, 0);
    }

    json tmj;
    file >> tmj;

    TileMap map(
        tmj["width"],
        tmj["height"],
        tmj["tilewidth"],
        tmj["tileheight"]
    );

    const std::string assetRoot = "assets/";

    for (const auto& ts : tmj["tilesets"]) {
        uint32_t firstgid = ts["firstgid"];

        std::string source = ts["source"].get<std::string>();
        std::string tsxPath = assetRoot + source;

        auto tileset = TileSetLoader::load(tsxPath, firstgid);

        if (tileset) {
            map.addTileSet(tileset);
            std::cout << "Loaded tileset: " << tsxPath << "\n";
        }
    }

    for (const auto& layerJson : tmj["layers"]) {
        if (layerJson["type"] != "tilelayer") {
            continue;
        }

        TileLayer layer;

        layer.name = layerJson.value("name", "");
        layer.width = layerJson["width"];
        layer.height = layerJson["height"];

        layer.visible = layerJson.value("visible", true);
        layer.opacity = layerJson.value("opacity", 1.0f);

        const auto& data = layerJson["data"];

        layer.tiles.reserve(layer.width * layer.height);

        for (const auto& gid : data) {
            layer.tiles.push_back(gid.get<uint32_t>());
        }

        map.addLayer(layer);

        std::cout << "Loaded layer: " << layer.name << "\n";
    }

    return map;
}