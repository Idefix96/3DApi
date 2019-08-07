#ifndef WORLD_MODEL_H_
#define WORLD_MODEL_H_

#include "3DMesh\3DMesh.h"
#include "Physics\PhysicModel.h"
#include "Bounding\Box\BoundingBox.h";
#include "stdafx.h"

class WorldModel
{
protected:
	std::string			m_strName;
	int					m_iState;
	btQuaternion		m_qAll;
	float				m_fAngleAll;
	enum RenderState {MESH, BOUNDARY, BOTH, NONE};

public:
	PhysicModel*	m_model;
	Mesh3D*			m_mesh;
	BoundingBox		m_boundingBox;

	WorldModel();

	Mesh3D*			getMesh();
	PhysicModel		getModel();
	glm::vec3		getPosition();
	std::string		getName();
	void			MoveForward();
	void			setName(std::string strName);
	void			setRenderState(RenderState renderState);
	void			Update();
};

#endif