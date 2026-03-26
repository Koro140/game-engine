#pragma once

#include "Core/Layer.h"

class PauseLayer : public Engine::Layer
{
public:
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
};