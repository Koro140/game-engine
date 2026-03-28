#pragma once

#include "Core/Layer.h"
#include "Core/Renderer/Texture.h"

#include "Core/Common/structs.h"

#include <entt/entt.hpp>

class AppLayer : public Engine::Layer
{
public:    
    AppLayer();
    void OnRender() override;
    void OnUpdate(float deltaTime) override;

private:
    entt::registry m_registry;
    entt::entity   m_player;

    bool gamePaused = false;

    void RendererSystem();
};