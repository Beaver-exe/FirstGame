#include "loader/TileSetLoader.h"
#include "loader/TextureLoader.h"

#include "tiles/TileSet.h"

#include "external/tinyxml2.h"
#include "external/stb_image.h"

#include <iostream>

using namespace tinyxml2;

std::shared_ptr<TileSet>
TileSetLoader::load(const std::string& tsxPath, uint32_t firstGid) {
    XMLDocument doc;

    if (doc.LoadFile(tsxPath.c_str()) != XML_SUCCESS) {
        std::cerr << "Failed to load TSX: " << tsxPath << "\n";
        return nullptr;
    }

    XMLElement* tileSetElement = doc.FirstChildElement("tileset");

    if (!tileSetElement) {
        std::cerr << "Invalid TSX format\n";
        return nullptr;
    }

    uint32_t tileWidth = 0;
    uint32_t tileHeight = 0;
    uint32_t tileCount = 0;
    uint32_t columns = 0;

    tileSetElement->QueryUnsignedAttribute("tilewidth", &tileWidth);
    tileSetElement->QueryUnsignedAttribute("tileheight", &tileHeight);
    tileSetElement->QueryUnsignedAttribute("tilecount", &tileCount);
    tileSetElement->QueryUnsignedAttribute("columns", &columns);

    XMLElement* imageElement = tileSetElement->FirstChildElement("image");

    if (!imageElement) {
        std::cerr << "Invalid TSX format (missing image)\n";
        return nullptr;
    }

    const char* source = imageElement->Attribute("source");

    if (!source) {
        std::cerr << "TSX image missing source path\n";
        return nullptr;
    }

    int imageWidth = 0;
    int imageHeight = 0;
    int channels = 0;

    stbi_set_flip_vertically_on_load(false);

    const std::string assetRoot = "assets/";
    std::string imagePath = assetRoot + source;

    unsigned char* data = stbi_load(imagePath.c_str(), &imageWidth, &imageHeight, &channels, 0);

    if (!data) {
        std::cerr << "Failed to load image for size check: " << imagePath << "\n";
        return nullptr;
    }

    stbi_image_free(data);

    unsigned int textureID = loadTexture(imagePath);

    return std::make_shared<TileSet>(
        firstGid,
        tileWidth,
        tileHeight,
        tileCount,
        columns,
        imageWidth,
        imageHeight,
        imagePath,
        textureID
    );
}