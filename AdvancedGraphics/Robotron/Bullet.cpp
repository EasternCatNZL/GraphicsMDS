#include "Bullet.h"

CBullet::CBullet()
{
	m_sID = "\0";
	m_pModel = nullptr;
	m_vDirection = vec3(0.0f, 0.0f, 0.0f);
	m_fSpeed = 30.0f;
	m_bIsActive = false;
}

CBullet::~CBullet()
{
	if (m_pModel != nullptr)
	{
		delete m_pModel;
		m_pModel = nullptr;
	}
}

bool CBullet::Initialise(string _sNewID, int _iHealth, vec3 _vPosition, bool _bIsActive)
{
	if (m_sID == "\0")
	{
		m_sID = _sNewID;
	}
	m_iMaxHealth = _iHealth;
	m_iHealth = _iHealth;
	m_bIsActive = _bIsActive;
	m_pModel->SetPosition(_vPosition);
	return true;
}

void CBullet::update(unsigned char _keyState[255], GLfloat _fDeltaTime)
{
	
	if (m_bIsActive)
	{
		//Check if the bullet is out of bounds and if health is <= 0
		if (glm::distance(vec3(0.0f, 0.0f, 0.0f), this->GetPosition()) > 15|| m_iHealth <= 0)
		{
			m_bIsActive = false;
		}
	}
	else
	{
		m_pModel->SetPosition(vec3(0.0f, 0.0f, -50.0f));
	}
}

void CBullet::render()
{
	if (m_pModel != nullptr && m_bIsActive)
	{
		m_pModel->render(m_vDirection);
	}
}

bool CBullet::checkCollision(CGameEntity* _pEntity1)
{

	bool collisionX = this->GetPosition().x + this->GetModel()->GetScale() >= _pEntity1->GetPosition().x &&
		_pEntity1->GetPosition().x + _pEntity1->GetModel()->GetScale() >= this->GetPosition().x;

	bool collisionY = this->GetPosition().y + this->GetModel()->GetScale() >= _pEntity1->GetPosition().y &&
		_pEntity1->GetPosition().y + _pEntity1->GetModel()->GetScale() >= this->GetPosition().y;

	bool collisionZ = this->GetPosition().z + this->GetModel()->GetScale() >= _pEntity1->GetPosition().z &&
		_pEntity1->GetPosition().z + _pEntity1->GetModel()->GetScale() >= this->GetPosition().z;

	if (collisionX && collisionY && collisionZ) {
		//printf("Colliding \n");
		return true;
	}
	else{
		//printf("Not - Colliding \n");
		return false;
	}
}



void CBullet::SetModel(CModel* _pNewModel){ m_pModel = _pNewModel; }

void CBullet::SetShadowModel(CModel* _pNewShadow){ m_pShadowModel = _pNewShadow; }

void CBullet::SetActive(bool _bNewState){ m_bIsActive = _bNewState; }

void CBullet::SetDirection(vec3 _vNewDirection){ m_vDirection = _vNewDirection; }

void CBullet::SetPosition(vec3 _vNewPosition)
{ 
	m_pModel->SetPosition(_vNewPosition); 
}

bool CBullet::GetActive(){ return m_bIsActive; }

void CBullet::GetPosition(vec3& _rResult){ m_pModel->GetPosition(_rResult); }

vec3& CBullet::GetPosition(){ return m_pModel->GetPosition(); }

vec3& CBullet::GetDirection(){ return m_vDirection; }

CModel* CBullet::GetModel(){ return m_pModel; }

CModel* CBullet::GetShadowModel(){ return m_pShadowModel; }

bool CBullet::FullHealth()
{
	if (m_iHealth == m_iMaxHealth)
		return true;
	return false;
}

void CBullet::IncreaseHealth()
{
	if (m_iHealth != m_iMaxHealth)
	{
		m_iHealth++;
	}
}
void CBullet::DecreaseHealth()
{
	if (m_iHealth > 0)
	{
		m_iHealth--;
	}
}