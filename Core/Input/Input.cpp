#include "Input.h"

#include "Core/Application.h"
namespace Engine
{
    bool Input::GetKeyPressed(Key_Code keyCode)
    {
        if (glfwGetKey(glfwGetCurrentContext(), keyCode) == GLFW_PRESS)
        {
            return true;
        }
        return false;
    }

    bool Input::GetKeyReleased(Key_Code keyCode)
    {
        if (glfwGetKey(Application::Get().GetWindow(), keyCode) == GLFW_RELEASE)
        {
            return true;
        }
        return false;
    }

    bool Input::GetMouseButtonPressed(Mouse_Button mouseButton) {
        if (glfwGetMouseButton(Application::Get().GetWindow(), mouseButton) == GLFW_PRESS)
        {
            
            return true;
        }
        return false;
    }


    bool Input::GetMouseButtonReleased(Mouse_Button mouseButton) {
        if (glfwGetMouseButton(Application::Get().GetWindow(), mouseButton) == GLFW_RELEASE)
        {
            
            return true;
        }
        return false;
    }

    void Input::GetMousePosition(double& x, double& y)
    {
        glfwGetCursorPos(Application::Get().GetWindow(), &x, &y);
    }
}