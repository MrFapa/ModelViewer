#include "Application.h"

#include "glm/gtc/matrix_transform.hpp"
#include "OpenGLLogger.h"
#include "Window.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "MeshRenderer.h"
#include "Shader.h"
#include "Camera.h"

// Temp
const int WIDTH = 1080, HEIGHT = 720;

Application::Application()
{
	m_Window = Window::CreateWindow({ WIDTH, HEIGHT, "Working Window" });
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
	Camera camera = Camera();
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	camera.setPosition({ 1.0f, 2.0f, -2.0f });
	glm::mat4 view = camera.GetViewMatrix();

    Mesh mesh = Mesh();
    (Loading::LoadOBJ("res/models/hollow_cube.obj", mesh) ? 
		LogInfo("Model was loaded successfully with a total of {} positions ", mesh.GetVertices().size()) 
		: LogWarning("Model could not be loaded successfully"));
    
    mesh.GetMeshRenderer().Init(mesh.GetVertices());

    shader.Bind();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	while (m_Window->IsValid())
	{
		m_Window->Update();

		glClearColor(0.02f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.SetUniform1f("scale", 1.0f);
		shader.SetUniformMat4("MVP", proj * view  );
        mesh.GetMeshRenderer().Bind();
        mesh.GetMeshRenderer().Draw();

	}
}

