#ifndef _BOX2D_H_
#define _BOX2D_H_

#include "3DMesh\3DMesh.h"

class Box2D : public Mesh3D
{
private:
	float m_width;
	float m_height;
public:
	Box2D(float width, float height);

	void setColor(AlphaColor color);
};

#endif