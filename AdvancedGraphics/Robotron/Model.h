//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2016 Media Design School
//
//	File Name	:	Model.h
//	Description	:	Model declaration file
//	Author		:	Casey Chim
//	Mail		:	casey.chi6605@mediadesign.school.nz
//

#pragma once

#ifndef __MODEL_H__
#define __MODEL_H__

//#include "Utils.h"
#include "GameScene.h"

using namespace glm;

class CModel
{
public:
	//Constructors & Deconstructors
	CModel(vec3 _Position, GLsizei _NumVertices, CCamera* _camera);
	~CModel();

	//Opengl Functions
	void init(ModelType _eType, float _fModelScale, std::string _sTexturePath);
	void render();
	void render(vec3 _vMovement);

	//Positional Functions
	void SetPosition(vec3 _vNewPosition);
	void GetPosition(vec3& _rPosition);
	vec3& GetPosition();
	
	//Model Functions
	float GetScale();

	//Model Rotation Functions
	void SetDoRotation();
	void SetDoRotation(bool _bState);
	void SetRotation(GLfloat _newRotation);
	void SetRotationAxes(GLfloat _xAxis, GLfloat _yAxis, GLfloat _zAxis);

	//Orbit Functions
	void SwapRotation();
	void SetDoOrbit();
	void SetDoOrbit(bool _bState);
	void SetOrbitCenter(vec3 m_newCenter);
	void SetParentBody(CGameEntity* _newParent);
	void SetOrbitRotation(GLfloat _newRotation);
	void SetOrbitAxes(GLfloat _xAxis, GLfloat _yAxis, GLfloat _zAxis);

	//Static Orbit Functions
	void static IncreaseOrbitSpeed();
	void static DecreaseOrbitSpeed();

private:
	//Camera/Shader/Vertices
	CCamera* m_Camera;
	GLuint program;
	GLuint texture, texture2;
	GLuint vao, vbo, ebo;
	GLsizei m_NumVertices;
	ModelType m_ModelType;
	MovementType m_MoveType;

	//Positional Members
	vec3 m_StartPosition;
	float m_PositionModifier;
	vec3* m_CurrentPosition;

	//Model Members
	float m_fModelScale;

	//Orbit Members
	//CModel* m_ParentBody;
	CGameEntity* m_ParentBody;
	vec3 m_OrbitCenter;
	static float m_sOrbitSpeed;

	//Orbit Rotations
	bool m_DoOrbit;
	GLfloat m_OrbitRotation;
	GLfloat m_OrbitAxisX;
	GLfloat m_OrbitAxisY;
	GLfloat m_OrbitAxisZ;

	//Model Rotations
	bool m_DoRotation;
	GLfloat m_Rotation;
	GLfloat m_RotationDirection;
	GLfloat m_RotationAxisX;
	GLfloat m_RotationAxisY;
	GLfloat m_RotationAxisZ;

	//Time Members
	static GLfloat Time;
	GLfloat m_LastTime;

	//Static Members
	static bool InitDone;

};

#endif //__MODEL_H__