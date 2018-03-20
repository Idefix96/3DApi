#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include "BasicBodies\Box\Box.h"

class BoundingBox : public Box
{

public:
	BoundingBox();
	void Draw(GLuint shader);
};

#endif