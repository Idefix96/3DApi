#include "stdafx.h"
#include "WorldModel.h"

WorldModel::WorldModel()
{
	m_model = new PhysicModel();
	m_mesh = new Mesh3D();

	m_qAll = btQuaternion(0, 0, 0, 1);
	m_fAngleAll = 0.0f;
	m_renderState = MESH;
}


void WorldModel::Update()
{
	
	btTransform trans;
	m_model->getRigidBody()->getMotionState()->getWorldTransform(trans);
	/*
	glm::vec3 vMiddleOfMesh = m_mesh->getBoundingCenter();
	*/
	//Synchronize physical model and mesh
	if (m_model->getRigidBody()->getInvMass() > 0)
	{
		m_mesh->translate(glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
		m_mesh->rotate(glm::quat(m_qAll.getW(), m_qAll.getX(), m_qAll.getY(), m_qAll.getZ()));
	}
}

Mesh3D* WorldModel::getMesh()
{
	return  m_mesh;
}

PhysicModel WorldModel::getModel()
{
	return *m_model;
}

void WorldModel::MoveForward()
{
	m_model->getRigidBody()->forceActivationState(DISABLE_DEACTIVATION);
	m_model->getRigidBody()->applyForce(btVector3(0, 0, -10), btVector3(0, 0, 0));
	//m_model->getRigidBody()->translate(btVector3(0,0,10));
	btTransform trans;
	m_model->getRigidBody()->getMotionState()->getWorldTransform(trans);

}

void WorldModel::setName(std::string strName)
{
	m_strName = strName;
}

std::string WorldModel::getName()
{
	return m_strName;
}

glm::vec3 WorldModel::getPosition()
{
	btTransform trans;
	m_model->getRigidBody()->getMotionState()->getWorldTransform(trans);
	return glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
}

void WorldModel::setRenderState(RenderState renderState)
{
	switch (renderState)
	{
	case WorldModel::MESH:
		m_mesh->setMode(GL_TRIANGLES);
		break;
	case WorldModel::BOUNDARY:
		m_mesh->setMode(GL_LINES);
		break;
	case WorldModel::BOTH:
		break;
	case WorldModel::NONE:
		break;
	default:
		break;
	}
}