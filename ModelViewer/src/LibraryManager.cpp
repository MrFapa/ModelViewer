#include "LibraryManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.h"

bool LibraryManager::InitializeLibraries()
{
	if (!InitializeGLFW())
		return false;

	// Glew need to be initialized in the window class because of the context

	return true;
}

void LibraryManager::TerminateLibraries()
{
	// terminate destroys window and cursor references, might cause problems (order) 
	if(glfwInitialized)
		glfwTerminate();

	// glew doesnt need to be terminated
}

bool LibraryManager::InitializeGLFW()
{
	// Check if already initialized
	if (glfwInitialized)
		return true;

	if(!glfwInit())
	{
		// logging library later on
		LogFatal("GLFW could not be initialized");
		glfwInitialized = false;
		return false;
	}
	glfwInitialized = true;
	return true;
}

bool LibraryManager::InitializeGLEW()
{
	// Check if already initialized
	/*if (glewInitialized)
		return true;*/

	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		glewInitialized = false;
		return false;
	}

	return true;
}



