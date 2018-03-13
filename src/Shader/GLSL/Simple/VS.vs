#version 440

layout (location = 0) in vec3 Position;

uniform mat4 gPersp;
uniform mat4 gWorldToCamera;

void main()
{	
	gl_Position = gPersp*gWorldToCamera*vec4(Position.x, Position.y, Position.z, 1.0);
}