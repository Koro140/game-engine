#pragma once

#include "Core/Layer.h"
#include "Core/Renderer/Texture.h"

#include "Core/Common/structs.h"

class AppLayer : public Engine::Layer
{
private:
    bool gamePaused;
    Engine::Rectangle playerPosition = {0,0,100,100};
public:
    AppLayer();
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
};