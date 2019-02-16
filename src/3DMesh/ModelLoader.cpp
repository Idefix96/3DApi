#include "stdafx.h"
#include "ModelLoader.h"

int ModelLoader::load(std::string fileName,  Mesh3D* mesh)
{
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
			if (this->m_scene->mMeshes[i]->HasBones())
			{
				this->m_vertexWeightData.push_back(glm::vec4(0.0f));
				this->m_boneIdData.push_back(glm::vec4(0.0f));
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

			aiColor4D diffuse;
			if (aiGetMaterialColor(this->m_scene->mMaterials[j], AI_MATKEY_COLOR_DIFFUSE, &diffuse) == AI_SUCCESS)
				material.setDiffuseAlphaColor(glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a));

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
		if (m_scene->mMeshes[i]->HasBones())
		{
			this->loadSkeleton(this->m_scene->mMeshes[i]);
		}
	}

	mesh->setPositionData(this->getPositionData());
	mesh->setNormalData(this->getNormalData());
	mesh->setUVData(this->getUvData());
	mesh->setTangentData(this->getTangentData());
	mesh->setBitangentData(this->getBitangentData());
	mesh->setMaterial(this->getMaterial()[0]);
	mesh->setSkeleton(this->m_skeleton);
	mesh->setVertexWeightData(this->m_vertexWeightData);
	mesh->setBoneIdData(this->m_boneIdData);
	mesh->setSkeleton(this->m_mainSkeleton);
	return 1;
}

int ModelLoader::loadSkeleton(aiMesh* mesh)
{


	for (unsigned int j = 0; j < mesh->mNumBones; j++)
	{
		aiNode *bone = this->m_scene->mRootNode->FindNode(mesh->mBones[j]->mName.data);
		Bone newBone;
		
		newBone.m_offsetMatrix = AiToGlmMatrix(mesh->mBones[j]->mOffsetMatrix);
		newBone.m_animationTransform = glm::mat4(1.0f);
		newBone.m_transformationMatrix = AiToGlmMatrix(bone->mTransformation);
		newBone.m_name = mesh->mBones[j]->mName.data;
		aiNode* curNode = this->m_scene->mRootNode->FindNode(aiString(mesh->mBones[j]->mName.data));
		newBone.m_parentName = curNode->mParent->mName.data;
		newBone.m_parent = NULL;
		newBone.m_index = j;

		for (int k = 0; k <= mesh->mBones[j]->mNumWeights - 1; k++)
		{
			int vertexId = mesh->mBones[j]->mWeights[k].mVertexId;
			float vertexWeight = mesh->mBones[j]->mWeights[k].mWeight;
			newBone.m_vertexIds.push_back(vertexId);
			newBone.m_vertexWeights.push_back(vertexWeight);
			if (this->m_vertexWeightData[vertexId].x == 0.0f)
			{
				this->m_vertexWeightData[vertexId].x = vertexWeight;
				this->m_boneIdData[vertexId].x = j;
			}
			else
				if (this->m_vertexWeightData[vertexId].y == 0.0f)
				{
					this->m_vertexWeightData[vertexId].y = vertexWeight;
					this->m_boneIdData[vertexId].y = j;
				}
				else
					if (this->m_vertexWeightData[vertexId].z == 0.0f)
					{
						this->m_vertexWeightData[vertexId].z = vertexWeight;
						this->m_boneIdData[vertexId].z = j;
					}
					else
						if (this->m_vertexWeightData[vertexId].w == 0.0f)
						{
							this->m_vertexWeightData[vertexId].w = vertexWeight;
							this->m_boneIdData[vertexId].w = j;
						}
		}
		std::pair<std::string, Bone> pair = { mesh->mBones[j]->mName.data, newBone };
		this->m_skeleton.insert(pair);
		this->m_mainSkeleton.addBone(mesh->mBones[j]->mName.data, newBone);

	}

	this->m_mainSkeleton.setHierarchy();
	for (std::map<std::string, Bone>::iterator i = this->m_skeleton.begin(); i != this->m_skeleton.end(); i++)
	{
		aiNode* curNode = this->m_scene->mRootNode->FindNode(aiString(i->first));
		if (this->m_skeleton.find(curNode->mParent->mName.data) != this->m_skeleton.end())
		{
			i->second.m_parent = &this->m_skeleton[curNode->mParent->mName.data];
		}
		if (i->second.m_parent == NULL)
		{
			aiNode* skeletonNode = this->m_scene->mRootNode->FindNode(aiString(i->first));
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

BoneHierarchy ModelLoader::getSkeleton()
{
	return this->m_skeleton;
}

glm::mat4 ModelLoader::AiToGlmMatrix(aiMatrix4x4 aiMat)
{
	glm::mat4 ret;

	ret[0][0] = aiMat.a1;
	ret[0][1] = aiMat.b1;
	ret[0][2] = aiMat.c1;
	ret[0][3] = aiMat.d1;
	ret[1][0] = aiMat.a2;
	ret[1][1] = aiMat.b2;
	ret[1][2] = aiMat.c2;
	ret[1][3] = aiMat.d2;
	ret[2][0] = aiMat.a3;
	ret[2][1] = aiMat.b3;
	ret[2][2] = aiMat.c3;
	ret[2][3] = aiMat.d3;
	ret[3][0] = aiMat.a4;
	ret[3][1] = aiMat.b4;
	ret[3][2] = aiMat.c4;
	ret[3][3] = aiMat.d4;

	return ret;
}