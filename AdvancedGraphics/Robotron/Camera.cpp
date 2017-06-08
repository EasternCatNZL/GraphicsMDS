//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2016 Media Design School
//
//	File Name	:	Camera.cpp
//	Description	:	Implementation of the Camera.h
//	Author		:	Casey Chim
//	Mail		:	casey.chi6605@mediadesign.school.nz
//

#include "Camera.h"

using namespace glm;

CCamera::CCamera(CameraType _eCamType, vec3 _Pos, vec3 _Front, vec3 _Up, GLuint _WIDTH, GLuint _HEIGHT) :m_DoOrbit(false)
{
	//Camera values
	m_camType = _eCamType;
	m_cameraSpeed = 1.0f;
	m_cameraMouseSpeed = 1.0f;
	m_cameraPos = _Pos;
	m_cameraFront = _Front;
	m_cameraUp = _Up;
	m_cameraRight = vec3(1.0f, 0.0f, 0.0f);
	m_cameraTarget = nullptr;

	//Orbit values
	m_radius = -15.0f;
	m_OrbitCenter = vec3(0.0f, 0.0f, 0.0f);

	//Window values
	WIDTH = _WIDTH;
	HEIGHT = _HEIGHT;
}

CCamera::~CCamera()
{

}

void CCamera::update(unsigned char _keyState[255], const float _deltaTime)
{
	float _fActualSpeed = m_cameraSpeed * _deltaTime;
	switch (m_camType)
	{
	case FLY:
	{
		if (_keyState[(unsigned char)'w'] == BUTTON_DOWN){

			m_cameraPos += m_cameraFront * _fActualSpeed;
			//m_cameraFront = m_cameraPos + normalize(m_cameraFront);
		}
		if (_keyState[(unsigned char)'s'] == BUTTON_DOWN){

			m_cameraPos -= m_cameraFront * _fActualSpeed;
			//m_cameraFront = m_cameraPos + normalize(m_cameraFront);
		}
		if (_keyState[(unsigned char)'q'] == BUTTON_DOWN){

			m_cameraFront -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * _fActualSpeed;
		}
		if (_keyState[(unsigned char)'e'] == BUTTON_DOWN){

			m_cameraFront += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * _fActualSpeed;
		}

		if (_keyState[(unsigned char)'a'] == BUTTON_DOWN){

			m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * _fActualSpeed;
		}

		if (_keyState[(unsigned char)'d'] == BUTTON_DOWN){

			m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * _fActualSpeed;
		}

		if (_keyState[(unsigned char)'f'] == BUTTON_DOWN){

			m_cameraPos -= m_cameraUp * _fActualSpeed;		
		}

		if (_keyState[(unsigned char)'r'] == BUTTON_DOWN){

			m_cameraPos += m_cameraUp * _fActualSpeed;
		}
		break;
	}
	case TRACK:
	{
		if (m_cameraTarget == nullptr)
		{
			m_cameraFront = vec3(0.0f, 0.0f, 0.0f);
		}
		else if (m_cameraTarget != nullptr)
		{
			vec3 newTarget;
			m_cameraTarget->GetPosition(newTarget);
			m_cameraFront = newTarget;
		}
		break;
	}
	case ORBIT:
	{
		if (m_DoOrbit)
		{
			GLfloat currentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
			currentTime = currentTime / 10000;

			m_cameraPos.x = m_OrbitCenter.x + m_radius * sin(currentTime);
			m_cameraPos.z = m_OrbitCenter.y + m_radius * cos(currentTime);
		}
		break;
	}
	case TOPDOWN:
	{
		m_cameraUp = vec3(0.0f, 0.0f, 1.0f);
		if (m_cameraTarget == nullptr)
		{
			m_cameraFront = vec3(0.0f, 0.0f, 0.0f);
			m_cameraPos = vec3(0.0f, 30.0f, 0.0f);
		}
		else if (m_cameraTarget != nullptr)
		{
			vec3 newTarget;
			m_cameraTarget->GetPosition(newTarget);
			m_cameraFront = newTarget;

			vec3 newPos;
			m_cameraTarget->GetPosition(newPos);
			newPos += vec3(0.0f, 30.0f, 0.0f);
			m_cameraPos = newPos;
		}
		break;
	}
	case STATIC:
	{
		break;
	}
	default:break;
	}
	//printf("\nCamera Pos: %f %f %f", m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);
}

//Getters & Setters
mat4 CCamera::GetView()
{
	mat4 view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
	return view;
}

mat4 CCamera::GetProjection()
{
	mat4 projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)800, 0.1f, 100.0f);
	return projection;
}

void CCamera::SetDoOrbit(bool _bState){ m_DoOrbit = _bState; }
void CCamera::SetOrbitCenter(vec3 _NewPos){m_OrbitCenter = _NewPos;}
void CCamera::SetRadius(GLfloat _NewRadius){m_radius = _NewRadius;}

void CCamera::SetType(CameraType _eNewType){ m_camType = _eNewType; }
void CCamera::SetMouseSpeed(GLfloat _fNewSpeed){ m_cameraMouseSpeed = _fNewSpeed; }
void CCamera::SetPosition(vec3 _vNewPos){m_cameraPos = _vNewPos;}
void CCamera::SetFront(vec3 _vNewFront){m_cameraFront = _vNewFront;}
void CCamera::SetRight(vec3 _vNewRight){ m_cameraRight = _vNewRight; }
void CCamera::SetUp(vec3 _vNewUp){m_cameraUp = _vNewUp;}
void CCamera::SetTarget(CGameEntity* _pNewTarget){ m_cameraTarget = _pNewTarget; }

GLfloat CCamera::GetMouseSpeed(){ return m_cameraMouseSpeed; }
vec3 CCamera::GetPosition(){return m_cameraPos;}
vec3 CCamera::GetFront(){return m_cameraFront;}
vec3 CCamera::GetRight(){ return m_cameraRight; }
vec3 CCamera::GetUp(){return m_cameraUp;}
CGameEntity* CCamera::GetTarget(){ return m_cameraTarget; }
