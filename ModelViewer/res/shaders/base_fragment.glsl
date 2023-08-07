#version 330 core

in float oDepth; 
in vec3 oNormal;
in vec2 oUV;

out vec4 FragColor;

void main()
{
    // Visualize the depth by converting it to a color
    FragColor = vec4(oDepth + 0.5f, 0.4f, 0.3f, 1.0f);
	//FragColor = vec4(oUV, 0.0f, 1.0f);
	//FragColor = vec4(oNormal, 1.0f);
}