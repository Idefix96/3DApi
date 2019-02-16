#ifndef _TYPES_H_
#define _TYPES_H_

#include <vector>
#include "glm\glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include <map>

typedef glm::vec3 Position;
typedef glm::vec2 UVCoordinates;
typedef glm::vec3 Normal;
typedef glm::vec3 Tangent;
typedef glm::vec3 Bitangent;
typedef glm::mat4 TranslationMatrix;
typedef glm::mat4 RotationMatrix;
typedef glm::mat4 ScalingMatrix;
typedef glm::mat4 ProjectionMatrix;
typedef glm::mat4 LookAtMatrix;
typedef glm::vec3 Direction;
typedef glm::quat Rotation;
typedef glm::vec3 Scale;
typedef glm::vec4 AlphaColor;
typedef glm::vec2 Position2D;
typedef glm::vec4 VertexWeights;
typedef glm::vec4 BoneId;

typedef std::vector<Position> PositionData;
typedef std::vector<UVCoordinates> UVData;
typedef std::vector<Normal> NormalData;
typedef std::vector<Tangent> TangentData;
typedef std::vector<Bitangent> BitangentData;
typedef std::vector<int> IndexData;
typedef std::vector<AlphaColor> ColorData;
typedef std::vector<VertexWeights> VertexWeightData;
typedef std::vector<BoneId> BoneIdData;
typedef glm::mat4 SkeletonTransformation[100];

typedef struct {
	Position m_position;
	UVCoordinates m_uv;
	Normal m_normal;
	Tangent m_tangent;
	Bitangent m_bitangent;
	AlphaColor m_color;
	glm::vec4 m_weights;
	glm::vec4 m_boneId;
}Vertex;

typedef struct Bone
{
	std::string					m_name;
	std::string					m_parentName;
	glm::mat4					m_offsetMatrix;
	glm::mat4					m_transformationMatrix;
	Bone*						m_parent;
	glm::mat4					m_animationTransform;
	std::vector<int>			m_vertexIds;
	std::vector<float>			m_vertexWeights;
	glm::mat4					m_overallMatrix;
	int							m_index;
}Bone;

typedef std::map<std::string, Bone> BoneHierarchy;

#endif