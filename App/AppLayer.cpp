#include "AppLayer.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "Core/Renderer/Renderer.h"
#include "Core/Input/Input.h"
#include "Core/Application.h"

#include "PauseLayer.h"

#include <iostream>

using namespace Engine;

AppLayer::AppLayer() : testTexture(RESOURCES_PATH "textures/container.jpg") {

}

void AppLayer::OnUpdate(float deltaTime)
{
    if (Input::GetKeyPressed(Input::KEY_CODE_F1))
    {
        if (!gamePaused)
        {
            Application::Get().PushLayer<PauseLayer>();
            gamePaused = true;
        }
        else {
            Application::Get().PopLayer();
            gamePaused = false;
        }
    }

    if (Input::GetKeyPressed(Input::KEY_CODE_ESCAPE))
    {
        Application::Get().stop();
    }
    

    float speed = 100.0f;
    if (Input::GetKeyDown(Input::KEY_CODE_DOWN))  playerPosition.y += speed * deltaTime;
    if (Input::GetKeyDown(Input::KEY_CODE_UP))    playerPosition.y -= speed * deltaTime;
    if (Input::GetKeyDown(Input::KEY_CODE_LEFT))  playerPosition.x -= speed * deltaTime;
    if (Input::GetKeyDown(Input::KEY_CODE_RIGHT)) playerPosition.x += speed * deltaTime;
    
}

void AppLayer::OnRender()
{
    glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Renderer::DrawTexture(testTexture, playerPosition, 0, {255,255,255,255});
}