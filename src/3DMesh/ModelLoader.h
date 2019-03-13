#ifndef _MODELLOADER_H_
#define _MODELLOADER_H_

#include <Importer.hpp>
#include <scene.h> 
#include <postprocess.h>
#include "Config.h"
#include "types.h"
#include "Material\Material.h"
#include "3DMesh\3DMesh.h"
#include "Animation\Skeleton.h"
#include "Animation\Animation.h"

class ModelLoader
{
private:
	const aiScene* m_scene;
	PositionData m_positionData;
	NormalData m_normalData;
	IndexData m_indexData;
	UVData m_uvData;
	TangentData m_tangentData;
	BitangentData m_bitangentData;
	VertexWeightData m_vertexWeightData;
	BoneIdData m_boneIdData;
	std::vector<Material> m_material;
	std::string m_fileName;
	std::string m_folderName;
	BoneHierarchy m_skeleton;
	Skeleton m_mainSkeleton;
	std::map<std::string, Animation> m_animations;

public:
	int load(std::string fileName, Mesh3D* mesh);
	int loadSkeleton(aiMesh* mesh);
	int loadAnimations(aiMesh* mesh);
	PositionData getPositionData();
	NormalData getNormalData();
	IndexData getIndexData();
	UVData getUvData();
	TangentData getTangentData();
	BitangentData getBitangentData();
	std::vector<Material> getMaterial();
	BoneHierarchy getSkeleton();
	glm::mat4 AiToGlmMatrix(aiMatrix4x4 aiMat);
};

#endif