#pragma once

class LibraryManager
{
public:
	static bool InitializeLibraries();
	static void TerminateLibraries();

	static bool InitializeGLFW();
	static bool InitializeGLEW();

	inline static bool IsGLFWInitialized() { return glfwInitialized; }
	inline static bool IsGLEWInitialized() { return glewInitialized; }
private:
	inline static bool glfwInitialized = false;
	inline static bool glewInitialized = false;
};