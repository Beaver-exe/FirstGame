#ifndef TILEREGISTRY_H
#define TILEREGISTRY_H

#include <map>
#include <string>
#include "TileDefinition.h"

class TileRegistry {

public:
    const TileDefinition* getTileDefinition(const std::string& tileName);

private:
    std::map<std::string, TileDefinition> tileDefinitions;
    void storeDefinition(const std::string& tileName, const TileDefinition& tileDefinition);

};


#endif