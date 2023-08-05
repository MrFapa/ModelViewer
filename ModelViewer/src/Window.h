#pragma once
#include <functional>
#include "GLFW/glfw3.h"


class Window
{
public:

	struct WindowSettings
	{
		int Width;
		int Height;
		const char* Title;

		WindowSettings(int width, int height, const char* title)
			: Width(width), Height(height), Title(title) {}
	};

	static Window* CreateWindow(WindowSettings settings);
	void Update();

	GLFWwindow* GetGLFWWindow() { return m_Window; }
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	bool IsValid() const { return m_IsValid; }
private:
	Window(int width, int height, const char* title);
	~Window();

	GLFWwindow* m_Window;

	int m_Width;
	int m_Height;
	const char* m_Title;

	bool m_IsValid;
	
};
