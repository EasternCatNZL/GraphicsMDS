//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2016 Media Design School
//
//	File Name	:	Utils.h
//	Description	:	Utils declaration file
//	Author		:	Casey Chim
//	Mail		:	casey.chi6605@mediadesign.school.nz
//

#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <iostream>


#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"

#include "FMOD/fmod.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/ext.hpp"

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "ShaderLoader.h"
#include "TripleShaderLoader.h"

#define BUTTON_UP	0
#define BUTTON_DOWN 1
#define PI 3.14159265359

enum ModelType
{
	PLANE,
	QUAD,
	RECTANGLE,
	CUBE,
	DIAMOND,
	NMS,
	TRIANGLE,
	PYRAMID,
	SPHERE,
	SPHERE_SQUASH,
	SPHERE_ROSE
};

enum SphereType
{
	NORMAL,
	SQUASH,
	ROSE
};

enum MovementType
{
	DIRECTIONAL,
	ORBITING
};

enum CameraType
{
	FLY,
	TRACK,
	ORBIT,
	TOPDOWN,
	STATIC
};

struct Position
{
	float x, y, z;

	Position(float _x, float _y, float _z)
	{
		x = _x, y = _y, z = _z;
	}

	Position(){}
};

struct TexCoord
{
	float u, v;

	TexCoord(float _u, float _v)
	{
		u = _u, v = _v;
	}

	TexCoord(){}
};

struct Normals
{
	float x, y, z;

	Normals(float _x, float _y, float _z)
	{
		x = _x, y = _y, z = _z;
	}

	Normals(){}
};

struct VertexFormat
{
	Position pos;
	TexCoord texCoord;
	Normals normal;

	VertexFormat(Position _pos, TexCoord _texCoord, Normals _normal)
	{
		pos = _pos;
		texCoord = _texCoord;
		normal = _normal;
	}

	VertexFormat(){}
};

class CUtils
{
public:
	static void SetVertices(ModelType _eType, float _fSize);
	static void setSphereData(std::vector<VertexFormat>& vertices, std::vector<GLuint>& indices);
	//Pseudocode used for sphere http://stackoverflow.com/questions/4405787/generating-vertices-for-a-sphere
	static void GenerateSphere(float _fSize, SphereType _eType);
	static void GeneratePlane(float _fSize, int _fDensity);
	static GLfloat* GetVertices();
	static GLuint* GetIndices();
	static int GetVerticesSize();
	static int GetIndicesSize();
private:
	static void SetVertex(int start, float x, float y, float z, float r, float g, float b, float tx1, float tx2);
	static void SetIndices(int _arrayPos, int _pos1, int _pos2, int _pos3);
private:
	static GLfloat* vertices;
	static GLuint* indices;
	static int verticesSize;
	static int indicesSize;
};