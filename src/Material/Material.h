#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "types.h"
#include "GL/glew.h"
#include "Texture\Texture.h"

class Material
{
private:
	AlphaColor m_diffuseAlphaColor;
	Texture m_Texture;
	Texture m_normalMap;
	float m_shininess;
	float m_shininessStrength;
	float	m_opacity;
	bool m_hasTexture;
	bool m_hasNormalMap;
public:
	Material();
	void setDiffuseAlphaColor(AlphaColor alphaColor);
	void loadTexture(std::string file);
	void loadNormalMap(std::string file);
	void setShininess(float shininess);
	void setShininessStrength(float shininessStrength);
	void setOpacity(float opacity);
	AlphaColor getDiffuseAlphaColor();
	float getShininess();
	float getShininessStrength();
	float getOpacity();
	Texture getTexture();
	Texture getNormalMap();
	void setHasTexture(bool hasTexture);
	bool hasTexture();
	void setHasNormalMap(bool hasNormalMap);
	bool hasNormalMap();
};

#endif