#include "Application.h"


#include "Window.h"
#include "Logger.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "LibraryManager.h"
#include "MeshRenderer.h"

Application::Application()
{
	m_Window = Window::CreateWindow({ 1280, 720, "Working Window" });
	LibraryManager::InitializeGLEW();
}

Application::~Application()
{
	
}

void Application::Run()
{
    LogInfo("Application starts running");

	Loading::ModelData data = Loading::LoadOBJ("res/models/hollow_cube.obj");
	if(!data.vertexCoord.empty())
	{
		LogInfo("Model '{}' was loaded successfully with a total of {} vertices and {} faces", data.modelName, data.vertexCoord.size() / 3, data.indices.size() / 3);
	} else
	{
		LogWarning("Model '{}' could not be loaded successfully", data.modelName);
	}

	Mesh mesh(data.vertexCoord, data.indices);
  
	while(m_Window->IsValid())
	{
		m_Window->Update();
		
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		mesh.GetMeshRenderer()->Bind();
		mesh.GetMeshRenderer()->Draw();

	}
}

