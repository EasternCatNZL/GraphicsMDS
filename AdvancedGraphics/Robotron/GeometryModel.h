#pragma once

#ifndef __GEOMETRYMODEL_H__
#define __GEOMETRYMODEL_H__

#include "Utils.h"
#include "Camera.h"

class GeometryModel {
public:
	GeometryModel(GLuint program, CCamera* camera);
	void Render();

private:
	GLuint program;
	GLuint vao, vbo;

	vec3 position;

	CCamera* camera;
};

#endif // !__GEOMETRYMODEL_H__
