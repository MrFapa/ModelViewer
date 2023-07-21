#include "Application.h"

// Might add command line args (not yet tho)
int main()
{
	Application* app = new Application();
	app->Run();
	delete app;

	return 0;
}