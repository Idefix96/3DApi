#version 440

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 UV;

out vec4 NormalTF;
out vec2 UV_FS; 

uniform mat4 gPersp;
uniform mat4 gWorldToCamera;

void main()
{	
	UV_FS = UV;
	NormalTF = 	vec4(Normal.x, Normal.y, Normal.z, 0.0);
	gl_Position = gPersp*gWorldToCamera*vec4(Position.x, Position.y, Position.z, 1.0);
}