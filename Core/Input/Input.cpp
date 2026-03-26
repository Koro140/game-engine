#include "Input.h"

#include "Core/Application.h"
namespace Engine
{
    enum Key_State {
        UP,
        DOWN,
        PRESSED,
        RELEASED,
    };

    static Key_State s_Keys[GLFW_KEY_LAST];
    static Key_State s_MouseButtons[GLFW_MOUSE_BUTTON_LAST];

    bool Input::GetKeyReleased(Key_Code keyCode)
    {
        return s_Keys[keyCode] == RELEASED;
    }

    bool Input::GetKeyPressed(Key_Code keyCode)
    {
        return s_Keys[keyCode] == PRESSED;
    }

    bool Input::GetKeyDown(Key_Code keyCode)
    {
        return s_Keys[keyCode] == DOWN;
    }

    bool Input::GetKeyUp(Key_Code keyCode)
    {
        return s_Keys[keyCode] == UP;
    }


    bool Input::GetMouseButtonReleased(Mouse_Button mouseButton)
    {
        return s_MouseButtons[mouseButton] == RELEASED;
    }

    bool Input::GetMouseButtonPressed(Mouse_Button mouseButton)
    {
        return s_MouseButtons[mouseButton] == PRESSED;
    }

    bool Input::GetMouseButtonDown(Mouse_Button mouseButton)
    {
        return s_MouseButtons[mouseButton] == DOWN;
    }

    bool Input::GetMouseButtonUp(Mouse_Button mouseButton)
    {
        return s_MouseButtons[mouseButton] == UP;
    }

    void Input::Update()
    {
        for (int key = 0; key < GLFW_KEY_LAST; key++) {
            bool isKeyDown = glfwGetKey(Application::Get().GetWindow(), key) == GLFW_PRESS;

            switch (s_Keys[key])
            {
            case Key_State::UP:
                s_Keys[key] = isKeyDown ? Key_State::PRESSED : Key_State::UP;
                break;
            case Key_State::PRESSED:
                s_Keys[key] = isKeyDown ? Key_State::DOWN : Key_State::RELEASED;
                break;
                    
            case Key_State::RELEASED:
                s_Keys[key] = isKeyDown ? Key_State::PRESSED : Key_State::UP;
                break;

            case Key_State::DOWN:
                s_Keys[key] = isKeyDown ? Key_State::DOWN : Key_State::RELEASED;
                break;
                
            default:
                break;
            }
        }

        for (int button = 0; button < GLFW_MOUSE_BUTTON_LAST; button++) {
            bool isKeyDown = glfwGetMouseButton(Application::Get().GetWindow(), button) == GLFW_PRESS;

            switch (s_MouseButtons[button])
            {
            case Key_State::UP:
                s_MouseButtons[button] = isKeyDown ? Key_State::PRESSED : Key_State::UP;
                break;
            case Key_State::PRESSED:
                s_MouseButtons[button] = isKeyDown ? Key_State::DOWN : Key_State::RELEASED;
                break;
                    
            case Key_State::RELEASED:
                s_MouseButtons[button] = isKeyDown ? Key_State::PRESSED : Key_State::UP;
                break;

            case Key_State::DOWN:
                s_MouseButtons[button] = isKeyDown ? Key_State::DOWN : Key_State::RELEASED;
                break;
                
            default:
                break;
            }
        }
    }

    void Input::GetMousePosition(double& x, double& y)
    {
        glfwGetCursorPos(Application::Get().GetWindow(), &x, &y);
    }
}