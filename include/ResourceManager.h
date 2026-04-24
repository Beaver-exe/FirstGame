#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "TextureLoader.h"


#include <map>
#include <string>

class ResourceManager 
{
public:
    void registerResources(const std::string& pathName);    
    unsigned int getTexture(const std::string& textureName);
    
private:
    void storeTexture(const std::string&, unsigned int textureId);
    std::map<std::string, unsigned int> textures;
    std::map<std::string, std::string> registry;

};

#endif