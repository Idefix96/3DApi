#ifndef _TYPES_H_
#define _TYPES_H_

#include "glm\glm.hpp"

typedef glm::vec3 Position;
typedef glm::vec2 UVCoordinates;
typedef glm::vec3 Normal;
typedef glm::vec3 Tangent;
typedef glm::vec3 Bitangent;
typedef glm::mat4 TranslationMatrix;
typedef glm::mat4 RotationMatrix;
typedef glm::mat4 ScalingMatrix;

typedef struct {
	Position m_position;
	UVCoordinates m_uv;
	Normal m_normal;
	Tangent m_tangent;
	Bitangent m_bitangent;
}Vertex;



#endif