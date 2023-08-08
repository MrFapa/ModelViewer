#pragma once

#include <unordered_map>
struct KeyInput
{
	int KeyCode;
	int Scancode;
	int Action;
	int Mods;

	KeyInput(int keycode, int scancode, int action, int mods) : KeyCode(keycode), Scancode(scancode), Action(action), Mods(mods) {}
	KeyInput() : KeyCode(-1), Scancode(0), Action(0), Mods(0){}

	operator bool() const
	{
		return KeyCode != -1;
	}
};

class Input
{
public:
	static Input& GetInstance();

	void Initialize(struct GLFWwindow* window);
	KeyInput GetKey(int key);
	void Update();
private:
	Input();
	static void KeyCallbackStatic(struct GLFWwindow* window, int keycode, int scancode, int action, int mods);
	void KeyCallback(int key, int scancode, int action, int mods);
	std::unordered_map<int, KeyInput> m_KeyMap;
	struct GLFWwindow* m_Window;
};