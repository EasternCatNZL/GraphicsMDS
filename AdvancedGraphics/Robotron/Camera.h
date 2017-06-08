//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2016 Media Design School
//
//	File Name	:	Camera.h
//	Description	:	Camera declaration file
//	Author		:	Casey Chim
//	Mail		:	casey.chi6605@mediadesign.school.nz
//

#pragma once

#ifndef __CAMERA_H__
#define __CAMERA_H__



#include "Utils.h"
#include "GameEntity.h"

using namespace glm;

class CCamera
{
public:
	//Camera Constructors & Deconstructors
	CCamera(CameraType _eCamTypevec3, vec3 _Pos, vec3 _Front, vec3 _Up, GLuint _WIDTH, GLuint _HEIGHT);
	~CCamera();

	//Orbit Functions
	void SetOrbitCenter(vec3 _NewPos);
	void SetDoOrbit(bool _bState);
	void SetRadius(GLfloat _NewRadius);

	//Camera Getter & Setters
	void SetType(CameraType _eNewType);
	void SetMouseSpeed(GLfloat _newSpeed);
	void SetPosition(vec3 _NewPos);
	void SetFront(vec3 _NewFront);
	void SetRight(vec3 _NewRight);
	void SetUp(vec3 _NewUp);
	void SetTarget(CGameEntity* _pNewTarget);

	GLfloat GetMouseSpeed();
	vec3 GetPosition();
	vec3 GetFront();
	vec3 GetRight();
	vec3 GetUp();
	CGameEntity* GetTarget();

	mat4 GetView();
	mat4 GetProjection();

	void update(unsigned char _keyState[255], const float _deltaTime);
private:
	//Orbit Members
	bool m_DoOrbit;
	vec3 m_OrbitCenter;
	GLfloat m_radius;

	//Camera Members
	CameraType m_camType;
	GLfloat m_cameraSpeed;
	GLfloat m_cameraMouseSpeed;
	vec3 m_cameraPos;
	vec3 m_cameraFront;
	vec3 m_cameraRight;
	vec3 m_cameraUp;
	CGameEntity* m_cameraTarget;

	//Window Members
	GLuint WIDTH, HEIGHT;
};

#endif //__CAMERA_H__