#include "3DMesh.h"
#include <iostream>

Mesh3D::Mesh3D()
{

}

Mesh3D::~Mesh3D()
{

}

void Mesh3D::setPositionData(PositionData data)
{
	this->m_positionData = data;
	this->m_vdm.setVertexPositionData(this->m_positionData);
}

void Mesh3D::setMaterial(Material material)
{
	this->m_material = material;
}

void Mesh3D::setNormalData(NormalData data)
{
	this->m_normalData = data;
	this->m_vdm.setVertexNormalData(this->m_normalData);
}

void Mesh3D::setIndexData(IndexData data)
{
	this->m_indexData = data;
	this->m_vdm.setVertexIndexData(this->m_indexData);
}

void Mesh3D::setUVData(UVData data)
{
	this->m_UvData = data;
	this->m_vdm.setVertexUVData(this->m_UvData);
}

void Mesh3D::setTangentData(TangentData data)
{
	this->m_tangentData = data;
	this->m_vdm.setVertexTangentData(this->m_tangentData);
}

void Mesh3D::setBitangentData(BitangentData data)
{
	this->m_bitangentData = data;
	this->m_vdm.setVertexBitangentData(this->m_bitangentData);
}

void Mesh3D::Draw(GLuint shader)
{
	this->m_vdm.bindVAO();
	if (this->m_material.hasTexture())
		glUniform1i(glGetUniformLocation(shader, "hasTexture"), this->m_material.hasTexture());
	if (this->m_material.hasNormalMap())
		glUniform1i(glGetUniformLocation(shader, "hasNormalMap"), this->m_material.hasNormalMap());

	glUniform1f(glGetUniformLocation(shader, "shininess"), this->m_material.getShininess());
	glUniform1f(glGetUniformLocation(shader, "shininessStrength"), this->m_material.getShininessStrength());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->m_material.getTexture().getTexture());
	glUniform1i(glGetUniformLocation(shader, "Texture"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->m_material.getNormalMap().getTexture());
	glUniform1i(glGetUniformLocation(shader, "normalMap"), 1);
	if (this->m_indexData.size() > 0)
		glDrawElements(GL_TRIANGLES, this->m_indexData.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, this->m_positionData.size());
}