#version 440 compatibility

out vec4 FragColor;

uniform vec4 materialColor;

void main()
{	
	FragColor = materialColor;
}