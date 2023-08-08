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

void Input::Update()
{
    std::vector<int> keysToRemove(m_KeyMap.size());

    for (auto& it : m_KeyMap)
    {
        keysToRemove.push_back(it.first);
    }
    
    for (int key : keysToRemove)
    {
        m_KeyMap.erase(key);
    }
}


void Input::KeyCallbackStatic(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
    Input& instance = GetInstance();
    instance.KeyCallback(keycode, scancode, action, mods);
}

void Input::KeyCallback(int keycode, int scancode, int action, int mods)
{
    m_KeyMap[keycode] = KeyInput{ keycode, scancode, action, mods };
}

