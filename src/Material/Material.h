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
	float m_specularFactor;
	float	m_opacity;
	bool m_hasTexture;
	bool m_hasNormalMap;
public:
	void setDiffuseAlphaColor(AlphaColor alphaColor);
	void loadTexture(std::string file);
	void loadNormalMap(std::string file);
	void setSpecularFactor(float specularFactor);
	void setOpacity(float opacity);
	AlphaColor getDiffuseAlphaColor();
	float getSpecularFactor();
	float getOpacity();
	Texture getTexture();
	Texture getNormalMap();
	void setHasTexture(bool hasTexture);
	bool hasTexture();
	void setHasNormalMap(bool hasNormalMap);
	bool hasNormalMap();
};

#endif