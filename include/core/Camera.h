#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Camera {    
public:
    Camera(float width, float height, glm::vec3 position);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    float Speed;

private: 
    glm::vec3 Position;
    float ScreenWidth;
    float ScreenHeight;
    glm::mat4 Projection;

};

#endif