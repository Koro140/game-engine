#pragma once

#include <glm/glm.hpp>
#include <entt/entt.hpp>

namespace Engine::Physics
{
    struct AABB
    {
        glm::vec2 position;
        glm::vec2 size;

        glm::vec2 Min() const { return position; }
        glm::vec2 Max() const { return position + size; }

        // Helpers
        glm::vec2 Center() const { return position + size * 0.5f; }
        float Left() const { return position.x; }
        float Right() const { return position.x + size.x; }
        float Top() const { return position.y; }
        float Bottom() const { return position.y + size.y; }
    };
    
    struct CollisionEvent {
        entt::entity other;
        glm::vec2 normal;
        float depth;
    };

    struct CollisionInfo {
        glm::vec2 normal;
        float depth;
    };

    struct ActorBody
    {
        glm::vec2 velocity{0.0f,0.0f};
        float mass{1.f};
        float restitution{0.2f};
        float drag {0.05f};
        bool useGravity {true};
    };
    
    struct StaticBody {};

    bool Intersects(const AABB& a,const AABB& b, CollisionInfo& infoOut);
    void UpdatePhysics(entt::registry& reg, float dt);
}