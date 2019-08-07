#include "stdafx.h"
#include "PhysicModel.h"


btRigidBody* PhysicModel::getRigidBody()
{
	m_qAll = btQuaternion(0, 0, 0, 1);
	m_fAngleAll = 0.0f;
	return m_RigidBody;
}

void PhysicModel::ApplySphereShape(float fRadius, float fMass, glm::quat quatInit, glm::vec3 posInit, bool kinematic)
{
	m_CollisionShape = new btSphereShape(fRadius);
	init(fMass, quatInit,  posInit, m_CollisionShape, kinematic);
}

void PhysicModel::ApplyCapsuleShape(float fRadius, float fHeight, float fMass, glm::quat quatInit, glm::vec3 posInit, bool kinematic)
{

	m_CollisionShape = new btCapsuleShape(fRadius, fHeight);
	init(fMass, quatInit, posInit, m_CollisionShape, kinematic);
}

void PhysicModel::ApplyIndexedMeshShape(int iNumTriangles, int iNumVertices, GLuint* iIndices, glm::vec3* fVertices, bool kinematic)
{
	t_mesh.m_numTriangles = iNumTriangles;
	t_mesh.m_numVertices = iNumVertices;
	t_mesh.m_triangleIndexBase = (unsigned char*)iIndices;
	t_mesh.m_triangleIndexStride = 3 * sizeof(int);
	t_mesh.m_vertexBase = (unsigned char*)fVertices;
	t_mesh.m_vertexStride = 3 * sizeof(float);
	triVert.addIndexedMesh(t_mesh);

	m_CollisionShape = new btBvhTriangleMeshShape(&triVert, true);
	init(0, glm::quat(0, 0, 0, 1), glm::vec3(0, 0, 0), m_CollisionShape, kinematic);
}

void  PhysicModel::init(float fMass, glm::quat quatInit, glm::vec3 posInit, btCollisionShape* collisionShape, bool kinematic)
{
	btQuaternion quat(quatInit.x, quatInit.y, quatInit.z, quatInit.w);
	btVector3 vec(posInit.x, posInit.y, posInit.z);
	m_DefaultMotionState = new btDefaultMotionState(btTransform(quat, vec));
	btVector3 fallInertia(0, 0, 0);
	m_CollisionShape->calculateLocalInertia(fMass, fallInertia);
	m_CI_RigidBody = new btRigidBody::btRigidBodyConstructionInfo(fMass, m_DefaultMotionState, m_CollisionShape, fallInertia);
	m_RigidBody = new btRigidBody(*m_CI_RigidBody);
	m_RigidBody->setActivationState(DISABLE_DEACTIVATION);
	if (kinematic)
	{
		m_RigidBody->setCollisionFlags(m_RigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	}
}

float PhysicModel::gety()
{
	return m_RigidBody->getWorldTransform().getOrigin().getY();
}
