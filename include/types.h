#ifndef _TYPES_H_
#define _TYPES_H_

#include <vector>
#include "glm\glm.hpp"
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

typedef std::vector<Position> PositionData;
typedef std::vector<UVCoordinates> UVData;
typedef std::vector<Normal> NormalData;
typedef std::vector<Tangent> TangentData;
typedef std::vector<Bitangent> BitangentData;
typedef std::vector<int> IndexData;

typedef glm::vec4 AlphaColor;

typedef struct {
	Position m_position;
	UVCoordinates m_uv;
	Normal m_normal;
	Tangent m_tangent;
	Bitangent m_bitangent;
}Vertex;

typedef struct Bone
{
	unsigned int			m_index;
	std::string				m_name;
	glm::mat4				m_offsetMatrix;
	glm::mat4				m_transformationMatrix;
	Bone*					m_parent;
	glm::mat4				m_animationTransform;
}Bone;

typedef std::map<std::string, Bone> Skeleton;

#endif