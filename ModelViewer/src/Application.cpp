#include "Application.h"

#include "Window.h"
#include "iostream"

Application::Application()
{
	m_Window = Window::CreateWindow({ 640, 400, "Working Window" });
	m_Window->SetUpdateFunction([]() {
		std::cout << "Hello World in loop" << std::endl;
	});
}

Application::~Application()
{
	
}

void Application::Run()
{
	while(m_Window->IsValid())
	{
		m_Window->OnUpdate();
	}
}

