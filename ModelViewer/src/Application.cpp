#include "Application.h"

#include "Window.h"
#include "iostream"

Application::Application()
{
	m_Window = Window::CreateWindow({ 1280, 720, "Working Window" });
}

Application::~Application()
{
	
}

void Application::Run()
{
	while(m_Window->IsValid())
	{
		m_Window->Update();
	}
}

