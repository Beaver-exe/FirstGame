#include "ResourceManager.h"
#include "TextureLoader.h"

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>


void ResourceManager::storeTexture(const std::string& textureName, unsigned int textureId) {
    textures[textureName] = textureId;
}

void ResourceManager::registerResources(const std::string& pathName) {
    
    std::ifstream registryFile(pathName);
    std::string line;

    while (std::getline(registryFile, line)) {
        std::cout << line << std::endl;
        std::istringstream iss(line);
        std::string textureName;
        std::string texturePath;

        iss >> textureName;
        iss >> texturePath;


        registry[textureName] = texturePath;
    }

}

unsigned int ResourceManager::getTexture(const std::string& textureName) {

    auto texture = textures.find(textureName);
    if (texture != textures.end())
    {
        return texture->second;
    }

    auto regIt = registry.find(textureName);
    if (regIt == registry.end())
    {
        std::cout << "ERROR: Texture not found in registry: " << textureName << std::endl;
        return 0;
    }

    const std::string& path = regIt->second;
    unsigned int textureId = loadTexture(path);

    storeTexture(textureName, textureId);

    return textureId;
}
