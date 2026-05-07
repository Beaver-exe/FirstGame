#ifndef RENDERER_H
#define RENDERER_H

#include "tiles/TileMap.h"
#include "Shader.h"
#include "tiles/TileRegistry.h"
#include "resources/ResourceManager.h"
#include "Camera.h"

class Renderer {
public:
    Renderer(Shader& shader, TileRegistry& tileRegistry, ResourceManager& resourceManager);
    void renderTileMap(const TileMap& map, Camera camera);

private:
    void drawTile(int worldX, int worldY, unsigned int textureId);

    Shader& shader;
    TileRegistry& tileRegistry;
    ResourceManager& resourceManager;
    unsigned int quadVAO, quadVBO, quadEBO;
    float tileSize = 64.0f;

};

#endif