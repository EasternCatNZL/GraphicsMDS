#include "Light.h"

CLight::CLight()
{
	m_sID = " ";
	m_pModel = nullptr;
	m_fSpeed = 5;
	m_vDirection = vec3(0.0f, 0.0f, 0.0f);
	m_bIsActive = true;
}
CLight::~CLight()
{

}
bool CLight::Initialise(string _sNewID, int _iHealth, vec3 _vPosition, bool _bIsActive)
{
	if (m_sID == "\0")
	{
		m_sID = _sNewID;
	}
	m_bIsActive = _bIsActive;
	m_pModel->SetPosition(_vPosition);
	return true;
}
void CLight::update(unsigned char _keyState[255], GLfloat _fDeltaTime)
{
	vec3 newPosition = m_pModel->GetPosition();
	if (_keyState[(unsigned char)'i'] == BUTTON_DOWN){
		m_pModel->SetPosition(newPosition - vec3(0.0f, 0.0f, m_fSpeed) * _fDeltaTime);
	}
	if (_keyState[(unsigned char)'k'] == BUTTON_DOWN){

		m_pModel->SetPosition(newPosition + vec3(0.0f, 0.0f, m_fSpeed) * _fDeltaTime);
	}
	if (_keyState[(unsigned char)'j'] == BUTTON_DOWN){

		m_pModel->SetPosition(newPosition - vec3(m_fSpeed, 0.0f, 0.0f) * _fDeltaTime);
	}

	if (_keyState[(unsigned char)'l'] == BUTTON_DOWN){

		m_pModel->SetPosition(newPosition + vec3(m_fSpeed, 0.0f, 0.0f) * _fDeltaTime);
	}

	if (_keyState[(unsigned char)'h'] == BUTTON_DOWN){

		m_pModel->SetPosition(newPosition - vec3(0.0f, m_fSpeed, 0.0f) * _fDeltaTime);
	}

	if (_keyState[(unsigned char)'y'] == BUTTON_DOWN){

		m_pModel->SetPosition(newPosition + vec3(0.0f, m_fSpeed, 0.0f) * _fDeltaTime);
	}
}
void CLight::render()
{
	m_pModel->render();
}
bool CLight::checkCollision(CGameEntity* _pEntity1)
{
	return false;
}

CModel* CLight::GetModel()
{
	return m_pModel;
}
CModel* CLight::GetShadowModel()
{
	return nullptr;
}
vec3& CLight::GetPosition()
{
	return m_pModel->GetPosition();
}
void CLight::GetPosition(vec3& _rResult)
{
	_rResult = m_pModel->GetPosition();
}
vec3& CLight::GetDirection()
{
	return vec3(0.0f, 0.0f, 0.0f);
}
bool CLight::GetActive()
{
	return false;
}
void CLight::SetModel(CModel* _pNewModel)
{
	m_pModel = _pNewModel;
}
void CLight::SetShadowModel(CModel* _pNewShadow)
{

}
void CLight::SetActive(bool _bNewState)
{

}

bool CLight::FullHealth()
{
	return false;
}
void CLight::IncreaseHealth()
{

}
void CLight::DecreaseHealth()
{

}

vec3 & CLight::GetColor()
{
	return vec3(1, 1, 1);
}