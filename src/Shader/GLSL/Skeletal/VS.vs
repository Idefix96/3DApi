#version 440 compatibility

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 UV;
layout (location = 3) in vec3 Tangent;
layout (location = 4) in vec3 Bitangent;
layout (location = 5) in vec4 Color;
layout (location = 6) in vec4 Weights;
layout (location = 7) in vec4 BoneIds;

out vec4 Position_FS;
out vec4 NormalTF;
out vec2 UV_FS; 
out vec4 Tangent_FS;
out vec4 Bitangent_FS;
out vec4 Color_FS;

uniform mat4 gPersp;
uniform mat4 gWorldToCamera;
uniform mat4 gTranslation;
uniform mat4 gRotation;
uniform mat4 gScaling;
uniform float numBones;
uniform mat4 gBoneTransform[50];

void main()
{	
	mat4 BoneTransform = mat4(0.0);
	if (BoneIds.x != 0.0)
	{
		BoneTransform += gBoneTransform[int(BoneIds.x)] * Weights.x;
	}
	if (BoneIds.y != 0.0)
	{
		BoneTransform += gBoneTransform[int(BoneIds.y)] * Weights.y;
	}
	if (BoneIds.z != 0.0)
	{
		BoneTransform += gBoneTransform[int(BoneIds.z)] * Weights.z;
	}
	if (BoneIds.w != 0.0)
	{
		BoneTransform += gBoneTransform[int(BoneIds.w)] * Weights.w;
	}

	Position_FS = gRotation*gScaling*BoneTransform*vec4(Position.x, Position.y, Position.z, 1.0);
	UV_FS = UV;
	Color_FS = Color;
	Tangent_FS = gRotation*gScaling*BoneTransform*vec4(Tangent.x, Tangent.y, Tangent.z, 0.0);
	Bitangent_FS = gRotation*gScaling*BoneTransform*vec4(Bitangent.x, Bitangent.y, Bitangent.z, 0.0);
	NormalTF = 	gRotation*gScaling*BoneTransform*vec4(Normal.x, Normal.y, Normal.z, 0.0);
	gl_Position = gPersp*gWorldToCamera*gTranslation*gRotation*gScaling*BoneTransform*vec4(Position.x, Position.y, Position.z, 1.0);
}