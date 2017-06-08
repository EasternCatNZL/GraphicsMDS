#pragma once

#include <string>
#include <fstream>

#include "Utils.h"
#include "Light.h"
#include "Camera.h"

class CLight;

class Terrain
{
public:
	Terrain(std::wstring HeightmapFilename, std::string texFileName, std::string texFileName1, std::string texFileName2, GLuint program, CCamera* camera, CLight* light);
	~Terrain();

	CLight* light;
	CCamera* camera;
	std::string texFileName;
	std::string texFileName1;
	std::string texFileName2;

	GLuint mNumVertices;
	GLuint mNumFaces;

	GLuint numRows = 513, numCols = 513;
	GLfloat heightScale = 0.35f, heightOffset = 0.0f, cellSpacing = 1.0f;
	std::vector<float> heightmap;
	std::vector<VertexFormat>vertices;
	std::vector<GLuint>indices;
	std::wstring heightmapFilename;

	GLuint vao, vbo, ebo, program, texture, texture1, texture2;

	void loadHeightMap();
	void smooth();
	float average(UINT i, UINT j);
	void createVerticesAndIndices();
	void buildBuffers();
	GLuint setTexture(std::string  texFileName);
	void draw();
};