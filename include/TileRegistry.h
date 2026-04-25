#ifndef TILEREGISTRY_H
#define TILEREGISTRY_H

#include <map>
#include <string>
#include "TileDefinition.h"

class TileRegistry {

public:
    const TileDefinition* getTileDefinition(int tileId);

private:
    std::map<int, TileDefinition> tileDefinitions;
    void storeDefinition(int tileId, const TileDefinition& tileDefinition);

};


#endif