#include "Material.h"

void Material::loadTexture(std::string file)
{
	this->m_Texture.loadTexture(file);
}

void Material::loadNormalMap(std::string file)
{
	this->m_normalMap.loadTexture(file);
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

Texture Material::getTexture()
{
	return this->m_Texture;
}

Texture Material::getNormalMap()
{
	return this->m_normalMap;
}

void Material::setHasTexture(bool hasTexture)
{
	this->m_hasTexture = hasTexture;
}

bool Material::hasTexture()
{
	return this->m_hasTexture;
}

void Material::setHasNormalMap(bool hasNormalMap)
{
	this->m_hasNormalMap = hasNormalMap;
}

bool Material::hasNormalMap()
{
	return this->m_hasNormalMap;
}