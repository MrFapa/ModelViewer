#include "Application.h"
#include "LibraryManager.h"

// Might add command line args (not yet tho)
int main()
{
	// Exit directly because nothing works without these libraries
	if(!LibraryManager::InitializeLibraries())
		return -1;

	Application* app = new Application();
	app->Run();
	delete app;

	LibraryManager::TerminateLibraries();

	return 0;
}