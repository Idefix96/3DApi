#include "AmbientLight.h"

float AmbientLight::getIntensity()
{
	return this->m_intensity;
}

void AmbientLight::setIntensity(float intensity)
{
	this->m_intensity = intensity;
}

glm::vec4 AmbientLight::getColor()
{
	return this->m_color;
}
void AmbientLight::setColor(glm::vec4 color)
{
	this->m_color = color;
}