#include "AppLayer.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Texture.h"
#include "Core/Renderer/Renderer2D.h"
#include "Core/Input/Input.h"

#include <iostream>

using namespace Engine;

void AppLayer::OnUpdate(float deltaTime)
{
    if (Input::GetKeyPressed(Input::Key_Code::KEY_CODE_1))
    {
        std::cout << "Pressed 1\n";
    }
    
}

void AppLayer::OnRender()
{
    glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}