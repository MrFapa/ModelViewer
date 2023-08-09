#pragma once

#include <unordered_map>
#include <glm/vec2.hpp>

struct KeyInput
{
	int KeyCode;
	int Scancode;
	int Action;
	int Mods;

	KeyInput(int keycode, int scancode, int action, int mods) : KeyCode(keycode), Scancode(scancode), Action(action), Mods(mods) {}
	KeyInput() : KeyCode(-1), Scancode(-1), Action(-1), Mods(-1){}

	operator bool() const
	{
		return KeyCode > -1;
	}
};

struct MouseInput
{
	int Button;
	int Action;
	int Mods;

	MouseInput(int button, int action, int mods) : Button(button), Action(action), Mods(mods){}
	MouseInput() : Button(-1), Action(-1), Mods(-1) {}

	operator bool() const
	{
		return Button > -1;
	}
};

class Input
{
public:
	static Input& GetInstance();

	static void Initialize(struct GLFWwindow* window);
	static void Update();
	static KeyInput GetKey(int key);
	static MouseInput GetMouseButton(int button);

	static glm::vec2 GetMousePosition();
	static glm::vec2 GetDeltaMousePosition();
private:
	Input();
	static void KeyCallbackStatic(struct GLFWwindow* window, int keycode, int scancode, int action, int mods);
	void KeyCallback(int key, int scancode, int action, int mods);
	static void MouseButtonCallbackStatic(struct GLFWwindow* window, int button, int action, int mods);
	void MouseButtonCallback(int button, int action, int mods);

private:
	std::unordered_map<int, KeyInput> m_KeyMap;
	std::unordered_map<int, MouseInput> m_MouseMap;
	struct GLFWwindow* m_Window;
	double m_MouseX = 0;
	double m_MouseY = 0;
	double m_LastMouseX = 0;
	double m_LastMouseY = 0;
};