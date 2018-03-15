#ifndef _DIRECTIONALLIGHT_H_
#define _DIRECTIONALLIGHT_H_


#include "types.h"
#include "glm\glm.hpp"

class DirectionalLight
{
private:
	float m_intensity;
	glm::vec4 m_color;
	Direction m_direction;
public:
	float getIntensity();
	void setIntensity(float intensity);
	glm::vec4 getColor();
	void setColor(glm::vec4 color);
	Direction getDirection();
	void setDirection(Direction direction);
};

#endif