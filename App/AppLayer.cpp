#include "AppLayer.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "Core/Renderer/Renderer.h"
#include "Core/Input/Input.h"
#include "Core/Application.h"
#include "Core/ResourceManager/ResourceManager.h"
#include "Core/ECS/Components.h"

#include "PauseLayer.h"

#include <iostream>

using namespace Engine;

AppLayer::AppLayer() {
    m_player = m_registry.create();

    m_registry.emplace<ECS::Transform>(m_player,
        glm::vec2{ 100.f, 100.f }, // position
        glm::vec2{ 100.f, 100.f },   // scale
        0.f      // rotation
    );

    m_registry.emplace<ECS::Sprite>(m_player,
        ResourceManager::LoadTexture(RESOURCES_PATH "textures/container.jpg", "container_tex"),
        Renderer::Color{255,255,255,255}
    );
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
    
    auto& transform = m_registry.get<ECS::Transform>(m_player);

    float speed = 100.0f;
    if (Input::GetKeyDown(Input::KEY_CODE_DOWN))  transform.position.y += speed * deltaTime;
    if (Input::GetKeyDown(Input::KEY_CODE_UP))    transform.position.y -= speed * deltaTime;
    if (Input::GetKeyDown(Input::KEY_CODE_LEFT))  transform.position.x -= speed * deltaTime;
    if (Input::GetKeyDown(Input::KEY_CODE_RIGHT)) transform.position.x += speed * deltaTime;
}

void AppLayer::RendererSystem()
{
    auto view = m_registry.view<ECS::Transform, ECS::Sprite>();
    view.each([](ECS::Transform& t, ECS::Sprite& s) 
        {
            Renderer::DrawTexture(*s.texture, {t.position.x,t.position.y, t.scale.x, t.scale.y}, t.rotation, s.color);
        }
    );
}

void AppLayer::OnRender()
{
    Renderer::ClearBackground(Renderer::GetColorFromF(0.2f, 0.5f, 0.5f, 1.0f));
    RendererSystem();
}