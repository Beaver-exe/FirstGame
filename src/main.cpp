#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include <external/glm/glm.hpp>
#include <external/glm/gtc/matrix_transform.hpp>
#include <external/glm/gtc/type_ptr.hpp>

#include "world/World.h"

#include "core/Shader.h"
#include "core/Camera.h"
#include "core/Renderer.h"

#include "resources/ResourceManager.h"

#include "tiles/TileDefinition.h"
#include "tiles/TileMap.h"

#include "loader/MapLoader.h"

#include "external/stb_image.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, InputState& input, Player& player);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float fpsTimer = 0.0f;
int frameCount = 0;

int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfwGetPrimaryMonitor()
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "First Game", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    glClearColor(0.2f, 0.5f, 0.7f, 1.0f);

    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f));
    Shader ourShader("shaders/shader.vert", "shaders/shader.frag");

    ResourceManager resourceManager;
    resourceManager.registerResources("assets/registry.txt");

    glm::ivec2 startPos(18, 18);

    World world("assets/maps/TestMap.tmj", startPos, true);
    Player& player = world.getPlayer();

    Renderer renderer(ourShader, resourceManager);

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = static_cast<float>(glfwGetTime());

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        frameCount++;

        fpsTimer += deltaTime;

        if (fpsTimer >= 1.0f) {
            float fps = frameCount / fpsTimer;

            std::string newTitle = "FPS - " + std::to_string(fps);

            glfwSetWindowTitle(window, newTitle.c_str());

            fpsTimer = 0.0f;
            frameCount = 0;
        }

        InputState input;

        processInput(window, input, player);
        player.update(deltaTime);
        glClear(GL_COLOR_BUFFER_BIT);
        
        renderer.renderTileMap(world.getMap(), camera);
        renderer.renderPlayer(player);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, InputState& input, Player& player) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        input.up = true;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        input.down = true;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        input.left = true;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        input.right = true;
    }

    player.setInputState(input);

}
