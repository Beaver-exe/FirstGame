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
#include "stb_image.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Camera& camera);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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

    float vertices[] = {
        // position (pixels)   // tex coords
        0.0f,   0.0f,          0.0f, 0.0f,
        64.0f,  0.0f,          1.0f, 0.0f,
        64.0f,  64.0f,         1.0f, 1.0f,
        0.0f,   64.0f,         0.0f, 1.0f
    };

    int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    unsigned int container = resourceManager.getTexture("awesomeface");
    ourShader.use();
    ourShader.setInt("image", 0);


    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, camera);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();

        ourShader.setVec3("spriteColor", 1.0f, 1.0f, 1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);
        glm::mat4 projection = camera.GetProjectionMatrix();
        ourShader.setMat4("projection", projection);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, container);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
