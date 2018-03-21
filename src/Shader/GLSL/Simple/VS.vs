#version 440

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 UV;
layout (location = 3) in vec3 Tangent;
layout (location = 4) in vec3 Bitangent;

out vec4 Position_FS;
out vec4 NormalTF;
out vec2 UV_FS; 
out vec4 Tangent_FS;
out vec4 Bitangent_FS;

uniform mat4 gPersp;
uniform mat4 gWorldToCamera;
uniform mat4 gTranslation;
uniform mat4 gRotation;
uniform mat4 gScaling;

void main()
{	
	Position_FS = gWorldToCamera*vec4(Position.x, Position.y, Position.z, 1.0);
	UV_FS = UV;
	Tangent_FS = gWorldToCamera*vec4(Tangent.x, Tangent.y, Tangent.z, 0.0);
	Bitangent_FS = gWorldToCamera*vec4(Bitangent.x, Bitangent.y, Bitangent.z, 0.0);
	NormalTF = 	gWorldToCamera*vec4(Normal.x, Normal.y, Normal.z, 0.0);
	gl_Position = gPersp*gWorldToCamera*gScaling*gRotation*gTranslation*vec4(Position.x, Position.y, Position.z, 1.0);
}