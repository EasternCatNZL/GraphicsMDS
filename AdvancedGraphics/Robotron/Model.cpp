//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2016 Media Design School
//
//	File Name	:	Model.cpp
//	Description	:	Implementation of the Model.h
//	Author		:	Casey Chim
//	Mail		:	casey.chi6605@mediadesign.school.nz
//

#include "Model.h"
#include "Utils.h"

using namespace glm;

bool CModel::InitDone = false;
float CModel::m_sOrbitSpeed = 1.0f;
GLfloat CModel::Time = 0.0f;

CModel::CModel(vec3 _Position, GLsizei _NumVertices, CCamera* _camera)
	:m_DoRotation(false),
	m_Rotation(0.0f),
	m_RotationAxisX(0.0f),
	m_RotationAxisY(1.0f),
	m_RotationAxisZ(0.0f),
	m_RotationDirection(1.0f),
	m_DoOrbit(false),
	m_OrbitRotation(0.0f),
	m_OrbitAxisX(0.0f),
	m_OrbitAxisY(1.0f),
	m_OrbitAxisZ(0.0f)
{
	m_OrbitCenter = vec3(0, 0, 0);
	m_ParentBody = nullptr;

	m_Camera = _camera;
	m_StartPosition = _Position;
	m_CurrentPosition = new vec3(_Position);

	m_NumVertices = _NumVertices;


}


CModel::~CModel()
{


	m_ParentBody = nullptr;
}

void CModel::init(ModelType _eType, float _fModelScale, std::string _sTexturePath)
{

	//Set member variables
	m_fModelScale = _fModelScale;
	m_ModelType = _eType;

	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("Coord_System_Texture_Quad.vs", "Coord_System_Texture_Quad.fs");//###Change this later###//

	if (!InitDone)
	{
		glEnable(GL_DEPTH_TEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_FILL, GL_LINE
	}
	//Remember to keep the size the same across classes
	GLfloat vertices[1000];
	GLuint indices[690];
	//Set vertices in CUtils
	CUtils::SetVertices(_eType, _fModelScale);

	//Get the vertices from CUtils and put into a constant array
	GLfloat* pTemp = CUtils::GetVertices();
	for (int i = 0; i < CUtils::GetVerticesSize(); ++i)
	{
		vertices[i] = *pTemp;
		pTemp++;
	}

	//Get the indices from CUtils and put into a constant array
	GLuint* pTemp2 = CUtils::GetIndices();
	for (int j = 0; j < CUtils::GetIndicesSize(); ++j)
	{
		indices[j] = *pTemp2;
		pTemp2++;
	}

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;

	unsigned char* image = SOIL_load_image(_sTexturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	printf("%s\n", SOIL_last_result());

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 100, 100, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (InitDone == false)
		InitDone = true;

}

void CModel::render()
{
	//glClearColor(0.0f, 0.6f, 1.0f, 1.0f);

	//Shader to use
	glUseProgram(program);

	//Texture Uniform Variables
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "Texture"), 0);

	glBindVertexArray(vao);

	//Current Time Uniform Variable
	GLfloat currentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
	currentTime = currentTime / 1000;

	GLint currentTimeLocation = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLocation, currentTime);

	Time = currentTime;

	vec3 LightPos = GameScene::GetInstance().GetLight()->GetPosition();

	//lighting uniform Variables
	glUniform3f(glGetUniformLocation(program, "lightColor"), 0.2f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(program, "diffuseColor"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(program, "objectColor"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(program, "lightPosition"), LightPos.x, LightPos.y, LightPos.z);

	//Translating the model
	GLint modelLoc = glGetUniformLocation(program, "model");

	glm::mat4 model;

	model = glm::translate(model, m_StartPosition);

	//Finish up render function
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, m_NumVertices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glm::mat4 view;
	glm::mat4 projection;

	view = m_Camera->GetView();

	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)800, 0.1f, 100.0f);

	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projLoc = glGetUniformLocation(program, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

}

//Render function that takes a direction and speed
void CModel::render(vec3 _vMovement)
{
	glClearColor(0.0f, 0.6f, 1.0f, 1.0f);

	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "Texture"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(program, "Texture2"), 1);

	glBindVertexArray(vao);

	GLfloat currentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
	currentTime = currentTime / 1000;

	GLint currentTimeLocation = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLocation, currentTime);

	Time = currentTime;

	//Translating the model
	GLint modelLoc = glGetUniformLocation(program, "model");

	glm::mat4 model;
	model = glm::translate(model, *m_CurrentPosition + _vMovement);

	//Calculate new position
	glm::mat4 tempModel;
	tempModel = glm::translate(tempModel, _vMovement);

	vec4 result = tempModel * vec4(*m_CurrentPosition, 1.0f);
	vec3* temp = new vec3(result);

	*m_CurrentPosition = *temp;

	//Finish up the render function
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, m_NumVertices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glm::mat4 view;
	glm::mat4 projection;

	view = m_Camera->GetView();

	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)800, 0.1f, 100.0f);

	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projLoc = glGetUniformLocation(program, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

}

void CModel::SetDoOrbit()
{
	if (m_DoOrbit)
		m_DoOrbit = false;
	else if (!m_DoOrbit)
		m_DoOrbit = true;
}

void CModel::SetDoOrbit(bool _bState){m_DoOrbit = _bState; }

void CModel::SetOrbitRotation(GLfloat _newRotation){m_OrbitRotation = _newRotation; }

void CModel::SetOrbitAxes(GLfloat _xAxis, GLfloat _yAxis, GLfloat _zAxis)
{
	m_OrbitAxisX = _xAxis;
	m_OrbitAxisY = _yAxis;
	m_OrbitAxisZ = _zAxis;
}

void CModel::SetDoRotation()
{
	if (m_DoRotation)
		m_DoRotation = false;
	else if (!m_DoRotation)
		m_DoRotation = true;
}

void CModel::SetDoRotation(bool _bState){m_DoRotation = _bState; }

void CModel::SetRotation(GLfloat _newRotation){m_Rotation = _newRotation; }

void CModel::SetRotationAxes(GLfloat _xAxis, GLfloat _yAxis, GLfloat _zAxis)
{
	m_RotationAxisX = _xAxis;
	m_RotationAxisY = _yAxis;
	m_RotationAxisZ = _zAxis;
}

void CModel::SwapRotation(){ m_RotationDirection *= -1; }

void CModel::SetOrbitCenter(vec3 m_newCenter){m_OrbitCenter = m_newCenter; }

void CModel::SetPosition(vec3 _vNewPosition){ m_StartPosition = _vNewPosition; *m_CurrentPosition = _vNewPosition; }

//GetPosition - Returns the current position of the model
void CModel::GetPosition(vec3& _rPosition){_rPosition = *m_CurrentPosition;}

vec3& CModel::GetPosition(){return *m_CurrentPosition;}

float CModel::GetScale(){ return m_fModelScale;  }

void CModel::SetParentBody(CGameEntity* _newParent){m_ParentBody = _newParent; }

void CModel::DecreaseOrbitSpeed()
{
	if (m_sOrbitSpeed < 1)
		m_sOrbitSpeed += 0.1f;
	printf("%f\n", m_sOrbitSpeed);
}

void CModel::IncreaseOrbitSpeed()
{
	if (m_sOrbitSpeed > 0.1)
		m_sOrbitSpeed -= 0.1f;
	printf("%f\n", m_sOrbitSpeed);
}
