#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "TileDefinition.h"
#include "TileMap.h"
#include "Renderer.h"

#include "stb_image.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Camera& camera);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float fpsTimer = 0.0f;
int frameCount = 0;

int main(void)
{
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

    TileDefinition wall = TileDefinition(1, "path", "wall", true, true, true);
    TileDefinition container = TileDefinition(2, "wood", "container", true, true, true);


    TileRegistry tileRegistry;
    tileRegistry.storeDefinition(1, wall);
    tileRegistry.storeDefinition(2, container);

    TileMap map = TileMap(150, 150);
    map.generateMap();

    Renderer renderer(ourShader, tileRegistry, resourceManager);

    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        frameCount++;
        if (deltaTime >= 1.0 / 30.0)
        {
            std::string FPS = std::to_string((1.0 / deltaTime) * frameCount);
            std::string newTitle = "FPS- " + FPS;
            glfwSetWindowTitle(window, newTitle.c_str());
            lastFrame = currentFrame;
            frameCount = 0;
        }

        processInput(window, camera);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.renderTileMap(map, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, Camera& camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}
