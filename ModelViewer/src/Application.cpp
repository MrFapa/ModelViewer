#include "Application.h"

#include "Logger.h"
#include "OBJLoader.h"

Application::Application()
{
	
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
	

}

