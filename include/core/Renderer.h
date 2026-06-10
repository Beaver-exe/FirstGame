#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include "Camera.h"

#include "resources/ResourceManager.h"

#include "tiles/TileMap.h"
#include "tiles/TileSet.h"

#include "entities/Player.h"

#include <external/glm/glm.hpp>

class Renderer {
public:
    Renderer(Shader& shader, ResourceManager& resourceManager);
    void renderTileMap(const TileMap& map, Camera camera);
    void renderPlayer(const Player& player);

private:
    void initQuad();
    void drawTile(
        int worldX,
        int worldY,
        int tileWidth,
        int tileHeight,
        unsigned int textureID,
        float u0,
        float v0,
        float u1,
        float v1
    );

    Shader& shader;
    ResourceManager& resourceManager;

    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;
    unsigned int quadEBO = 0;
};

#endif