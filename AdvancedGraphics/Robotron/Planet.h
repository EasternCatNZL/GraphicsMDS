#pragma once

#include"GameEntity.h"
#include "Model.h"

class CPlanet : public CGameEntity
{
	//Functions
public:
	CPlanet();
	~CPlanet();
	virtual bool Initialise(string _sNewID, int _iHealth, vec3 _vPosition, bool _bIsActive);
	virtual void update(unsigned char _keyState[255], GLfloat _fDeltaTime);
	virtual void render();
	virtual bool checkCollision(CGameEntity* _pEntity1);

	virtual CModel* GetModel();
	virtual CModel* GetShadowModel();
	virtual vec3& GetPosition();
	virtual void GetPosition(vec3& _rResult);
	virtual vec3& GetDirection();
	virtual bool GetActive();
	virtual void SetModel(CModel* _pNewModel);
	virtual void SetShadowModel(CModel* _pNewShadow);
	virtual void SetActive(bool _bNewState);

	virtual bool FullHealth();
	virtual void IncreaseHealth();
	virtual void DecreaseHealth() ;
private:

	//Members
public:

private:

};