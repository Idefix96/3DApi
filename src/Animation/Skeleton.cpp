#include "stdafx.h"
#include "Skeleton.h"

void Skeleton::setHierarchy()
{
	for (std::map<std::string, Bone>::iterator i = this->m_hierarchy.begin(); i != this->m_hierarchy.end(); i++)
	{
		
		if (this->m_hierarchy.find(i->second.m_parentName) != this->m_hierarchy.end())
		{
			i->second.m_parent = &this->m_hierarchy[i->second.m_parentName];
		}
	}
}

void Skeleton::addBone(std::string name, Bone bone)
{
	std::pair<std::string, Bone> pair = { name, bone };
	this->m_hierarchy.insert(pair);
}

void Skeleton::update()
{	
	for (BoneHierarchy::iterator it = m_hierarchy.begin(); it != m_hierarchy.end(); ++it)
	{
		it->second.m_overallMatrix = it->second.m_transformationMatrix*it->second.m_offsetMatrix;
		Bone* parent = it->second.m_parent;

		while (parent != NULL)
		{
			it->second.m_overallMatrix = m_hierarchy[parent->m_name].m_transformationMatrix*it->second.m_overallMatrix;
			parent = parent->m_parent;
		}
		
		this->m_skeletonTransformation[it->second.m_index] = it->second.m_overallMatrix;
	}
}

void Skeleton::rotateBoneLocal(std::string boneName, glm::vec3 axis, float angle)
{
	this->m_hierarchy[std::string(boneName)].m_transformationMatrix = glm::rotate(this->m_hierarchy[boneName].m_transformationMatrix, angle, axis);
	this->update();
}

void Skeleton::rotateBoneGlobal(std::string boneName, glm::vec3 axis, float angle)
{
	glm::mat4 axisTransformation = this->m_hierarchy[std::string(boneName)].m_transformationMatrix;
	Bone* parent = this->m_hierarchy[std::string(boneName)].m_parent;
	while (parent != NULL)
	{
		axisTransformation = m_hierarchy[parent->m_name].m_transformationMatrix*axisTransformation;
		parent = parent->m_parent;
	}
	axisTransformation = glm::inverse(axisTransformation);
	glm::vec4 axis4d = axisTransformation * glm::vec4(axis.x, axis.y, axis.z, 0.0f);
	this->m_hierarchy[std::string(boneName)].m_transformationMatrix = glm::rotate(this->m_hierarchy[boneName].m_transformationMatrix, angle, glm::vec3(axis4d.x, axis4d.y, axis4d.z));
	this->update();
}
