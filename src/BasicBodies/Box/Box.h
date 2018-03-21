#ifndef _BOX_H_
#define _BOX_H_

#include "3DMesh\3DMesh.h"

class Box: public Mesh3D
{
private:
	float m_width;
	float m_height;
	float m_depth;

public:
	Box(float width = 1.0f, float height = 1.0f, float depth = 1.0f);
};

#endif