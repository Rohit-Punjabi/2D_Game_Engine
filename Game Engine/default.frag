#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit from the main function
uniform sampler2D text;
uniform int renderMode;


void main()
{
	if (renderMode == 0)
		FragColor = texture(text, texCoord);
	
	else if (renderMode == 1)
		FragColor = vec4(color, 1.0f);
}