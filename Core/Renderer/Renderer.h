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

        void InitializeQuad();
        void DestroyQuad();
        void DrawTexture(Texture &texture, Rectangle destination, float rotation, Color color);
    }
}
