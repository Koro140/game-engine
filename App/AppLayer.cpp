#include "AppLayer.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "Core/Renderer/Renderer.h"
#include "Core/Input/Input.h"
#include "Core/Application.h"
#include "Core/ResourceManager/ResourceManager.h"

#include "PauseLayer.h"

#include <iostream>

using namespace Engine;

Texture* testTexture;

AppLayer::AppLayer() {
    testTexture = ResourceManager::LoadTexture(RESOURCES_PATH "textures/container.jpg", "container_tex");
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
    Renderer::ClearBackground(Renderer::GetColorFromF(0.2f, 0.5f, 0.5f, 1.0f));
    Renderer::DrawTexture(*testTexture, playerPosition, 0, {255,255,255,255});

    Renderer::DrawTextureSlice(*testTexture, {0,0,testTexture->m_Width * 2.0f,testTexture->m_Height * 2.0f},{100,100,100,100}, 0, {255,255,255,255});
}