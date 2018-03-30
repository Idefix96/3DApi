#include "Material.h"

Material::Material()
{
	this->m_hasNormalMap = false;
	this->m_hasTexture = false;
}

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
	this->m_hasColor = true;
}
void Material::setShininess(float shininess)
{
	this->m_shininess = shininess;
}

void Material::setShininessStrength(float shininessStrength)
{
	this->m_shininessStrength = shininessStrength;
}

void Material::setOpacity(float opacity)
{
	this->m_opacity = opacity;
}

AlphaColor Material::getDiffuseAlphaColor()
{
	return this->m_diffuseAlphaColor;
}

float Material::getShininess()
{
	return this->m_shininess;
}

float Material::getShininessStrength()
{
	return this->m_shininessStrength;
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

bool Material::hasColor()
{
	return this->m_hasColor;
}