#include "Application.h"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"
#include "OpenGLLogger.h"
#include "Window.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "MeshRenderer.h"
#include "Shader.h"

Application::Application()
{
	m_Window = Window::CreateWindow({ 720, 720, "Working Window" });
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

    Mesh mesh = Mesh();
    (Loading::LoadOBJ("res/models/hollow_cube.obj", mesh) ? 
		LogInfo("Model was loaded successfully with a total of {} positions ", mesh.GetVertices().size()) 
		: LogWarning("Model could not be loaded successfully"));
    
    mesh.GetMeshRenderer().Init(mesh.GetVertices());

    shader.Bind();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    float rotationAngle = 0.0f;
	while (m_Window->IsValid())
	{
		m_Window->Update();

		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rotationAngle += glm::radians(0.2f);
        shader.SetUniform1f("rotationAngle", rotationAngle);

        mesh.GetMeshRenderer().Bind();
        mesh.GetMeshRenderer().Draw();

	}
}

