//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2016 Media Design School
//
//	File Name	:	main.cpp
//	Description	:	Setup and runs the solar system
//	Author		:	Casey Chim
//	Mail		:	casey.chi6605@mediadesign.school.nz
//


#define MOUSE_LEFT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2

#include <iostream>
#include <vector>

#include "GameScene.h"


bool Pressed = false;

CCamera* MainCamera;
int CameraFocus;

unsigned char keyState[255]; //tracks keystates for keyboard
unsigned char mouseStates[3]; //tracks mouse states

std::vector<CModel*> Models{};

using namespace glm;

void keyboard(unsigned char key, int x, int y)
{
	keyState[key] = BUTTON_DOWN;
	Pressed = true;
	GameScene::GetInstance().SetPressed(Pressed);

}

void keyboard_up(unsigned char key, int x, int y)
{
	keyState[key] = BUTTON_UP;
	Pressed = false;
	GameScene::GetInstance().SetPressed(Pressed);
}

void mouseUpdate( int _iX, int _iY)
{
	//Run the GameScene mouse update function
	GameScene::GetInstance().mouseUpdate( _iX, _iY);
}

void render()
{
	//Run the GameScene render function
	GameScene::GetInstance().render();
}

void update()
{
	//Run the GameScene update function
	GameScene::GetInstance().update(keyState);	
}

int main(int argc, char **argv)
{

	
	GLsizei WIDTH = 800;
	GLsizei HEIGHT = 800;

	// init glut
	glutInit(&argc, argv);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(500, 300);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Solar System");



	HWND name;
	name = GetForegroundWindow();
	//glutSetCursor(GLUT_CURSOR_NONE);

	//init GLEW
	glewInit();

	//Initialize the GameScene
	GameScene::GetInstance().Init(name);

	// register callbacks
	glutDisplayFunc(render);

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);

	glutPassiveMotionFunc(mouseUpdate);

	glutIdleFunc(update);
	glutMainLoop();

	return 0;

}

