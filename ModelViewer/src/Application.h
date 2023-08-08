#pragma once

class Application
{
public:
	Application();
	~Application();

	void Run();

    static inline int WIDTH = 1000;
    static inline int HEIGHT = 1000;
private:

	struct Window* m_Window;
	class Camera* m_Camera;
};
