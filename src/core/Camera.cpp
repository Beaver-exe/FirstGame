#include "Camera.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float width, float height, glm::vec3 position) {

    ScreenWidth = width;
    ScreenHeight = height;
    Position = position;
    Speed = 100.0f;
    Projection = glm::ortho(
        0.0f, width,
        0.0f, height,
        -1.0f, 1.0f
    );
};

glm::mat4 Camera::GetViewMatrix() {
    return glm::translate(glm::mat4(1.0f), -Position);
};

glm::mat4 Camera::GetProjectionMatrix() {
    return glm::ortho(
        0.0f, ScreenWidth,
        0.0f, ScreenHeight,
        -1.0f, 1.0f
    );
};

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {

    float velocity = Speed * deltaTime;

    if (direction == LEFT)
        Position.x -= velocity;
    if (direction == RIGHT) 
        Position.x += velocity;
    if (direction == UP)
        Position.y += velocity;
    if (direction == DOWN)
        Position.y -= velocity;
}   