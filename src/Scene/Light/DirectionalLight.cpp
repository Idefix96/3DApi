#include "DirectionalLight.h"

float DirectionalLight::getIntensity()
{
	return this->m_intensity;
}

void DirectionalLight::setIntensity(float intensity)
{
	this->m_intensity = intensity;
}

glm::vec4 DirectionalLight::getColor()
{
	return this->m_color;
}
void DirectionalLight::setColor(glm::vec4 color)
{
	this->m_color = color;
}

Direction DirectionalLight::getDirection()
{
	return this->m_direction;
}
void DirectionalLight::setDirection(Direction direction)
{
	this->m_direction = direction;
}