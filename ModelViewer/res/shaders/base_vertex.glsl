#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out float oDepth;
out vec3 oNormal;
out vec2 oUV;

uniform float scale;
uniform mat4 MVP;
void main()
{
    gl_Position = MVP * vec4(aPos * scale, 1.0);
    oDepth = aPos.z; 
	oNormal = aNormal;
	oUV = aUV;
}