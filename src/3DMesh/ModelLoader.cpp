#include "ModelLoader.h"

int ModelLoader::load(std::string fileName)
{
	const aiMesh* paiMesh;
	Assimp::Importer importer;

	this->m_fileName = MODEL_PATH + fileName;
	this->m_folderName = fileName.substr(0, fileName.find_last_of("/")+1);
	this->m_scene = importer.ReadFile(this->m_fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace| aiProcess_FlipUVs);
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
			if (this->m_scene->mMeshes[i]->HasTangentsAndBitangents())
			{			
				this->m_tangentData.push_back(Tangent(this->m_scene->mMeshes[i]->mTangents[j].x, this->m_scene->mMeshes[i]->mTangents[j].y, this->m_scene->mMeshes[i]->mTangents[j].z ));
				this->m_bitangentData.push_back(Bitangent(this->m_scene->mMeshes[i]->mBitangents[j].x, this->m_scene->mMeshes[i]->mBitangents[j].y, this->m_scene->mMeshes[i]->mBitangents[j].z));
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
			Material material;
			aiString Path;

			float shininess;
			float shininessStrength;
			this->m_scene->mMaterials[j]->Get(AI_MATKEY_SHININESS, shininess);
			this->m_scene->mMaterials[j]->Get(AI_MATKEY_SHININESS_STRENGTH, shininessStrength);
			material.setShininess(shininess);
			material.setShininessStrength(shininessStrength);

			if (this->m_scene->mMaterials[j]->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{

				std::string textureFile = Path.data;
				material.loadTexture(MODEL_PATH + this->m_folderName + TEXTURE_SUB_PATH + textureFile);
				material.setHasTexture(true);
			}
			else
				material.setHasTexture(false);

			if (this->m_scene->mMaterials[j]->GetTexture(aiTextureType_NORMALS, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string textureFile = Path.data;
				material.loadNormalMap(MODEL_PATH + this->m_folderName + TEXTURE_SUB_PATH + textureFile);
				material.setHasNormalMap(true);
			}
			else
				material.setHasNormalMap(false);

			this->m_material.push_back(material);
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

TangentData ModelLoader::getTangentData()
{
	return this->m_tangentData;
}

BitangentData ModelLoader::getBitangentData()
{
	return this->m_bitangentData;
}

std::vector<Material> ModelLoader::getMaterial()
{
		return this->m_material;
}