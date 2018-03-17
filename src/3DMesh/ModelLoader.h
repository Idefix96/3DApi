#ifndef _MODELLOADER_H_
#define _MODELLOADER_H_

#include <Importer.hpp>
#include <scene.h> 
#include <postprocess.h>
#include "Config.h"
#include "types.h"
#include "Material\Material.h"

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
	std::vector<Material> m_material;
	std::string m_fileName;
	std::string m_folderName;
public:
	int load(std::string fileName);
	PositionData getPositionData();
	NormalData getNormalData();
	IndexData getIndexData();
	UVData getUvData();
	TangentData getTangentData();
	BitangentData getBitangentData();
	std::vector<Material> getMaterial();
};

#endif