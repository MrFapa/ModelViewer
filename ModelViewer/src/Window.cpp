#include "Window.h"
#include "Logger.h"
#include "LibraryManager.h"

Window* Window::CreateWindow(WindowSettings settings)
{
	return new Window(settings.Width, settings.Height, settings.Title);
}

void Window::Update()
{
	m_IsValid = !glfwWindowShouldClose(m_Window);

	// Process events
	glfwPollEvents();

	// Swap front and back buffers
	glfwSwapBuffers(m_Window);
	
}

Window::Window(int width, int height, const char* title)
	: m_Width(width), m_Height(height), m_Title(title)
{
	LogInfo("Window '{}' with Size [{}, {}] gets created", m_Title, m_Width, m_Height);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

	m_IsValid = m_Window;
	if (!m_IsValid)
		return;

	glfwMakeContextCurrent(m_Window);

}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
}



