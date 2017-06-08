#include "Camera.h"
#include "Cubemap.h"

class ReflectionModel
{
public:
	ReflectionModel(GLuint _program, CCamera* _camera, Cubemap* _skybox);
	~ReflectionModel();

	CCamera* camera;
	Cubemap* skybox;

	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint program;

	std::vector<VertexFormat>vertices;
	std::vector<GLuint>indices;

	void render();
};