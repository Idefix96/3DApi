#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "types.h"
#include "GL/glew.h"
#include "Texture\DiffuseTexture.h"

class Material
{
private:
	AlphaColor m_diffuseAlphaColor;
	DiffuseTexture m_diffuseTexture;
	float m_specularFactor;
	float	m_opacity;
public:
	void setDiffuseAlphaColor(AlphaColor alphaColor);
	void loadDiffuseTexture(std::string file);
	void setSpecularFactor(float specularFactor);
	void setOpacity(float opacity);
	AlphaColor getDiffuseAlphaColor();
	float getSpecularFactor();
	float getOpacity();
	DiffuseTexture getTexture();
};

#endif