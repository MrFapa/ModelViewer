#include "Application.h"


#include "Window.h"
#include "Logger.h"
#include "OBJLoader.h"

Application::Application()
{
	m_Window = Window::CreateWindow({ 1280, 720, "Working Window" });
}

Application::~Application()
{
	
}

void Application::Run()
{
  //LogInfo("Application starts running");
	Loading::ModelData data = Loading::LoadOBJ("res/models/plate.obj");
	if(!data.vertexCoord.empty())
	{
		LogInfo("Model '{}' was loaded successfully with a total of {} vertices", data.modelName, data.vertexCoord.size());
	} else
	{
		LogWarning("Model '{}' could not be loaded successfully", data.modelName);
	}
  
	while(m_Window->IsValid())
	{
		m_Window->Update();
	}
}

