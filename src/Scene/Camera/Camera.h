#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "types.h"
#include "glm\gtc\matrix_transform.hpp"

class Camera
{
private:
	float				m_fovy;
	float				m_aspect;
	float				m_zNear;
	float				m_zFar;
	Position			m_position;
	Position			m_center;
	Direction			m_lookDir;
	Direction			m_up;
	Direction			m_xAxis;
	ProjectionMatrix	m_perspectiveMatrix;
	LookAtMatrix		m_worldToCamera;

public:
	Camera();
	~Camera();

	void setFovy(float fovy);
	void setAspect(float aspect);
	void setZNear(float zNear);
	void setZFar(float zFar);
	void setPerspectiveMatrix();
	void setPerspectiveMatrix(float fovy, float aspect, float zNear, float zFar);
	ProjectionMatrix getPerspectiveMatrix();
	LookAtMatrix getWorldToCameraMatrix();
	Position getPosition();
	void move(Direction direction);
};

#endif