#include "Application.h"

#include "LibraryManager.h"
#include "OpenGLLogger.h"
#include "Window.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "MeshRenderer.h"
#include "Shader.h"
#include "Camera.h"
#include "Input.h"
#include "KeyCodes.h"


Application::Application()
{
	m_Window = Window::CreateWindow({ WIDTH, HEIGHT, "Working Window" });
	m_Camera = new Camera((float)WIDTH / (float)HEIGHT);
	m_Camera->SetPosition({ 0.0f, 0.0f, 20.0f });
	Input::Initialize(m_Window->GetGLFWWindow());
}

Application::~Application()
{
	//delete m_Window;
	delete m_Camera;
}


void Application::Run()
{
	LibraryManager::InitializeGLEW();
    Shader shader = Shader("res/shaders/base_vertex.glsl", "res/shaders/base_fragment.glsl");
	

    Mesh mesh = Mesh();
    (Loading::LoadOBJ("res/models/chest.obj", mesh) ? 
		LogInfo("Model was loaded successfully with a total of {} vertices ", mesh.GetVertices().size()) 
		: LogWarning("Model could not be loaded successfully"));
    
    mesh.GetMeshRenderer().Init(mesh.GetVertices());

    shader.Bind();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	while (m_Window->IsValid())
	{
		m_Window->Update();
		Input::Update();
		glClearColor(0.02f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if(Input::GetMouseButton(KeyCodes::MOUSE_LEFT).Action == GLFW_PRESS)
		{
			glm::vec2 mouseDiff = Input::GetDeltaMousePosition();
			// 100 is just hardcoded, speed will be adjustable with imgui later
			m_Camera->Move(glm::radians(100 * -(mouseDiff.x) / WIDTH), glm::radians(100 * -(mouseDiff.y) / HEIGHT));
		}

		shader.SetUniform1f("scale", 1.0f);
		shader.SetUniformMat4("MVP", m_Camera->GetProjViewMatrix());
        mesh.GetMeshRenderer().Bind();
        mesh.GetMeshRenderer().Draw();
		
		KeyInput key = Input::GetInstance().GetKey(KeyCodes::W);
		if(Input::GetKey(KeyCodes::W).Action == GLFW_PRESS)
		{
			m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3{0, 0, 1});
		}
		if (Input::GetKey(KeyCodes::S).Action == GLFW_PRESS)
		{
			m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3{ 0, 0, -1 });
		}

		
	}
}

