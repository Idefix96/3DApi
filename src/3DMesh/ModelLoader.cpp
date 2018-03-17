#include "ModelLoader.h"

int ModelLoader::load(std::string fileName)
{
	const aiMesh* paiMesh;
	Assimp::Importer importer;

	this->m_fileName = MODEL_PATH + fileName;
	this->m_folderName = fileName.substr(0, fileName.find_last_of("/")+1);
	this->m_scene = importer.ReadFile(this->m_fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
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
			if (this->m_scene->mMeshes[i]->HasTextureCoords(0))
			{
				this->m_uvData.push_back(UVCoordinates(this->m_scene->mMeshes[i]->mTextureCoords[0][j].x, this->m_scene->mMeshes[i]->mTextureCoords[0][j].y));
			}
		}
		for (unsigned int k = 0; k < this->m_scene->mMeshes[i]->mNumFaces; k++)
		{
			this->m_indexData.push_back(this->m_scene->mMeshes[i]->mFaces[k].mIndices[0]);
			this->m_indexData.push_back(this->m_scene->mMeshes[i]->mFaces[k].mIndices[1]);
			this->m_indexData.push_back(this->m_scene->mMeshes[i]->mFaces[k].mIndices[2]);
		}

		for (unsigned int j = 0; j < this->m_scene->mNumMaterials; j++)
		{
			aiString Path;
			if (this->m_scene->mMaterials[j]->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				Material material;
				std::string textureFile = Path.data;
				material.loadDiffuseTexture(MODEL_PATH + this->m_folderName + TEXTURE_SUB_PATH + textureFile);
				this->m_material.push_back(material);
			}
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

UVData ModelLoader::getUvData()
{
	return this->m_uvData;
}

std::vector<Material> ModelLoader::getMaterial()
{
		return this->m_material;
}