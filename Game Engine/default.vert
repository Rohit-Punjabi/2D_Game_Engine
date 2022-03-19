#version 330 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;


// Outputs the color for the Fragment Shader
out vec3 color;

// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform float scale;

void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = projectionMatrix * modelMatrix * vec4(aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
}