#ifndef PHYSICMODEL_H_
#define PHYSICMODEL_H_

#include "btBulletDynamicsCommon.h"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/transform.hpp"
#include "types.h"
#include "3DMesh\3DMesh.h"

class PhysicModel
{
private:
	btCollisionShape*							m_CollisionShape;
	btDefaultMotionState*						m_DefaultMotionState;
	btRigidBody::btRigidBodyConstructionInfo*  m_CI_RigidBody;
	btRigidBody*								m_RigidBody;
	btTransform								m_trans;
	btTriangleIndexVertexArray triVert;
	btIndexedMesh t_mesh;
	btCollisionWorld::ClosestRayResultCallback*	m_RayCallback;
	btCollisionWorld::ClosestRayResultCallback*	m_RayCallbackDirection1;
	btCollisionWorld::ClosestRayResultCallback*	m_RayCallbackDirection2;
	btCollisionWorld::ClosestRayResultCallback*	m_RayCallbackDirection3;
	btQuaternion		m_qAll;
	float				m_fAngleAll;
	void init(float fMass, glm::quat quatInit, glm::vec3 posInit, btCollisionShape* collisionShape, bool kinematic);
public:

	btRigidBody* getRigidBody();
	void ApplySphereShape(float fRadius, float fMass, glm::quat quatInit, glm::vec3 posInit, bool kinematic = true);
	void ApplyCapsuleShape(float fRadius, float fHeight, float fMass, glm::quat quatInit, glm::vec3 posInit, bool kinematic = true);
	void ApplyIndexedMeshShape(int iNumTriangles, int iNumVertices, GLuint* iIndices, glm::vec3* fVertices, bool kinematic = false);
	float gety();
};

#endif