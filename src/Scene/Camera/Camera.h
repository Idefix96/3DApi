#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "types.h"
#include "glm\gtc\matrix_transform.hpp"
#include "SFML\Window.hpp"
#include "Config.h"

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
	Direction			m_forward;
	ProjectionMatrix	m_perspectiveMatrix;
	LookAtMatrix		m_worldToCamera;
	bool				m_isKeyPressedForward;
	bool				m_isKeyPressedBackwards;
	bool				m_isLeftMouseButtonPressed;
	Position2D			m_mousePosition;
	Position2D			m_mousePositionLastFrame;
	Direction			m_currentRotation;
	RotationMatrix		m_rotationMatrix;

public:
	Camera();
	~Camera();

	void setFovy(float fovy);
	void setAspect(float aspect);
	void setZNear(float zNear);
	void setZFar(float zFar);
	void setPerspectiveMatrix();
	void setPerspectiveMatrix(float fovy, float aspect, float zNear, float zFar);
	void rotate(Direction rotation);
	ProjectionMatrix getPerspectiveMatrix();
	LookAtMatrix getWorldToCameraMatrix();
	Position getPosition();
	void move(Direction direction);
	void move(float delta);

	void controller(sf::Keyboard::Key key, bool pressed);
	void controller(sf::Mouse::Button button, bool pressed);
	void setControlForwardPressed(bool pressed);
	void setControlBackwardPressed(bool pressed);
	void setLeftMouseButtonPressed(bool pressed);
	void doAction();
};

#endif