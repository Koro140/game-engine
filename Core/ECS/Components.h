#include "Core/Renderer/Texture.h"

namespace Engine::ECS
{
    struct Transform {
        glm::vec2 position;
        glm::vec2 scale;

        float rotation;
    };

    struct Sprite {
        Texture* texture;
        Renderer::Color color;
    };
}