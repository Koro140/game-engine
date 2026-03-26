#include "Renderer2D.h"

#include <glad/glad.h>

namespace Engine {
    Renderer2D::Renderer2D()
    {
        shader2D = new Shader(RESOURCES_PATH "shader/vertex.vert", RESOURCES_PATH "shader/fragment.frag");
        float vertices[] = {
             // positions      // texture coords
             0.5f,  0.5f,      1.0f, 1.0f,   // top right
             0.5f, -0.5f,      1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f,      0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f,      0.0f, 1.0f    // top left 
        };

        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void Renderer2D::destroy() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);

        delete shader2D;
    }
}