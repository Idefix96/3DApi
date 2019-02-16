#pragma once
#include "types.h"

class Skeleton
{
private:
	BoneHierarchy	m_hierarchy;
public:
	SkeletonTransformation	m_skeletonTransformation;
	void setHierarchy();
	void addBone(std::string name, Bone bone);
	void update();
	void rotateBoneGlobal(std::string boneName, glm::vec3 axis, float angle);
	void rotateBoneLocal(std::string boneName, glm::vec3 axis, float angle);
};