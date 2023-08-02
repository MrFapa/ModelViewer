#include "Application.h"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"
#include "OpenGLLogger.h"
#include "Window.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "LibraryManager.h"
#include "MeshRenderer.h"

Application::Application()
{
	m_Window = Window::CreateWindow({ 720, 720, "Working Window" });
}

Application::~Application()
{
	
}

const float positionss[9] = {
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
};

const int indicess[3] = {
	0, 1, 2
};

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

out float oDepth; // Change 'vec1' to 'float'

uniform float rotationAngle; // The rotation angle uniform

void main()
{
    // Create a rotation matrix using the rotation angle around the Z-axis
    mat4 rotationMatrixZ = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, cos(0.7f), -sin(0.7f), 0.0,
        0.0, sin(0.7f), cos(0.7f), 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    mat4 rotationMatrixX = mat4(
        cos(rotationAngle), 0.0, sin(rotationAngle), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(rotationAngle), 0.0, cos(rotationAngle), 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    // Apply the rotation to the vertex position
    vec3 rotatedPosition = (rotationMatrixX * rotationMatrixZ * vec4(aPos, 1.0)).xyz;

    gl_Position = vec4(rotatedPosition, 1.0);
    oDepth = aPos.z; // Change 'aDepth' to 'oDepth'
}
)";
const char* fragmentShaderSource = R"(
#version 330 core

in float oDepth; // Change 'vec1' to 'float'

out vec4 FragColor;

void main()
{
    // Visualize the depth by converting it to a color
    FragColor = vec4(0.3f, 0.1f, oDepth + 0.5f, 1.0f);
}
)";

void Application::Run()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return;
	}

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    Mesh mesh = Mesh();

    if (Loading::LoadOBJ("res/models/hollow_cube.obj", mesh))
    {
        LogInfo("Model was loaded successfully with a total of {} positions ", mesh.GetVertices().size());
    }
    else
    {
        LogWarning("Model could not be loaded successfully");
    }

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<float> positions;
    std::vector<Vertex> vertices = mesh.GetVertices();
    std::vector<unsigned int> indices(vertices.size());

    for(int i = 0; i < vertices.size(); i++)
    {
        indices[i] = i;
        positions.push_back(vertices[i].position.x);
        positions.push_back(vertices[i].position.y);
        positions.push_back(vertices[i].position.z);
    }


    unsigned int VBO, VAO, IBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
    
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    float rotationAngle = 0.0f;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	while (m_Window->IsValid())
	{
		m_Window->Update();

		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rotationAngle += glm::radians(0.2f);
        GLint rotationAngleLoc = glGetUniformLocation(shaderProgram, "rotationAngle");

        // Pass the updated rotation angle value to the shader
        glUniform1f(rotationAngleLoc, rotationAngle);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0));

	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);
}

