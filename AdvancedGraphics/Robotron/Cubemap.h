#pragma once

#include <vector>

#include "Camera.h"

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

class Cubemap
{ 
public:
	Cubemap(GLuint program, CCamera* camera);
	~Cubemap();

	void render();

	CCamera* camera;
	
	std::vector<VertexFormat>vertices;
	std::vector<GLuint>indices;

	GLuint loadCubemap(std::vector<const GLchar*> faces);

	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint texture;
	GLuint program;

	GLuint getTextureID();
};