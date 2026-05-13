#include "loader/TextureLoader.h"
#include "external/stb_image.h"

#include <glad/glad.h>
#include <iostream>

unsigned int loadTexture(const std::string& textPath) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(false);

    unsigned char* data = stbi_load(
        textPath.c_str(),
        &width,
        &height,
        &nrChannels,
        STBI_rgb_alpha
    );

    if (data) {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data
        );

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture: " << textPath << std::endl;
    }

    stbi_image_free(data);

    return texture;
}