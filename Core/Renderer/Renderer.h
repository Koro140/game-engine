#pragma once

#include "Texture.h"
#include "Core/Common/structs.h"

namespace Engine
{
    namespace Renderer
    {
        struct Color {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };

        const Color RED =       {255,0,0,255};
        const Color BLUE =      {0,0,255,255};
        const Color YELLOW =    {255,255,0,255};
        const Color GREEN =     {0,255,0,255};

        void InitializeQuad();
        void DestroyQuad();

        // Drawing functions
        void DrawTexture(Texture &texture, Rectangle destination, float rotation, Color color);
        void DrawTextureSlice(Texture &texture, Rectangle source, Rectangle destination, float rotation, Color color);
        void ClearBackground(Color color);

        // Utils
        Color GetColorFromF(float r,float g,float b,float a);
    }
}
