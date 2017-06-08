//The GameScene class was not implemented
//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2016 Media Design School
//
//	File Name	:	GameScene.cpp
//	Description	:	Implementation of the GameScene.h
//	Author		:	Casey Chim
//	Mail		:	casey.chi6605@mediadesign.school.nz
//

#include "GameScene.h"

GameScene* GameScene::Instance = nullptr;

GameScene::GameScene()
{
	m_pGround = nullptr;
	m_iLevel = 0;
	m_iScene = 0;
	m_iMenuItem = 0;
	m_fLastMouseX = 0.0f;
	m_fLastMouseY = 0.0f;
	srand(time(NULL));
}

GameScene::~GameScene()
{
	delete MainCamera;
	MainCamera = nullptr;

	delete MainLight;
	MainLight = nullptr;

	delete m_pGround;
	m_pGround = nullptr;
}

void GameScene::Init(HWND _name)
{
	name = _name;
	//Optionss
	m_bMSAA = true;
	m_bWireframe = true;
	m_bCull = true;
	m_bDepth = true;
	//Shader Loading
	GLuint SkyboxProgram;
	GLuint ReflectionProgram;
	GLuint Model3DProgram;
	GLuint HeightMapProgram;
	ShaderLoader shaderLoader;
	ShaderLoader tripleLoader;
	GLuint GeoProgram;
	SkyboxProgram = shaderLoader.CreateProgram("Skybox_Shader.vs", "Skybox_Shader.fs");
	ReflectionProgram = shaderLoader.CreateProgram("Reflection_Shader.vs", "Reflection_Shader.fs");
	Model3DProgram = shaderLoader.CreateProgram("3D_Model_Shader.vs", "3D_Model_Shader.fs");
	HeightMapProgram = shaderLoader.CreateProgram("heightmap.vs", "heightmap.fs");
	GeoProgram = tripleLoader.CreateProgram("Geo.vs", "Geo.fs", "Geo.gs");


	WIDTH = 800;
	HEIGHT = 800;
	HalfWidth = WIDTH / 2;
	HalfHeight = HEIGHT / 2;

	LastTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
	//Setup Camera
	MainCamera = new CCamera(FLY, vec3(0.0f, 7.0f, 3.0f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 0.0f), WIDTH, HEIGHT);
	//Setup Light
	MainLight = new CLight();
	CModel* newModel = new CModel(vec3(0.0f, 7.0f, 0.0f), 36, MainCamera);
	newModel->init(CUBE, 0.5f, "Assets/textures/Green.png");
	MainLight->SetModel(newModel);
	//Setup Skybox
	m_pSkybox = new Cubemap(SkyboxProgram, MainCamera);

	m_pSphere = new ReflectionModel(ReflectionProgram, MainCamera, m_pSkybox);

	m_p3DCastle = new Model("Assets/models/castle2/castle.obj", MainCamera, Model3DProgram);

	terrain = new Terrain(L"Assets/heightmap/terrain.raw", "Assets/heightmap/rock.jpg", "Assets/heightmap/grass.jpg", "Assets/heightmap/sand.jpg", HeightMapProgram, MainCamera, MainLight);

	geoModel = new GeometryModel(GeoProgram, MainCamera);
	

	m_pBox = new CPlanet();
	//Create model
	newModel = new CModel(vec3(6.0f, 5.0f, 0.0f), 36, MainCamera);
	newModel->init(CUBE, 1.0f, "Assets/textures/Red.png");
	//Set the entities model
	m_pBox->SetModel(newModel);
	//Add entity to entity vector
	Entities.push_back(m_pBox);

	m_pMirror = new CPlanet();
	//Create model
	newModel = new CModel(vec3(6.0f, 4.0f, 0.0f), 36, MainCamera);
	newModel->init(QUAD, 4.0f, "Assets/textures/Green.png");
	//Set the entities model
	m_pMirror->SetModel(newModel);
	//Add entity to entity vector
	Entities.push_back(m_pMirror);

	m_pInvertedBox = new CPlanet();
	//Create model
	newModel = new CModel(vec3(6.0f, 3.0f, 0.0f), 36, MainCamera);
	newModel->init(CUBE, 1.0f, "Assets/textures/Red.png");
	//Set the entities model
	m_pInvertedBox->SetModel(newModel);
	//Add entity to entity vector
	Entities.push_back(m_pInvertedBox);
}

void GameScene::ClearScreen()
{
	for (auto iter = Labels.begin(); iter != Labels.end(); ++iter)
	{
		(*iter)->m_bActive = false;
	}
}

void GameScene::render()
{
	glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	MainLight->render();

	if (m_bCull)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
	}

	m_pSphere->render();

	if(m_bCull) glDisable(GL_CULL_FACE);

	//m_p3DCastle->Draw();

	m_pBox->render();

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT);

	m_pMirror->render();
		
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDepthMask(GL_TRUE);

	m_pInvertedBox->render();

	glDisable(GL_STENCIL_TEST);

	m_pSkybox->render();

	//terrain->draw();

	//geoModel->Render();

	glutSwapBuffers();
}

//Frame by frame update
void GameScene::update(unsigned char _keyState[255])
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		cerr << "OpenGL error: " << err << endl;
	}

	//if (name == GetForegroundWindow() || GetWindow(name, GW_CHILD))
	//	glutWarpPointer(WIDTH / 2, HEIGHT / 2);
	GLfloat currentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
	DeltaTime = (currentTime - LastTime) /1000.0f; //Time between last frame and current frame

	//Quick fix for zero deltatime on fast computers
	if (DeltaTime == 0.0f)
	{
		DeltaTime = 0.001;
	}
	LastTime = currentTime;
	
	//printf("\nDeltaTime: %f Time: %f LastTime: %f", DeltaTime, currentTime, LastTime);

	//Update camera
	if (MainCamera != nullptr)
	{
		MainCamera->update(_keyState, DeltaTime);
	}
	if (MainLight != nullptr)
	{
		MainLight->update(_keyState, DeltaTime);
	}
	if (_keyState[(unsigned char)'m'] == BUTTON_DOWN && Pressed)
	{
		if (m_bMSAA)
		{
			m_bMSAA = false;
			glDisable(GL_MULTISAMPLE);
		}
		else if (!m_bMSAA)
		{
			m_bMSAA = true;
			glEnable(GL_MULTISAMPLE);
		}
		Pressed = false;
	}
	if (_keyState[(unsigned char)'n'] == BUTTON_DOWN && Pressed)
	{
		if (m_bWireframe)
		{
			m_bWireframe = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (!m_bWireframe)
		{
			m_bWireframe = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		Pressed = false;
	}
	if (_keyState[(unsigned char)'b'] == BUTTON_DOWN && Pressed)
	{
		if (m_bCull)
		{
			m_bCull = false;
			glDisable(GL_CULL_FACE);
		}
		else if (!m_bCull)
		{
			m_bCull = true;
			glEnable(GL_CULL_FACE);
		}
		Pressed = false;
	}
	if (_keyState[(unsigned char)'v'] == BUTTON_DOWN && Pressed)
	{
		printf("Restarting Level");
		Init(name);
		Pressed = false;
	}
	if (_keyState[(unsigned char)'c'] == BUTTON_DOWN && Pressed)
	{
		if (m_bDepth)
		{
			m_bDepth = false;
			glDepthFunc(GL_ALWAYS);
		}
		else if (!m_bDepth)
		{
			m_bDepth = true;
			glDepthFunc(GL_LESS);
		}
		Pressed = false;
	}
	
	glutPostRedisplay();
}

void GameScene::mouseUpdate( int _iX, int _iY)
{
	//if (name == GetForegroundWindow() || GetWindow(name, GW_CHILD))
	//{
	//	vec3 newCameraFront = MainCamera->GetFront();
	//	vec3 newCameraRight = vec3(0.0f, 0.0f, 0.0f);
	//	//change on x axis
	//	if (_iX > HalfWidth)
	//	{
	//		newCameraFront += glm::normalize(glm::cross(MainCamera->GetFront(), MainCamera->GetUp())) * MainCamera->GetMouseSpeed() * DeltaTime;
	//		glutWarpPointer(HalfWidth, HalfHeight);
	//	}
	//	else if (_iX < HalfWidth)
	//	{
	//		newCameraFront -= glm::normalize(glm::cross(MainCamera->GetFront(), MainCamera->GetUp())) * MainCamera->GetMouseSpeed() * DeltaTime;
	//		glutWarpPointer(HalfWidth, HalfHeight);
	//	}
	//	//change on y axis
	//	if (_iY > HalfHeight)
	//	{
	//		newCameraFront += glm::normalize(glm::cross(MainCamera->GetFront(), vec3(1.0f, 0.0f, 0.0f))) * MainCamera->GetMouseSpeed() * DeltaTime;
	//		glutWarpPointer(HalfWidth, HalfHeight);
	//	}
	//	else if (_iY < HalfHeight)
	//	{
	//		newCameraFront -= glm::normalize(glm::cross(MainCamera->GetFront(), vec3(1.0f, 0.0f, 0.0f))) * MainCamera->GetMouseSpeed() * DeltaTime;
	//		glutWarpPointer(HalfWidth, HalfHeight);
	//	}
	//	MainCamera->SetFront(newCameraFront);
	//	MainCamera->SetRight(newCameraRight);
	//	m_fLastMouseX = _iX;
	//	m_fLastMouseY = _iY;
	//}
	//Check if the window is in focus

	GLfloat xoffset = _iX - m_fLastMouseX;
	GLfloat yoffset = m_fLastMouseY - _iY;
	m_fLastMouseX = _iX;
	m_fLastMouseY = _iY;

	//set offset based on sensitivity
	xoffset *= MainCamera->GetMouseSpeed();
	yoffset *= MainCamera->GetMouseSpeed();

	yaw += xoffset;
	pitch += yoffset;

	//check pitch(y) bounds
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	vec3 front;
	front.x = cos(radians(yaw))* cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(glm::radians(pitch));
	MainCamera->SetFront(normalize(front));
}

void GameScene::SetPressed(bool _NewState){Pressed = _NewState;}

CCamera* GameScene::GetCamera(){return MainCamera;}

CLight* GameScene::GetLight(){return MainLight; }

GameScene& GameScene::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new GameScene();
	}

	return (*Instance);
}