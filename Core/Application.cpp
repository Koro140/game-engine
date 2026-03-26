#include "Application.h"

#include <glad/glad.h>

#include <iostream>
#include <assert.h>

#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Renderer2D.h"

namespace Engine
{

    static Application* s_Application = nullptr;

    Application::Application(const ApplicationSettings& settings)
    {

        s_Application = this;

        m_Window = nullptr;
        m_AppRunning = false;

        glfwInit();
        m_Window = glfwCreateWindow(settings.windowWidth, settings.windowHeight, settings.appName.c_str(), NULL, NULL);
        if (m_Window == nullptr) {
            std::cerr << "Couldn't initialize window\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_Window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        // INITIALIZE ALL SUBSYSTEMS HERE
        Renderer2D& renderer = Renderer2D::getInstance();


        // set appRunning if everythig went right
        m_AppRunning = true;
    }

    void Application::run()
    {
        float lastFrameTime = 0;
        while (m_AppRunning && !glfwWindowShouldClose(m_Window))
        {
            float currentFrameTime = static_cast<float>(glfwGetTime());
            float deltaTime = currentFrameTime - lastFrameTime;
            lastFrameTime = currentFrameTime;

            glfwPollEvents();

            for (const std::unique_ptr<Layer>& layer : m_LayerStack)
            {
                layer->OnUpdate(deltaTime);
            }

            for (const std::unique_ptr<Layer>& layer : m_LayerStack)
            {
                layer->OnRender();
            }

            glfwSwapBuffers(this->m_Window);
        }
    }

    Application::~Application() {
        // Destroy all subsystems here
        Renderer2D& renderer = Renderer2D::getInstance();
        renderer.destroy();


        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    Application& Application::Get() {
        assert(s_Application);
        return *s_Application;
    }
}