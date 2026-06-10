#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <external/glm/glm.hpp>
#include <external/glm/gtc/matrix_transform.hpp>

class Camera {    
public:
    Camera(float width, float height, glm::vec3 position);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    float Speed;

private: 
    glm::vec3 Position;
    float ScreenWidth;
    float ScreenHeight;
    glm::mat4 Projection;

};

#endif