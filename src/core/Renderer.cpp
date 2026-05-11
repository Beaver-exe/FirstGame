#include "core/Renderer.h"

#include <glad/glad.h>

#include <external/glm/gtc/matrix_transform.hpp>

Renderer::Renderer(Shader& shader, ResourceManager& resourceManager)
    : shader(shader),
      resourceManager(resourceManager)
{
    initQuad();
}

void Renderer::initQuad()
{
    float vertices[] = {
        // pos         // uv
        0.0f, 0.0f,    0.0f, 0.0f,
        1.0f, 0.0f,    1.0f, 0.0f,
        1.0f, 1.0f,    1.0f, 1.0f,
        0.0f, 1.0f,    0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glGenBuffers(1, &quadEBO);

    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Renderer::drawTile(
    int worldX,
    int worldY,
    int tileWidth,
    int tileHeight,
    unsigned int textureID,
    float u0,
    float v0,
    float u1,
    float v1
)
{
    float vertices[] = {
        // pos         // uv
        0.0f, 0.0f,    u0, v0,
        1.0f, 0.0f,    u1, v0,
        1.0f, 1.0f,    u1, v1,
        0.0f, 1.0f,    u0, v1
    };

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    shader.setMat4("model",
        glm::translate(glm::mat4(1.0f),
        glm::vec3(worldX, worldY, 0.0f)) *
        glm::scale(glm::mat4(1.0f),
        glm::vec3(tileWidth, tileHeight, 1.0f))
    );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::renderTileMap(const TileMap& map, Camera camera)
{
    shader.use();

    shader.setMat4("view", camera.GetViewMatrix());
    shader.setMat4("projection", camera.GetProjectionMatrix());
    shader.setVec3("spriteColor", 1.0f, 1.0f, 1.0f);

    int mapWidth = map.getWidth();
    int mapHeight = map.getHeight();

    int tileWidth = map.getTileWidth();
    int tileHeight = map.getTileHeight();

    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            uint32_t gid = map.getTile(x, y);

            if (gid == 0)
                continue;

            auto tileset = map.getTileSetForGid(gid);
            if (!tileset)
                continue;

            uint32_t localID = gid - tileset->firstGid;

            uint32_t tileX = localID % tileset->columns;
            uint32_t tileY = localID / tileset->columns;

            float px = tileX * tileset->tileWidth;
            float py = tileY * tileset->tileHeight;

            float u0 = px / tileset->imageWidth;
            float v0 = py / tileset->imageHeight;
            float u1 = (px + tileset->tileWidth) / tileset->imageWidth;
            float v1 = (py + tileset->tileHeight) / tileset->imageHeight;

            int worldX = x * tileWidth;
            int worldY = y * tileHeight;

        
            drawTile(
                worldX,
                worldY,
                tileWidth,
                tileHeight,
                tileset->textureID,
                u0, v0, u1, v1
            );
        }
    }
}