#include "TileRegistry.h"
#include "TileDefinition.h"

#include <iostream>

void TileRegistry::storeDefinition(const std::string& tileName, const TileDefinition& tileDefinition) {
    tileDefinitions[tileName] = tileDefinition;
}

const TileDefinition* TileRegistry::getTileDefinition(const std::string& tileName) {
    auto definition = tileDefinitions.find(tileName);
    if (definition != tileDefinitions.end()) {
        return &definition->second;
    }

    std::cout << "ERROR: Tile Definition not found in registry: " << tileName << std::endl;
    return nullptr;
}
