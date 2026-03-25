#include "Application.h"

#include <glad/glad.h>

#include <iostream>

#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Renderer2D.h"

Engine::Application::Application(const ApplicationSettings& settings)
{
    window = nullptr;
    appRunning = false;

    glfwInit();
    window = glfwCreateWindow(settings.windowWidth, settings.windowHeight, settings.appName.c_str(), NULL, NULL);
    if (window == nullptr) {
        std::cerr << "Couldn't initialize window\n";
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // INITIALIZE ALL SUBSYSTEMS HERE
    Renderer2D& renderer = Renderer2D::getInstance();


    // set appRunning if everythig went right
    appRunning = true;
}

void Engine::Application::run() {
    while (appRunning && !glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(this->window);
    }
}

Engine::Application::~Application() {
    // Destroy all subsystems here
    Renderer2D& renderer = Renderer2D::getInstance();
    renderer.destroy();


    glfwDestroyWindow(window);
    glfwTerminate();
}
