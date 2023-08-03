#version 330 core

in float oDepth; 
in vec3 oNormal;
in vec2 oUV;

out vec4 FragColor;

void main()
{
    // Visualize the depth by converting it to a color
    FragColor = vec4(0.3f, 0.1f, oDepth + 0.5f, 1.0f);
	FragColor = vec4(oUV, 0.0f, 1.0f);
	FragColor = vec4(oNormal, 1.0f);
}