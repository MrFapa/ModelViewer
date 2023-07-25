#pragma once

class Application
{
public:
	Application();
	~Application();

	void Run();
private:
	class Window* m_Window;
};