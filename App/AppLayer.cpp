#include "AppLayer.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "Core/Renderer/Renderer.h"
#include "Core/Input/Input.h"
#include "Core/Application.h"
#include "Core/ResourceManager/ResourceManager.h"
#include "Core/ECS/Components.h"
#include "Core/Physics/Physics.h"

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

    m_registry.emplace<Physics::ActorBody>(m_player,
        Physics::ActorBody{}
    );

    auto& body = m_registry.get<Physics::ActorBody>(m_player);
    body.useGravity = true;
    body.drag = 5.f;
    body.restitution = 0.7f;
    
    m_registry.emplace<Physics::AABB>(m_player,
        Physics::AABB{{100,100},{100,100}}
    );

    m_registry.emplace<ECS::Sprite>(m_player,
        ResourceManager::LoadTexture(RESOURCES_PATH "textures/container.jpg", "container_tex"),
        Renderer::Color{255,255,255,255}
    );

    m_cubesVec.push_back(m_registry.create());

    m_registry.emplace<ECS::Transform>(m_cubesVec[0],
        glm::vec2{ 100.f, 300.f }, // position
        glm::vec2{ 200.f, 200.f },   // scale
        0.f      // rotation
    );

    m_registry.emplace<Physics::StaticBody>(m_cubesVec[0],
        Physics::StaticBody{}
    );

    m_registry.emplace<Physics::AABB>(m_cubesVec[0],
        Physics::AABB{{100,300},{200,200}}
    );

    m_registry.emplace<ECS::Sprite>(m_cubesVec[0],
        ResourceManager::GetTexture("container_tex"),
        Renderer::Color{255,255,255,255}
    );

    ResourceManager::LoadAudio(RESOURCES_PATH "audio/jump.wav", "jump");
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
    
    auto& body = m_registry.get<Physics::ActorBody>(m_player);

    auto& transform = m_registry.get<ECS::Transform>(m_player);
    auto& aabb = m_registry.get<Physics::AABB>(m_player);

    float speed = 100.0f;
    if (Input::GetKeyDown(Input::KEY_CODE_DOWN))  body.velocity.y = speed;
    if (Input::GetKeyDown(Input::KEY_CODE_UP))    body.velocity.y = -speed;
    if (Input::GetKeyDown(Input::KEY_CODE_LEFT))  body.velocity.x = -speed;
    if (Input::GetKeyDown(Input::KEY_CODE_RIGHT)) body.velocity.x = speed;
    
    // Player Jump
    if (Input::GetKeyPressed(Input::KEY_CODE_SPACE))
    {
        ResourceManager::GetAudio("jump")->play();
        body.velocity.y = -1000.0f;
    }
    

    Physics::UpdatePhysics(m_registry, deltaTime);
    transform.position = aabb.position;    
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
