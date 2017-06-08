//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2016 Media Design School
//
//	File Name	:	Utils.cpp
//	Description	:	Implementation of the Utils.h
//	Author		:	Casey Chim
//	Mail		:	casey.chi6605@mediadesign.school.nz
//

#include "Utils.h"

GLfloat* CUtils::vertices = new GLfloat;
GLuint* CUtils::indices = new GLuint;
int CUtils::verticesSize = 0;
int CUtils::indicesSize = 0;

void CUtils::setSphereData(std::vector<VertexFormat>& vertices, std::vector<GLuint>& indices){

	std::vector<VertexFormat> Vertices;
	std::vector<GLuint> Indices;

	double latitudeBands = 30;
	double longitudeBands = 30;
	double radius = 1.0f;

	for (double latNumber = 0; latNumber <= latitudeBands; latNumber++) {
		double theta = latNumber * 3.14 / latitudeBands;
		double sinTheta = sin(theta);
		double cosTheta = cos(theta);

		for (double longNumber = 0; longNumber <= longitudeBands; longNumber++) {
			double phi = longNumber * 2 * 3.14 / longitudeBands;
			double sinPhi = sin(phi);
			double cosPhi = cos(phi);

			VertexFormat vs;

			vs.texCoord.u = 1 - (longNumber / longitudeBands); // u
			vs.texCoord.v = 1 - (latNumber / latitudeBands);   // v

			vs.normal.x = cosPhi * sinTheta;   // x
			vs.normal.y = cosTheta;            // y
			vs.normal.z = sinPhi * sinTheta;   // z

			vs.pos.x = radius * vs.normal.x;
			vs.pos.y = radius * vs.normal.y;
			vs.pos.z = radius * vs.normal.z;

			Vertices.push_back(vs);
		}
	}



	for (GLuint latNumber = 0; latNumber < latitudeBands; latNumber++) {
		for (GLuint longNumber = 0; longNumber < longitudeBands; longNumber++) {
			GLuint first = (latNumber * (longitudeBands + 1)) + longNumber;
			GLuint second = first + longitudeBands + 1;

			Indices.push_back(first);
			Indices.push_back(second);
			Indices.push_back(first + 1);

			Indices.push_back(second);
			Indices.push_back(second + 1);
			Indices.push_back(first + 1);

		}
	}

	vertices.clear(); indices.clear();
	vertices = Vertices;
	indices = Indices;

}

//GenerateSphere 
// _fSize - decides the size of the sphere
// _eType - decides what sphere is made
void CUtils::GenerateSphere(float _fSize, SphereType _eType)
{
	//Remember to change array size in model.cpp init()
	vertices = new GLfloat[1000];
	indices = new GLuint[690];
	//Zeroing vertices to see clearer during memory debugging
	for (int i = 0; i < 1000; ++i)
	{
		vertices[i] = 0.0f;
	}
	int iCount = 0;
	//Values to create the sphere
	float deltaTheta = 3.1413592f / 12.0f;
	float deltaPhi = 2.0f * 3.1413592f / 10.0f;
	float theta = 0.0f;
	float phi = 0.0f;
	//X,Y,Z Coordinates
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	//RGB Values
	float r = 0.0f;
	float g = 1.0f;
	float b = 0.0f;
	//Texture Coordinates
	float tx1 = 0.0f;
	float tx2 = 1.0f;
	//UV Coords
	float u = 0.0f;
	float v = 0.0f;

	SetVertex(iCount * 8, 0, 1, 0, r, g, b, 0.5f, 1.0f); //North pole end cap
	iCount++;
	for (int ring = 0; ring < 10; ++ring){ //Move to a new z - offset 
		theta += deltaTheta;
		phi = 0.0f;
		for (int point = 0; point < 10; ++point){ //Draw a ring
			phi += deltaPhi;
			x = sin(theta) * cos(phi);
			y = cos(theta);
			z = sin(theta) * sin(phi);

			u = (float)(0.5 + (atan2(-z, -x) / (2 * PI)));
			v = (float)(0.5 - (asin(-y) / PI));

			SetVertex(iCount * 8, x, y, z, r, g, b, u, v);

			iCount++;
		}
		//Switch cases for ring colouring
		switch (ring)
		{
		case 0:
		{
			r = 0.0f;
			g = 0.0f;
			b = 1.0f;
			break;
		}
		case 1:
		{
			r = 1.0f;
			g = 0.0f;
			b = 0.0f;
			break;
		}
		case 2:
		{
			r = 0.0f;
			g = 1.0f;
			b = 0.0f;
			break;
		}
		case 3:
		{
			r = 0.0f;
			g = 0.0f;
			b = 1.0f;
			break;
		}
		case 4:
		{
			r = 1.0f;
			g = 0.0f;
			b = 0.0f;
			break;
		}
		case 5:
		{
			r = 0.0f;
			g = 1.0f;
			b = 0.0f;
			break;
		}
		case 6:
		{
			r = 0.0f;
			g = 0.0f;
			b = 1.0f;
			break;
		}
		case 7:
		{
			r = 1.0f;
			g = 0.0f;
			b = 0.0f;
			break;
		}
		case 8:
		{
			r = 0.0f;
			g = 1.0f;
			b = 0.0f;
			break;
		}
		default:
		{
			r = 1.0f;
			g = 1.0f;
			b = 1.0f;
			break;
		}
		}

	}
	//South pole end cap
	r = 0.0f;
	g = 0.0f;
	b = 1.0f;
	SetVertex(iCount * 8, 0, -1, 0, r, g, b, 0.5, 0); 
	iCount++;

	verticesSize = iCount * 8;

	//Scale the vertices and change the shape
	iCount = 0;
	switch (_eType)
	{
	case(NORMAL) :
	{
		for (int i = 0; i < 1000; ++i)
		{
			if (iCount >= 3)
			{
				i += 5;//Change to i += 4 for a cool bug
				iCount = 0;
			}
			vertices[i] *= _fSize;
			iCount++;
		}
		break;
	}
	case(SQUASH) ://Squashes the sphere down the y axis
	{
		for (int i = 0; i < 1000; ++i)
		{
			vertices[i] *= _fSize;
			vertices[i + 2] *= _fSize;
			i += 7;
		}
		break;
	}
	case(ROSE) :
	{
		for (int i = 0; i < 1000; ++i)
		{
			if (iCount >= 3)
			{
				i += 4;
				iCount = 0;
			}
			vertices[i] *= _fSize;
			iCount++;
		}
		break;
	}
	default: break;
	}

	//Create the indices for a sphere
	int IndicesPos = 0;
	//Create indices connect to the north pole
	for (int i = 0; i < 10; ++i)
	{
		if (i == 9)
		{
			SetIndices(IndicesPos, 0, i + 1, i - 8);
			IndicesPos += 3;
		}
		else
		{
			SetIndices(IndicesPos, 0, i + 1, i + 2);
			IndicesPos += 3;
		}
	}
	//Create the indices for the middle rings
	iCount = 1;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (j == 9)
			{
				SetIndices(IndicesPos, iCount, iCount - 9, iCount + 10);
				IndicesPos += 3;
				SetIndices(IndicesPos, iCount - 9, iCount + 10, iCount + 1);
				IndicesPos += 3;
				iCount++;
			}
			if (j < 9)
			{
				SetIndices(IndicesPos, iCount, iCount + 1, iCount + 10);
				IndicesPos += 3;
				SetIndices(IndicesPos, iCount + 1, iCount + 10, iCount + 11);
				IndicesPos += 3;
				iCount++;
			}
			else
				break;
		}
	}
	//Create the indices for the south pole
	iCount = 101;
	for (int i = 0; i < 10; ++i)
	{

		if (i == 9)
		{
			SetIndices(IndicesPos, 101, iCount - 1, iCount + 8);
			IndicesPos += 3;
			iCount--;
		}

		else if (i < 9)
		{
			SetIndices(IndicesPos, 101, iCount - 1, iCount - 2);
			IndicesPos += 3;
			iCount--;
		}
		else
			break;
	}

	indicesSize = IndicesPos;
}

//GeneratePlane - Generates a plane made of vertices
//(float _fSize) - Determines the overall size of the plane
//(float _fDensity) - Determines how many vertices are in a row
void CUtils::GeneratePlane(float _fSize, int _fDensity)
{
	vertices = new GLfloat[1000];
	indices = new GLuint[1000];

	int iCount = 0;
	//X,Y,Z Coordinates
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	//RGB Values
	float r = 0.0f;
	float g = 1.0f;
	float b = 1.0f;
	//Texture Coordinates
	float tx1 = 0.0f;
	float tx2 = 1.0f;
	//Delta Coordinates
	float delta = _fSize / _fDensity;
	verticesSize = 0;

	for (int i = 0; i < _fDensity; ++i)
	{
		for (int j = 0; j < _fDensity; ++j)
		{
			SetVertex(iCount * 8, x, y, z, r, g, b, tx1, tx2);
			iCount++;
			verticesSize++;
			x += delta;
		}
		g -= 0.1f;
		b -= 0.1f;
		y += delta;
		x = 0;
	}

	int iCursor = 0;
	int IndicesPos = 0;
	for (int i = 0; i < _fDensity; ++i)
	{
		for (int j = 0; j < _fDensity; ++j)
		{
			SetIndices(IndicesPos, iCursor, iCursor + 1, iCursor + _fDensity);
			IndicesPos += 3;
			SetIndices(IndicesPos, iCursor + 1, iCursor + _fDensity, iCursor + _fDensity + 1);
			IndicesPos += 3;
			iCursor++;
		}
	}
	indicesSize = IndicesPos - 3;
	printf("lmao");
}

void CUtils::SetVertex(int start, float x, float y, float z, float r, float g, float b, float tx1, float tx2)
{
	vertices[start] = x;
	vertices[start + 1] = y;
	vertices[start + 2] = z;
	vertices[start + 3] = r;
	vertices[start + 4] = g;
	vertices[start + 5] = b;
	vertices[start + 6] = tx1;
	vertices[start + 7] = tx2;
}

void CUtils::SetIndices(int _arrayPos, int _pos1, int _pos2, int _pos3)
{
	indices[_arrayPos] = static_cast<GLint>(_pos1);
	indices[_arrayPos + 1] = static_cast<GLint>(_pos2);
	indices[_arrayPos + 2] = static_cast<GLint>(_pos3);
}

//SetVertices - Sets the vertices for the shape given
// _eType - Decides what shape to get vertices and indices for
// _fSize - Decides the size of the shape
void CUtils::SetVertices(ModelType _eType, float _fSize)
{
	if (_eType == CUBE)
	{
		//#Note: When changing size, also change VerticesSize below
		vertices = new GLfloat[264]{

			//-1, 1, 1, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  //Top Left
			//1, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Top right
			//-1, -1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, //Bottom Left
			//1, -1, 1, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, //Bottom Right

			//1, 1, 1, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			//1, 1, -1, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			//1, -1, 1, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			//1, -1, -1, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

			//-1, 1, 1, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			//-1, 1, -1, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			//1, 1, 1, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			//1, 1, -1, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

			//-1, 1, -1, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  //Top Left
			//1, 1, 1, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Top right
			//-1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, //Bottom Left
			//1, -1, -1, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, //Bottom Right

			//-1, 1, 1, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			//-1, 1, -1, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			//-1, -1, 1, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			//-1, -1, -1, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

			//-1, -1, 1, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			//-1, -1, -1, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			//1, -1, 1, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			//1, -1, -1, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			//position				   //color		     //tex Coord //Normal
			-_fSize, -_fSize, -_fSize, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
				-_fSize, _fSize, -_fSize, 0.0f, 1.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
				_fSize, _fSize, -_fSize, 1.0f, 0.0f, -0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
				_fSize, -_fSize, -_fSize, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,

				// Fill in the back face vertex data.
				-_fSize, -_fSize, _fSize, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
				-_fSize, _fSize, _fSize, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
				_fSize, _fSize, _fSize, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
				_fSize, -_fSize, _fSize, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

				// Fill in the top face vertex data.
				-_fSize, _fSize, -_fSize, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
				-_fSize, _fSize, _fSize, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				_fSize, _fSize, _fSize, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				_fSize, _fSize, -_fSize, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

				// Fill in the bottom face vertex data.
				-_fSize, -_fSize, -_fSize, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
				-_fSize, -_fSize, _fSize, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
				_fSize, -_fSize, _fSize, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
				_fSize, -_fSize, -_fSize, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

				// Fill in the left face vertex data.
				-_fSize, -_fSize, _fSize, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
				-_fSize, _fSize, _fSize, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
				-_fSize, _fSize, -_fSize, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
				-_fSize, -_fSize, -_fSize, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

				// Fill in the right face vertex data.
				_fSize, -_fSize, _fSize, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
				_fSize, _fSize, _fSize, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				_fSize, _fSize, -_fSize, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				_fSize, -_fSize, -_fSize, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
		};
		verticesSize = 264;

		//INDICES
		indices = new GLuint[36]{
			// front
			0, 1, 2,
				0, 2, 3,
				// top
				4, 5, 6,
				4, 6, 7,
				//0, 1, 8,
				//1, 8,9,
				// back
				8, 9, 10,
				8, 10, 11,
				// bottom
				12, 13, 14,
				12, 14, 15,
				// left
				16, 17, 18,
				16, 18, 19,
				// right
				20, 21, 22,
				20, 22, 23,
		};
		indicesSize = 36;
	}
	else if (_eType == PYRAMID)
	{
		vertices = new GLfloat[192]{
			//position				//color			//texture coord
			-_fSize, -_fSize, -_fSize, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
				-_fSize, _fSize, -_fSize, 0.0f, 1.0f, -0.0f, 0.0f, 0.0f,
				_fSize, _fSize, -_fSize, 1.0f, 0.0f, -0.0f, 1.0f, 0.0f,
				_fSize, -_fSize, -_fSize, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		};
		verticesSize = 32;

		//INDICES
		indices = new GLuint[36]{
			0, 1, 2,
				0, 2, 3,

		};
		indicesSize = 6;
	}
	else if (_eType == DIAMOND)
	{
		vertices = new GLfloat[192]{
			//position			//color			//texture coord
			-_fSize, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f,
				0.0f, _fSize, 0.0f, 0.0f, 1.0f, -0.0f, 0.5f, 0.0f,
				_fSize, 0.0f, 0.0f, 1.0f, 0.0f, -0.0f, 1.0f, 0.5f,
				0.0f, -_fSize, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f,
		};
		verticesSize = 32;

		//INDICES
		indices = new GLuint[36]{
			0, 1, 2,
				0, 2, 3,
		};
		indicesSize = 6;
	}
	else if (_eType == NMS)
	{
		vertices = new GLfloat[192]{
			//position			//color			//texture coord
			-_fSize, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f,
				0.0f, _fSize, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f,
				_fSize, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f,
				0.0f, -_fSize * 2, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f,
				0.0f, 0.0f, -_fSize, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,
				0.0f, 0.0f, _fSize, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f
		};
		verticesSize = 48;

		//INDICES
		indices = new GLuint[36]{
			//Top half
			0, 1, 4,
				4, 1, 2,
				3, 4, 2,
				3, 0, 4,
				//Bottom half
				2, 1, 5,
				3, 2, 5,
				3, 5, 0,
				5, 1, 0
		};
		indicesSize = 24;
	}
	else if (_eType == QUAD)
	{

		vertices = new GLfloat[44]{
			//position					//color				//tex coord		//Normal
			-_fSize,  0.0f, - _fSize,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
			-_fSize, 0.0f, _fSize,		0.0f, 1.0f, -0.0f,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
			_fSize, 0.0f, _fSize,		1.0f, 0.0f, -0.0f,	1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
			_fSize, 0.0f, -_fSize,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,		0.0f, 1.0f, 0.0f
		};
		verticesSize = 44;

		//INDICES
		indices = new GLuint[36]{
			0, 1, 2,
				0, 2, 3,

		};
		indicesSize = 6;
	}
	else if (_eType == TRIANGLE)
	{
		vertices = new GLfloat[192]{
			0.0f, 0.5774f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
				0.5f, -0.2887f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.2f,
				-0.5f, -0.2887f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.2f
		};

		verticesSize = 32;

		indices = new GLuint[36]{
			0, 1, 2,
		};

		indicesSize = 3;
	}
	else if (_eType == RECTANGLE)
	{
		vertices = new GLfloat[192]{
			//position				//color			//texture coord
			-_fSize, -_fSize / 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
				-_fSize, _fSize / 2.0f, 0.0f, 0.0f, 1.0f, -0.0f, 0.0f, 0.0f,
				_fSize, _fSize / 2.0f, 0.0f, 1.0f, 0.0f, -0.0f, 1.0f, 0.0f,
				_fSize, -_fSize / 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		};
		verticesSize = 32;

		//INDICES
		indices = new GLuint[36]{
			0, 1, 2,
				0, 2, 3,

		};
		indicesSize = 6;
	}
	else if (_eType == PLANE)
	{
		GeneratePlane(10,10);
	}
	else if (_eType == SPHERE)
	{
		GenerateSphere(_fSize, NORMAL);
	}
	else if (_eType == SPHERE_SQUASH)
	{
		GenerateSphere(_fSize, SQUASH);
	}
	else if (_eType == SPHERE_ROSE)
	{
		GenerateSphere(_fSize, ROSE);
	}
	
}

GLfloat* CUtils::GetVertices()
{
	return vertices;
}

GLuint* CUtils::GetIndices()
{
	return indices;
}

int CUtils::GetVerticesSize()
{
	return verticesSize;
}

int CUtils::GetIndicesSize()
{
	return indicesSize;
}