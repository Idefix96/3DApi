#version 440 compatibility

in vec2 UV_FS; 

uniform vec4 gColor;
uniform sampler2D Texture;
out vec4 FragColor;

void main()
{	
	FragColor = vec4(1, 1, 1, texture2D(Texture, UV_FS).r) * gColor;
}