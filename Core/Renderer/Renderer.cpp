#include "Renderer.h"

#include "Core/Renderer/Shader.h"
#include "Core/Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine {
    static unsigned int quadVAO = 0;
    static unsigned int quadVBO = 0;

    Shader* shader2D = nullptr;

    void Renderer::InitializeQuad()
    {
        shader2D = new Shader(RESOURCES_PATH "shader/vertex2D.vert", RESOURCES_PATH "shader/fragment2D.frag");

        int windowWidth;
        int windowHeight;
        glfwGetFramebufferSize(Application::Get().GetWindow(), &windowWidth, &windowHeight);
        
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight), 0.0f, -1.0f, 1.0f);  
        shader2D->use();
        shader2D->setMat4("projection", projection);
        
        float vertices[] = { 
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 
        
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &quadVAO);
        glBindVertexArray(quadVAO);

        glGenBuffers(1, &quadVBO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void Renderer::DestroyQuad() {
        glDeleteBuffers(1, &quadVBO);
        glDeleteVertexArrays(1, &quadVAO);

        delete shader2D;
    }

    void Renderer::DrawTexture(Texture& texture, Rectangle destination, float rotation, Color color) {
        DrawTextureSlice(texture, {0,0,(float)texture.m_Width, (float)texture.m_Height}, destination, rotation, color);
    }

    void Renderer::DrawTextureSlice(Texture& texture, Rectangle source, Rectangle destination, float rotation, Color color) {

        glm::vec2 position = {destination.x, destination.y};
        glm::vec2 size = {destination.width, destination.height};
        glm::vec3 v_color = {color.r / 255.0f, color.g / 255.0f, color.b / 255.0f};
        
        glm::vec4 uvRect = {
            source.x / (float)texture.m_Width,
            source.y / (float)texture.m_Height,
            (source.x + source.width) / (float)texture.m_Width,
            (source.y + source.height) / (float)texture.m_Height
        };

        shader2D->use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f));  
        
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
        
        model = glm::scale(model, glm::vec3(size, 1.0f)); 
        
        shader2D->setMat4("model", model);
        shader2D->setVec3("spriteColor", v_color);
        shader2D->setVec4("uvRect", uvRect);

        glActiveTexture(GL_TEXTURE0);
        texture.Bind();
        
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
    
    void Renderer::ClearBackground(Color color) {
        glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    Renderer::Color Renderer::GetColorFromF(float r,float g,float b,float a) {
        return {
            static_cast<unsigned char>(r * 255), static_cast<unsigned char>(g * 255),
            static_cast<unsigned char>(b * 255), static_cast<unsigned char>(a * 255)
        };
    }
}