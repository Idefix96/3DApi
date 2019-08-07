#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "Config.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicModel.h"

class Physics
{
private:
	btBroadphaseInterface*						m_broadphase;
	btSequentialImpulseConstraintSolver*		m_solver;
	btDefaultCollisionConfiguration*			m_collisionConfiguration;
	btCollisionDispatcher*						m_dispatcher;
	btCollisionWorld::ClosestRayResultCallback*	m_RayCallback;
	btDiscreteDynamicsWorld*					m_dynamicsWorld;
	std::vector<PhysicModel*>					m_models;
public:
	Physics();
	~Physics();

	void update();
	void addPhysicModel(PhysicModel* NewModel);
};

#endif 