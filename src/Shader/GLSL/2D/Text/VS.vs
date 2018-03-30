#version 440 compatibility

layout (location = 0) in vec4 Position;

out vec2 UV_FS; 

void main()
{	
	
	UV_FS = vec2(Position.z, Position.w);
	
	gl_Position = vec4(Position.x, Position.y, 0.0, 1.0);
}