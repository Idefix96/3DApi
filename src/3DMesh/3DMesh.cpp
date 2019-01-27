#include "3DMesh.h"
#include <iostream>

Mesh3D::Mesh3D()
{
	m_translationMatrix = TranslationMatrix(1.0f);
	m_rotationMatrix = RotationMatrix(1.0f);
	m_scalingMatrix = ScalingMatrix(1.0f);
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

void Mesh3D::setColorData(ColorData data)
{
	this->m_colorData = data;
	this->m_vdm.setVertexColorData(this->m_colorData);
	this->m_hasColor = true;
}

bool Mesh3D::hasColor()
{
	return this->m_hasColor;
}

void Mesh3D::Draw(GLuint shader)
{	
	glUseProgram(shader);
	this->m_vdm.bindVAO();
	glUniform1i(glGetUniformLocation(shader, "hasColor"), this->hasColor());
	glUniform1i(glGetUniformLocation(shader, "hasTexture"), this->m_material.hasTexture());
	glUniform1i(glGetUniformLocation(shader, "hasNormalMap"), this->m_material.hasNormalMap());
	glUniform1i(glGetUniformLocation(shader, "hasMaterialColor"), this->m_material.hasColor());
	glUniform1f(glGetUniformLocation(shader, "shininess"), this->m_material.getShininess());
	glUniform1f(glGetUniformLocation(shader, "shininessStrength"), this->m_material.getShininessStrength());
	glUniform4fv(glGetUniformLocation(shader, "materialColor"), 1, glm::value_ptr(this->m_material.getDiffuseAlphaColor()));
	glUniformMatrix4fv(glGetUniformLocation(shader, "gScaling"), 1, GL_FALSE, glm::value_ptr(this->m_scalingMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader, "gRotation"), 1, GL_FALSE, glm::value_ptr(this->m_rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader, "gTranslation"), 1, GL_FALSE, glm::value_ptr(this->m_translationMatrix));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->m_material.getTexture().getTexture());
	glUniform1i(glGetUniformLocation(shader, "diffuseTexture"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->m_material.getNormalMap().getTexture());
	glUniform1i(glGetUniformLocation(shader, "normalMap"), 1);
	
	if (this->m_indexData.size() > 0)
		glDrawElements(GL_TRIANGLES, this->m_indexData.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, this->m_positionData.size());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,NULL);
}

void Mesh3D::rotate(Direction angle)
{
	this->m_rotationMatrix = glm::rotate(glm::mat4(1.0f), angle.x, glm::vec3(1, 0, 0));
	this->m_rotationMatrix *= glm::rotate(glm::mat4(1.0f), angle.y, glm::vec3(0, 1, 0));
	this->m_rotationMatrix *= glm::rotate(glm::mat4(1.0f), angle.z, glm::vec3(0, 0, 1));
}


void Mesh3D::translate(Position position)
{
	this->m_translationMatrix = glm::translate(glm::mat4(1.0f), position);
}

void Mesh3D::scale(Scale scale)
{
	this->m_scalingMatrix[0][0] = scale.x;
	this->m_scalingMatrix[1][1] = scale.y;
	this->m_scalingMatrix[2][2] = scale.z;
}