#include "Material.h"

void Material::loadDiffuseTexture(std::string file)
{
	this->m_diffuseTexture.loadTexture(file);
}

void Material::setDiffuseAlphaColor(AlphaColor alphaColor)
{
	this->m_diffuseAlphaColor = alphaColor;
}
void Material::setSpecularFactor(float specularFactor)
{
	this->m_specularFactor = specularFactor;
}

void Material::setOpacity(float opacity)
{
	this->m_opacity = opacity;
}

AlphaColor Material::getDiffuseAlphaColor()
{
	return this->m_diffuseAlphaColor;
}

float Material::getSpecularFactor()
{
	return this->m_specularFactor;
}

float Material::getOpacity()
{
	return this->m_opacity;
}

DiffuseTexture Material::getTexture()
{
	return this->m_diffuseTexture;
}