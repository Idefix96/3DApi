#version 440

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

out vec4 NormalTF;

uniform mat4 gPersp;
uniform mat4 gWorldToCamera;

void main()
{	
	NormalTF = 	gWorldToCamera*vec4(Normal.x, Normal.y, Normal.z, 0.0);
	gl_Position = gPersp*gWorldToCamera*vec4(Position.x, Position.y, Position.z, 1.0);
}