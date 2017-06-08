#pragma once

#ifndef __GAMEENTITY_H__
#define __GAMEENTITY_H__

#include "Utils.h"
class CModel;

using namespace glm;
using namespace std;

class CGameEntity
{
	//Functions
public:
	virtual bool Initialise(string _sNewID, int _iHealth, vec3 _vPosition, bool _bIsActive) = 0;
	virtual void update(unsigned char _keyState[255], GLfloat _fDeltaTime) = 0;
	virtual void render() = 0;
	virtual bool checkCollision(CGameEntity* _pEntity1) = 0;

	virtual CModel* GetModel() = 0;
	virtual CModel* GetShadowModel() = 0;
	virtual vec3& GetPosition() = 0;
	virtual void GetPosition(vec3& _rResult) = 0;
	virtual vec3& GetDirection() = 0;
	virtual bool GetActive() = 0;
	virtual void SetModel(CModel*_pNewModel) = 0;
	virtual void SetShadowModel(CModel* _pNewShadow) = 0;
	virtual void SetActive(bool _bNewState) = 0;
	
	//Returns true if entity has full health
	virtual bool FullHealth() = 0;
	virtual void IncreaseHealth() = 0;
	virtual void DecreaseHealth() = 0;

private:

	//Members
public:


private:

protected:
	string m_sID;
	CModel* m_pModel;
	CModel* m_pShadowModel;

	glm::vec3 m_vDirection;
	glm::vec3 m_vVelocity;

	bool m_bIsActive;
	bool m_bShadowActive;

	int m_iMaxHealth;
	int m_iHealth;
};

#endif //__GAMEENTITY_H__