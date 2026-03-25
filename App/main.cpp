#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Core/Application.h"
#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Texture.h"

int main(void) {
    Engine::ApplicationSettings settings;
    
    settings.appName = "Game";
    settings.windowHeight = 720;
    settings.windowWidth = 1280;
    Engine::Application app(settings);

    app.run();
}