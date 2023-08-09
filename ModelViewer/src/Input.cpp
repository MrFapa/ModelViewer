#include "Input.h"
#include "GLFW/glfw3.h"

Input::Input()
{
    m_Window = nullptr;
}

// Public Functions
Input& Input::GetInstance()
{
    static Input instance;
    return instance;
}

void Input::Initialize(GLFWwindow* window)
{
    auto& instance = GetInstance();
    instance.m_Window = window;
    glfwSetKeyCallback(instance.m_Window, KeyCallbackStatic);
    glfwSetMouseButtonCallback(instance.m_Window, MouseButtonCallbackStatic);
}

void Input::Update()
{
    auto& instance = GetInstance();
    instance.m_LastMouseX = instance.m_MouseX;
    instance.m_LastMouseY = instance.m_MouseY;
    glfwGetCursorPos(instance.m_Window, &instance.m_MouseX, &instance.m_MouseY);
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

glm::vec2 Input::GetMousePosition()
{
    const auto& instance = GetInstance();
    return { static_cast<float>(instance.m_MouseX), static_cast<float>(instance.m_MouseY)};
}

glm::vec2 Input::GetDeltaMousePosition()
{
    const auto& instance = GetInstance();
    return { static_cast<float>(instance.m_MouseX - instance.m_LastMouseX),
            static_cast<float>(instance.m_MouseY - instance.m_LastMouseY) };
}



// Private Functions

// Key Input Handling
void Input::KeyCallbackStatic(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
    Input& instance = GetInstance();
    instance.KeyCallback(keycode, scancode, action, mods);
}

void Input::KeyCallback(int keycode, int scancode, int action, int mods)
{
    action = (action == GLFW_REPEAT) ? GLFW_PRESS : action;
    m_KeyMap[keycode] = KeyInput{ keycode, scancode, action, mods };
}

// Mouse Input Handling
void Input::MouseButtonCallbackStatic(GLFWwindow* window, int button, int action, int mods)
{
    Input& instance = GetInstance();
    instance.MouseButtonCallback(button, action, mods);
}

void Input::MouseButtonCallback(int button, int action, int mods)
{
    m_MouseMap[button] = MouseInput{ button, action, mods };
}
