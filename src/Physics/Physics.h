#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "Config.h"
#include "btBulletDynamicsCommon.h"

class Physics
{
private:
	btBroadphaseInterface*						m_broadphase;
	btSequentialImpulseConstraintSolver*		m_solver;
	btDefaultCollisionConfiguration*			m_collisionConfiguration;
	btCollisionDispatcher*						m_dispatcher;
	btCollisionWorld::ClosestRayResultCallback*	m_RayCallback;
	btDiscreteDynamicsWorld*					m_dynamicsWorld;
public:
	Physics();
	~Physics();

	void update();
};

#endif