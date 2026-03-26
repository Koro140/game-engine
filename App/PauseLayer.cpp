#include "PauseLayer.h"

#include <glad/glad.h>

#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Texture.h"

#include <iostream>

void PauseLayer::OnUpdate(float deltaTime)
{
    std::cout << "PauseLayer::OnUpdate: hello" << std::endl;
}

void PauseLayer::OnRender()
{
    // Red
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}