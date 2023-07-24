#pragma once
#include <GL/glew.h>

#include "Logger.h"


static void ClearErrors()
{
    while (glGetError() != GL_NO_ERROR);
}
// Maybe do an insert
static void CheckErrorGL(const char* filepath, unsigned int line)
{
    while (GLenum error = glGetError() != GL_NO_ERROR)
    {
        LogFatal("OpenGL Error: {}  [{}, {}]", (const char*) glewGetErrorString(error), filepath, line);
    }
}

// Use Macro instead of function
#ifdef MV_DEBUG
#define GLCall(x) ClearErrors();\
	x;\
    CheckErrorGL(__FILE__, __LINE__)
#else
#define GLCall(x)
#endif