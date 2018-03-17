#include "Camera.h"

Camera::Camera()
{
	this->m_fovy = 45;
	this->m_aspect = 1980.0 / 1080.0;
	this->m_zNear = 0.01;
	this->m_zFar = 1000;
	this->m_perspectiveMatrix = glm::perspective(this->m_fovy, this->m_aspect, this->m_zNear, this->m_zFar);
	this->m_position = Position(3, 0, 0);
	this->m_center = Position(0, 0, 0);
	this->m_lookDir = this->m_center - this->m_position;
	this->m_up = Direction(0, 1, 0);
	this->m_worldToCamera = glm::lookAt(this->m_position, this->m_center, this->m_up);
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

void Camera::move(Direction direction)
{
	this->m_position += direction;
	this->m_center += direction;
	this->m_worldToCamera = glm::lookAt(this->m_position, this->m_center, this->m_up);
}