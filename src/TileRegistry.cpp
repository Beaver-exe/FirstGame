#include "TileRegistry.h"
#include "TileDefinition.h"

#include <iostream>

void TileRegistry::storeDefinition(int tileId, const TileDefinition& tileDefinition) {
    tileDefinitions[tileId] = tileDefinition;
}

const TileDefinition* TileRegistry::getTileDefinition(const int tileId) {
    
    auto definition = tileDefinitions.find(tileId);
    if (definition != tileDefinitions.end()) {
        return &definition->second;
    }

    std::cout << "ERROR: Tile Definition not found in registry: " << tileId << std::endl;
    return nullptr;
}
