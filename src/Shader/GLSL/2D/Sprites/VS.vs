#version 440 compatibility

layout (location = 0) in vec4 Position;
layout (location = 1) in vec2 UV;

out vec2 UV_FS; 

void main()
{	
	
	UV_FS = vec2(UV.x, UV.y);
	
	gl_Position = vec4(Position.x, Position.y, 0.0, 1.0);
}