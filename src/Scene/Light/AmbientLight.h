#ifndef _AMBIENTLIGHT_H_
#define _AMBIENTLIGHT_H_

#include "types.h"
#include "glm\glm.hpp"

class AmbientLight
{
private:
	float m_intensity;
	glm::vec4  m_color;
public:
	float getIntensity();
	void setIntensity(float intensity);
	glm::vec4 getColor();
	void setColor(glm::vec4 color);
};

#endif
