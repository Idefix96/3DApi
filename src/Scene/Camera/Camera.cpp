#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	this->m_fovy = 45;
	this->m_aspect = 1980.0 / 1080.0;
	this->m_zNear = 0.01;
	this->m_zFar = 1000;
	this->m_perspectiveMatrix = glm::perspective(this->m_fovy, this->m_aspect, this->m_zNear, this->m_zFar);
	this->m_position = Position(0, 0, 0);
	this->m_center = Position(0, 0, -1);
	this->m_lookDir = this->m_center - this->m_position;
	this->m_forward = this->m_lookDir;
	this->m_up = Direction(0, 1, 0);
	this->m_worldToCamera = glm::lookAt(this->m_position, this->m_center, this->m_up);
	this->m_xAxis = glm::vec3(1.f, 0.f, 0.f);
	this->m_isKeyPressedForward = false;
	this->m_isKeyPressedBackwards = false;
	this->m_isLeftMouseButtonPressed = false;
	this->m_currentRotation = glm::vec3(0);
	this->m_rotationMatrix = glm::mat4(1.0);
}

Camera::~Camera()
{

}

void Camera::setFovy(float fovy)
{
	this->m_fovy = fovy;
}

void Camera::setAspect(float aspect)
{
	this->m_aspect = aspect;
} 

void Camera::setZNear(float zNear)
{
	this->m_zNear = zNear;
}

void Camera::setZFar(float zFar)
{
	this->m_zFar = zFar;
}

void Camera::setPerspectiveMatrix()
{
	this->m_perspectiveMatrix = glm::perspective(this->m_fovy, this->m_aspect, this->m_zNear, this->m_zFar);
}

void Camera::setPerspectiveMatrix(float fovy, float aspect, float zNear, float zFar)
{
	this->m_perspectiveMatrix = glm::perspective(fovy, aspect, zNear, zFar);
}

ProjectionMatrix  Camera::getPerspectiveMatrix()
{
	return this->m_perspectiveMatrix;
}

LookAtMatrix  Camera::getWorldToCameraMatrix()
{
	return this->m_worldToCamera;
}

Position Camera::getPosition()
{
	return this->m_position;
}

void Camera::move(Direction direction)
{
	this->m_position += direction;
	this->m_center += direction;
	this->m_worldToCamera = glm::lookAt(this->m_position, this->m_center, this->m_up);
}

void Camera::move(float delta)
{
	this->m_position += delta*this->m_forward;
	this->m_center += delta*this->m_forward;
	this->m_forward = glm::normalize(this->m_center - this->m_position);
	this->m_worldToCamera = glm::lookAt(this->m_position, this->m_center, this->m_up);
}

void Camera::rotate(Direction rotation)
{
	this->m_currentRotation += rotation;
	this->m_rotationMatrix = glm::rotate(glm::mat4(1.0), this->m_currentRotation.y, glm::vec3(0.f, 1.f, 0.f));
	glm::vec4 newLookDir = this->m_rotationMatrix*glm::vec4(this->m_lookDir.x, this->m_lookDir.y, this->m_lookDir.z, 0.f);
	glm::vec4 newXAxis = this->m_rotationMatrix*glm::vec4(this->m_xAxis.x, this->m_xAxis.y, this->m_xAxis.z, 0.f);
	this->m_rotationMatrix = glm::rotate(glm::mat4(1.0), this->m_currentRotation.x, glm::vec3(newXAxis.x, newXAxis.y, newXAxis.z));
	 newLookDir = this->m_rotationMatrix*glm::vec4(newLookDir.x, newLookDir.y, newLookDir.z, 0.f);

	this->m_forward = Direction(newLookDir.x, newLookDir.y, newLookDir.z);
	this->m_center = this->m_position + glm::vec3(this->m_forward.x, this->m_forward.y, this->m_forward.z);
	this->m_worldToCamera = glm::lookAt(this->m_position, this->m_center, this->m_up);
}

void Camera::setControlForwardPressed(bool pressed)
{
	this->m_isKeyPressedForward = pressed;
}
void Camera::setControlBackwardPressed(bool pressed)
{
	this->m_isKeyPressedBackwards = pressed;
}

void Camera::setLeftMouseButtonPressed(bool pressed)
{
	this->m_isLeftMouseButtonPressed = pressed;
}

void Camera::controller(sf::Keyboard::Key key, bool pressed)
{	
	if (key == CAMERA_FORWARD_KEY)
	{
		this->m_isKeyPressedForward = pressed;
	}
	if (key == CAMERA_BACKWARD_KEY)
	{
		this->m_isKeyPressedBackwards = pressed;
	}
}

void Camera::controller(sf::Mouse::Button button, bool pressed)
{
	
	if (button == sf::Mouse::Left)
	{
		this->m_isLeftMouseButtonPressed = pressed;
		this->m_mousePosition.x = sf::Mouse::getPosition().x;
		this->m_mousePosition.y = sf::Mouse::getPosition().y;
		this->m_mousePositionLastFrame.x = sf::Mouse::getPosition().x;
		this->m_mousePositionLastFrame.y = sf::Mouse::getPosition().y;
	}
}

void Camera::doAction()
{
	if (this->m_isKeyPressedForward)
		this->move(CAMERA_DEFAULT_SPEED);
	if (this->m_isKeyPressedBackwards)
		this->move(-CAMERA_DEFAULT_SPEED);

	if (this->m_isLeftMouseButtonPressed)
	{
		this->m_mousePosition.x = sf::Mouse::getPosition().x;	
		this->m_mousePosition.y = sf::Mouse::getPosition().y;
	
		glm::vec3 rotation = glm::vec3((this->m_mousePosition.y - this->m_mousePositionLastFrame.y)/100.f, ( this->m_mousePositionLastFrame.x - this->m_mousePosition.x )/100.f, 0.f);
		this->rotate(rotation);

		this->m_mousePositionLastFrame.x = this->m_mousePosition.x;
		this->m_mousePositionLastFrame.y = this->m_mousePosition.y;
	}
}
