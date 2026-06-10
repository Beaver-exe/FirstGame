#include "core/Camera.h"
#include <iostream>

#include <external/glm/glm.hpp>
#include <external/glm/gtc/matrix_transform.hpp>

Camera::Camera(float width, float height, glm::vec3 position) {

    ScreenWidth = width;
    ScreenHeight = height;
    Position = position;
    Speed = 100.0f;
    Projection = glm::ortho(
        0.0f,
        width,
        height,
        0.0f,
        -1.0f,
        1.0f
    );
};

glm::mat4 Camera::GetViewMatrix() {
    return glm::translate(glm::mat4(1.0f), -Position);
};

glm::mat4 Camera::GetProjectionMatrix() {
    return glm::ortho(
        0.0f,
        ScreenWidth,
        ScreenHeight,
        0.0f,
        -1.0f,
        1.0f
    );
};
