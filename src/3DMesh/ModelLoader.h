#ifndef _MODELLOADER_H_
#define _MODELLOADER_H_

#include <Importer.hpp>
#include <scene.h> 
#include <postprocess.h>
#include "Config.h"
#include "types.h"

class ModelLoader
{
private:
	const aiScene* m_scene;
	PositionData m_positionData;
	NormalData m_normalData;
	IndexData m_indexData;

public:
	int load(std::string fileName);
	PositionData getPositionData();
	NormalData getNormalData();
	IndexData getIndexData();
};

#endif