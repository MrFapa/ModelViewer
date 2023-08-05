#include "Application.h"

#include "glm/gtc/matrix_transform.hpp"

#include "OpenGLLogger.h"
#include "Window.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "MeshRenderer.h"
#include "Shader.h"
#include "Camera.h"

Application::Application()
{
	m_Window = Window::CreateWindow({ WIDTH, HEIGHT, "Working Window" });
	m_Camera = new Camera();
}

Application::~Application()
{

}


void Application::Run()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return;
	}

    Shader shader = Shader("res/shaders/base_vertex.glsl", "res/shaders/base_fragment.glsl");
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	m_Camera->SetPosition({ 0.0f, 0.0f, 10.0f });

    Mesh mesh = Mesh();
    (Loading::LoadOBJ("res/models/chest.obj", mesh) ? 
		LogInfo("Model was loaded successfully with a total of {} positions ", mesh.GetVertices().size()) 
		: LogWarning("Model could not be loaded successfully"));
    
    mesh.GetMeshRenderer().Init(mesh.GetVertices());

    shader.Bind();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	double lastXpos = 0, lastYpos = 0;

	while (m_Window->IsValid())
	{
		m_Window->Update();
		glClearColor(0.02f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double xpos, ypos;
		glfwGetCursorPos(m_Window->GetGLFWWindow(), &xpos, &ypos);
		if(glfwGetMouseButton(m_Window->GetGLFWWindow(), GLFW_MOUSE_BUTTON_LEFT))
		{
			// 100 is just hardcoded, speed will be adjustable with imgui later
			m_Camera->Move((float) glm::radians(100 * (xpos - lastXpos) / WIDTH), (float) glm::radians(100 * (ypos - lastYpos) / HEIGHT));
		}
		glm::mat4 view = m_Camera->GetViewMatrix();

		shader.SetUniform1f("scale", 1.0f);
		shader.SetUniformMat4("MVP", proj * view  );
        mesh.GetMeshRenderer().Bind();
        mesh.GetMeshRenderer().Draw();

		lastXpos = xpos;
		lastYpos = ypos;


	}
}

