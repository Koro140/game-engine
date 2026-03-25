#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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
        GLFWwindow* window;
        bool appRunning;
    public:
        Application(const ApplicationSettings& settings);
        ~Application();
        
        void attachLayer();
        void run();
    };    
}
