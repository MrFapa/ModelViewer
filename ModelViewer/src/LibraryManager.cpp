#include "LibraryManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

bool LibraryManager::InitializeLibraries()
{
	if (!InitializeGLFW())
		return false;

	if (!InitializeGLEW())
		return false;

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
		std::cout << "GLFW Initialization failed! " << std::endl;
		glfwInitialized = false;
		return false;
	}
	glfwInitialized = true;
	return true;
}

bool LibraryManager::InitializeGLEW()
{
	// Check if already initialized
	if (glewInitialized)
		return true;

	// Important so that the tempWindow doesnt pop up
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	// Create temporary context for the glew initialization
	GLFWwindow* tempWindow = glfwCreateWindow(1, 1, "", nullptr, nullptr);
	if (!tempWindow)
	{
		std::cout << "GLEW Initialization failed: Couldn't create temporary window for initialization" << std::endl;
		return false;
	}
	// Resets this for the next CreateWindow call
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

	glfwMakeContextCurrent(tempWindow);

	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		glfwDestroyWindow(tempWindow);
		// logging library later on
		std::cout << "GLEW Initialization failed: " << glewGetErrorString(err) << std::endl;
		glewInitialized = false;
		return false;
	}

	// Clean up temporary Window
	glfwMakeContextCurrent(nullptr);
	glfwDestroyWindow(tempWindow);

	glewInitialized = true;
	return true;
}



