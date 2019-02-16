#ifndef _3DMESH_H_
#define _3DMESH_H_

#include "types.h"
#include "GraphicsData\VertexDataManager.h"
#include "Config.h"
#include "Material\Material.h"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/transform.hpp"
#include "Shader\Shader.h"
#include "Animation\Skeleton.h"

class Mesh3D
{
protected:
	VertexDataManager		m_vdm;
	PositionData			m_positionData;
	NormalData				m_normalData;
	IndexData				m_indexData;
	UVData					m_UvData;
	TangentData				m_tangentData;
	BitangentData			m_bitangentData;
	Material				m_material;
	ColorData				m_colorData;
	VertexWeightData		m_vertexWeightData;
	BoneIdData				m_boneIdData;
	Position				m_currentPosition;
	Rotation				m_currentRotation;
	RotationMatrix			m_rotationMatrix;
	TranslationMatrix		m_translationMatrix;
	ScalingMatrix			m_scalingMatrix;

	Shader*					m_shader;
	bool					m_hasColor;

	BoneHierarchy			m_skeleton;
	SkeletonTransformation	m_skeletonTransformation;

	Skeleton				m_MainSkeleton;
	
public:
	Mesh3D();
	~Mesh3D();

	void setPositionData(PositionData data);
	void setNormalData(NormalData data);
	void setIndexData(IndexData data);
	void setUVData(UVData data);
	void setTangentData(TangentData data);
	void setBitangentData(BitangentData data);
	void setColorData(ColorData data);
	void setVertexWeightData(VertexWeightData data);
	void setBoneIdData(BoneIdData data);
	void setMaterial(Material material);
	void Draw(GLuint shader);
	void rotate(Direction angle);
	void translate(Position position);
	void scale(Scale scale);
	bool hasColor();
	void setShader(Shader* shader);
	void setSkeleton(BoneHierarchy skeleton);
	void setSkeleton(Skeleton skeleton);
	void update();
	
	Shader* getShader();
};

#endif
