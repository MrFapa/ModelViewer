#include "Input.h"
#include "GLFW/glfw3.h"


Input::Input()
{
    m_Window = nullptr;
}

Input& Input::GetInstance()
{
    static Input instance;
    return instance;
}

void Input::Initialize(GLFWwindow* window)
{
    m_Window = window;
    glfwSetKeyCallback(m_Window, KeyCallbackStatic);
    glfwSetMouseButtonCallback(m_Window, MouseButtonCallbackStatic);
}

KeyInput Input::GetKey(int key)
{
    auto& instance = GetInstance();
    auto it = instance.m_KeyMap.find(key);
    if (it != instance.m_KeyMap.end())
    {
        return it->second;
    }
    return KeyInput();
}

MouseInput Input::GetMouseButton(int button)
{
    auto& instance = GetInstance();
    auto it = instance.m_MouseMap.find(button);
    if (it != instance.m_MouseMap.end())
    {
        return it->second;
    }
    return MouseInput();
}


void Input::ClearInputs()
{
    // Keyboard
    std::vector<int> keysToRemove(m_KeyMap.size());

    for (auto& it : m_KeyMap)
    {
        keysToRemove.push_back(it.first);
    }
    
    for (int key : keysToRemove)
    {
        m_KeyMap.erase(key);
    }

    // Mouse
    std::vector<int> buttonsToRemove(m_MouseMap.size());

    for (auto& it : m_MouseMap)
    {
        buttonsToRemove.push_back(it.first);
    }

    for (int button : buttonsToRemove)
    {
        m_MouseMap.erase(button);
    }
}


void Input::KeyCallbackStatic(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
    Input& instance = GetInstance();
    instance.KeyCallback(keycode, scancode, action, mods);
}

void Input::KeyCallback(int keycode, int scancode, int action, int mods)
{
    action = (action == GLFW_REPEAT) ? GLFW_PRESS : action;
    m_KeyMap[keycode] = KeyInput{ keycode, scancode, (action), mods};
}

void Input::MouseButtonCallbackStatic(GLFWwindow* window, int button, int action, int mods)
{
    Input& instance = GetInstance();
    instance.MouseButtonCallback(button, action, mods);
}

void Input::MouseButtonCallback(int button, int action, int mods)
{
    m_MouseMap[button] = MouseInput{ button, action, mods };
}



