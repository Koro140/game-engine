#include "AppLayer.h"

#include <glad/glad.h>

#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Texture.h"

void AppLayer::OnUpdate(float deltaTime)
{

}

void AppLayer::OnRender()
{
    glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}