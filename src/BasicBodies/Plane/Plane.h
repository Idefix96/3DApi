#ifndef _PLANE_H_
#define _PLANE_H_

#include "types.h"
#include "3DMesh\3DMesh.h"
#include "glm\glm.hpp"
class Plane : public Mesh3D
{
private:
	Position m_offset;
	Direction m_direction1;
	Direction m_direction2;
	float m_width;
	float m_length;
public:
	Plane(Position offset = Position(0, 0, 0), Direction direction1 = Direction(1, 0, 0), Direction direction2 = Direction(0, 0, 1), float width = 1.0f, float length = 1.0f);

};

#endif