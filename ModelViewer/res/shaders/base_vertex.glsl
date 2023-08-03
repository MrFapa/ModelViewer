#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out float oDepth;
out vec3 oNormal;
out vec2 oUV;

uniform float rotationAngle;

void main()
{
    mat4 rotationMatrixZ = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, cos(0.5f), -sin(0.5f), 0.0,
        0.0, sin(0.5f), cos(0.5f), 0.0,
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
    oDepth = aPos.z; 
	oNormal = aNormal;
	oUV = aUV;
}