#include "ModelLoader.h"
#include <iostream>

int ModelLoader::load(std::string fileName)
{
	const aiMesh* paiMesh;
	Assimp::Importer importer;

	fileName = MODEL_PATH + fileName;
	std::cout << fileName << std::endl;
	this->m_scene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	if (!this->m_scene)
	{
		return 0;
	}

	for (unsigned int i = 0; i < this->m_scene->mNumMeshes; i++)
	{
		for (unsigned int j = 0; j < this->m_scene->mMeshes[i]->mNumVertices; j++)
		{
			this->m_positionData.push_back(Position(this->m_scene->mMeshes[i]->mVertices[j].x, this->m_scene->mMeshes[i]->mVertices[j].y, this->m_scene->mMeshes[i]->mVertices[j].z));

			if (this->m_scene->mMeshes[i]->HasNormals())
			{
				this->m_normalData.push_back(Normal(this->m_scene->mMeshes[i]->mNormals[j].x, this->m_scene->mMeshes[i]->mNormals[j].y, this->m_scene->mMeshes[i]->mNormals[j].z));
			}
		}
		for (unsigned int k = 0; k < this->m_scene->mMeshes[i]->mNumFaces; k++)
		{
			this->m_indexData.push_back(this->m_scene->mMeshes[i]->mFaces[k].mIndices[0]);
			this->m_indexData.push_back(this->m_scene->mMeshes[i]->mFaces[k].mIndices[1]);
			this->m_indexData.push_back(this->m_scene->mMeshes[i]->mFaces[k].mIndices[2]);
		}
	}
	return 1;
}

PositionData ModelLoader::getPositionData()
{
	return this->m_positionData;
}

NormalData ModelLoader::getNormalData()
{
	return this->m_normalData;
}

IndexData ModelLoader::getIndexData()
{
	return this->m_indexData;
}