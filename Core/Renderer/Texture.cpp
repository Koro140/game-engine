#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <glad/glad.h>

Engine::Texture::Texture(const char* fileName)
{
    this->m_Height = 0;
    this->m_Width = 0;
    this->m_nChannels = 0;
    this->m_Id = 0;

    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* img = stbi_load(fileName, &m_Width, &m_Height, &m_nChannels, 0);
    if (img == nullptr) {
        std::cerr << "Couldn't open image file " << fileName << std::endl;
        return;
    }
    else {
        GLenum format;
        if (m_nChannels == 1)
            format = GL_RED;
        else if (m_nChannels == 3)
            format = GL_RGB;
        else if (m_nChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(img);

    std::cout << "Created " << fileName << " texture successfully" << std::endl;
}

void Engine::Texture::Bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Engine::Texture::Destroy() {
    if (m_Id != 0)
    {
        glDeleteTextures(1, &m_Id);

        this->m_Id = 0;
        this->m_Width = 0;
        this->m_Height = 0;
        this->m_nChannels = 0;
    }
}

Engine::Texture::~Texture()
{
    if (m_Id != 0) {
        glDeleteTextures(1, &m_Id);
    }
}