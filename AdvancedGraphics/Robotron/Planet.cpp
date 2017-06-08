#include "Planet.h"

CPlanet::CPlanet()
{
	m_sID = " ";
	m_pModel = nullptr;
	m_vDirection = vec3(0.0f, 0.0f, 0.0f);
	m_bIsActive = false;
}

CPlanet::~CPlanet()
{
	if (m_pModel != nullptr)
	{
		delete m_pModel;
		m_pModel = nullptr;
	}
}

bool CPlanet::Initialise(string _sNewID, int _iHealth, vec3 _vPosition, bool _bIsActive)
{
	if (m_sID == "\0")
	{
		m_sID = _sNewID;
	}
	m_bIsActive = _bIsActive;
	m_pModel->SetPosition(_vPosition);
	return true;
}

void CPlanet::update(unsigned char _keyState[255], GLfloat _fDeltaTime)
{

}

void CPlanet::render()
{
	if (m_pModel != nullptr)
	{
		m_pModel->render();
	}
}

bool CPlanet::checkCollision(CGameEntity* _pEntity1)
{

	bool collisionX = this->GetPosition().x + this->GetModel()->GetScale() >= _pEntity1->GetPosition().x &&
		_pEntity1->GetPosition().x + _pEntity1->GetModel()->GetScale() >= this->GetPosition().x;

	bool collisionY = this->GetPosition().y + this->GetModel()->GetScale() >= _pEntity1->GetPosition().y &&
		_pEntity1->GetPosition().y + _pEntity1->GetModel()->GetScale() >= this->GetPosition().y;

	bool collisionZ = this->GetPosition().z + this->GetModel()->GetScale() >= _pEntity1->GetPosition().z &&
		_pEntity1->GetPosition().z + _pEntity1->GetModel()->GetScale() >= this->GetPosition().z;

	if (collisionX && collisionY && collisionZ) {
		printf("Colliding \n");
		return true;
	}
	else{
		//printf("Not - Colliding \n");
		return false;
	}
}

void CPlanet::SetModel(CModel* _pNewModel){ m_pModel = _pNewModel; }

void CPlanet::SetShadowModel(CModel* _pNewShadow){ m_pShadowModel = _pNewShadow; }

void CPlanet::SetActive(bool _bNewState){ m_bIsActive = _bNewState; }

bool CPlanet::GetActive(){ return m_bIsActive; }

void CPlanet::GetPosition(vec3& _rResult){ m_pModel->GetPosition(_rResult); }

vec3& CPlanet::GetPosition(){ return m_pModel->GetPosition(); }

vec3& CPlanet::GetDirection(){ return m_vDirection; }

CModel* CPlanet::GetModel(){ return m_pModel; }

CModel* CPlanet::GetShadowModel(){ return m_pShadowModel; }

bool CPlanet::FullHealth()
{
	if (m_iHealth == m_iMaxHealth)
		return true;
	return false;
}

void CPlanet::IncreaseHealth()
{ 
	if (m_iHealth != m_iMaxHealth)
	{
		m_iHealth++;
	}
}
void CPlanet::DecreaseHealth()
{
	if (m_iHealth > 0)
	{
		m_iHealth--;
	}
}