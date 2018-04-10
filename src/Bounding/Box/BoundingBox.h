#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include "3DMesh\3DMesh.h"

class BoundingBox : public Mesh3D
{
private:
	float m_width;
	float m_height;
	float m_depth;
public:
	BoundingBox(float width = 1.0f, float height = 1.0f, float depth = 1.0f);
	void Draw(GLuint shader);
};

#endif
