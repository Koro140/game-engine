#pragma once

namespace Engine
{
    class Layer
    {
    private:
    public:
        ~Layer() = default;

        virtual void OnUpdate(float deltaTime) {};
        virtual void OnEvent() {};
        virtual void OnRender() {};
    };    
}