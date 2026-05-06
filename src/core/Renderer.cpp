#include "Renderer.h"
#include "TileMap.h"

#include <glad/glad.h>

Renderer::Renderer(Shader& shader, TileRegistry& tileRegistry, ResourceManager& resourceManager) :
 shader(shader), tileRegistry(tileRegistry), resourceManager(resourceManager) {

    float vertices[] = {
        0.0f, 0.0f,   0.0f, 0.0f,
        1.0f, 0.0f,   1.0f, 0.0f,
        1.0f, 1.0f,   1.0f, 1.0f,
        0.0f, 1.0f,   0.0f, 1.0f
    };

    int indices[] = {
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


void Renderer::drawTile(int worldX, int worldY, unsigned int textureId) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(worldX, worldY, 0.0f));
    model = glm::scale(model, glm::vec3(tileSize, tileSize, 1.0f));

    shader.setMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glBindVertexArray(quadVAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}


void Renderer::renderTileMap(const TileMap& map, Camera camera) {
    
    int mapWidth = map.getWidth();
    int mapHeight = map.getHeight();

    shader.use();
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix();

    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    shader.setVec3("spriteColor", 1.0f, 1.0f, 1.0f);

    for (int x = 0; x < mapWidth; x++) {
        for (int y = 0; y < mapHeight; y++) {

            int worldX = x * tileSize;
            int worldY = y * tileSize;

            int tileId = map.getTile(x, y);

            const TileDefinition* tileDef = tileRegistry.getTileDefinition(tileId);
            if (!tileDef)
                continue;

            std::string texName = tileDef->getTextureName();
            unsigned int texId =  resourceManager.getTexture(texName);

            drawTile(worldX, worldY, texId);

        }
    }
}



