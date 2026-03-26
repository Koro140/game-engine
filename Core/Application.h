#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Layer.h"  

#include <string>
#include <memory>
#include <vector>
#include <set>
#include <functional>

namespace Engine
{
    struct ApplicationSettings
    {
        std::string appName;
        int windowWidth;
        int windowHeight;
    };

    class Application
    {
    private:
        GLFWwindow* m_Window;
        bool m_AppRunning;

        std::vector<std::unique_ptr<Layer>> m_LayerStack;
        std::vector<std::function<void()>> m_CommandLayerStack;
    public:
        Application(const ApplicationSettings& settings);
        ~Application();
        void run();
        void stop();
		
		GLFWwindow* GetWindow() {
			return m_Window;
		}

        template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		void PushLayer()
		{
			m_CommandLayerStack.push_back([this]() {
				m_LayerStack.push_back(std::make_unique<TLayer>());
			});
		}
		
		void PopLayer()
		{
			m_CommandLayerStack.push_back([this]() {
				if (!m_LayerStack.empty())
					m_LayerStack.pop_back();
			});
		}
		
        template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		TLayer* GetLayer()
		{
			for (const auto& layer : m_LayerStack)
			{
				if (auto casted = dynamic_cast<TLayer*>(layer.get()))
				return casted;
			}
			return nullptr;
		}
		
		static Application &Get();
		friend class Layer;
    };    
}
