#include "Physics.h"

#include <algorithm>

namespace Engine::Physics
{   
    static constexpr glm::vec2 GRAVITY    {0.f, 9.81f};
    static constexpr float     SLOP       {0.01f};
    static constexpr float     CORRECTION {0.8f};

    // Check for intersections
    bool Intersects(const AABB &a, const AABB &b, CollisionInfo &infoOut)
    {
        float overlapX = std::min(a.Right(), b.Right()) - std::max(a.Left(), b.Left());
        float overlapY = std::min(a.Bottom(), b.Bottom()) - std::max(a.Top(), b.Top());
        if (overlapX <= 0.0f || overlapY <= 0.0f)
        {
            return false;
        }
        
        glm::vec2 aCenter = a.Center();
        glm::vec2 bCenter = b.Center();
        
        if (overlapX < overlapY)
        {
            infoOut.normal = {aCenter.x < bCenter.x ? -1.f : 1.f, 0.f};
            infoOut.depth  = overlapX;
        }
        else
        {
            infoOut.normal = {0.f, aCenter.y < bCenter.y ? -1.f : 1.f};
            infoOut.depth  = overlapY;
        }

        return true;
    }

    void ClearCollisionEvents(entt::registry& reg) {
        reg.clear<CollisionEvent>();
    }

    // Apply velocity and gravity
    void IntegrationSystem(entt::registry& reg, float dt) {
        auto view = reg.view<ActorBody, AABB>();
        view.each([dt](ActorBody& actor, AABB& aabb)
        {
            if (actor.useGravity)
            {
                actor.velocity += GRAVITY * dt;
            }
            
            actor.velocity *= (1.f - actor.drag * dt);
            aabb.position += actor.velocity * dt;
        });
    }

    // Resolve collisions between physics bodies
    void UpdatePhysicsBodiesCollision(entt::registry &reg)
    {
        // Updating Actors VS Static
        auto actors = reg.view<ActorBody, AABB>();
        auto statics = reg.view<StaticBody, AABB>();

        actors.each([&](entt::entity eA, ActorBody& actor, AABB& aabbA)
        {
            statics.each([&](entt::entity eS, AABB& aabbS)
            {
                CollisionInfo info;
                if (!Intersects(aabbA, aabbS, info)) {return;}
                
                float correction = std::max(info.depth - SLOP, 0.f) * CORRECTION;
                aabbA.position -= info.normal * correction;

                float velDot = glm::dot(actor.velocity, info.normal);
                if (velDot < 0.f)
                    actor.velocity -= info.normal * velDot * (1.f + actor.restitution);
                
                reg.emplace_or_replace<CollisionEvent>(eA, CollisionEvent{eS, info.normal, info.depth});
            });
        });

        // TODO : Actor VS Actor
    }

    void UpdatePhysics(entt::registry &reg, float dt)
    {
        ClearCollisionEvents(reg);
        IntegrationSystem(reg, dt);
        UpdatePhysicsBodiesCollision(reg);
    }
}