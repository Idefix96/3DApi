#version 440 compatibility

layout (location = 0) in vec3 Position;

uniform mat4 gPersp;
uniform mat4 gWorldToCamera;
uniform mat4 gTranslation;
uniform mat4 gRotation;
uniform mat4 gScaling;

void main()
{	
	gl_Position = gPersp*gWorldToCamera*gTranslation*gRotation*gScaling*vec4(Position.x, Position.y, Position.z, 1.0);
}