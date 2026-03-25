#pragma once

#include "Core/Layer.h"

class AppLayer : public Engine::Layer
{
public:
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
};