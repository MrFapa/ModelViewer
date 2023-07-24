#include "Window.h"

Window* Window::CreateWindow(WindowSettings settings)
{
	return new Window(settings.Width, settings.Height, settings.Title);
}

void Window::OnUpdate()
{
	m_IsValid = !glfwWindowShouldClose(m_Window);

	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);


	m_UpdateFunction();


	/* Swap front and back buffers */
	glfwSwapBuffers(m_Window);

	/* Poll for and process events */
	glfwPollEvents();
	
}

void Window::SetUpdateFunction(const std::function<void()>& updateFunction)
{
	m_UpdateFunction = updateFunction;
}

Window::Window(int width, int height, const char* title)
	: m_Width(width), m_Height(height), m_Title(title)
{
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

	m_IsValid = m_Window;
	if (m_IsValid)
		return;

	glfwMakeContextCurrent(m_Window);

}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
}



