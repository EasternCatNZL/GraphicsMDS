#include "GeometryModel.h"

GeometryModel::GeometryModel(GLuint program, CCamera * camera)
{
	this->program = program;
	this->camera = camera;

	GLfloat points[] = {
		//pass in one point
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f
	};

	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);

	glGenVertexArrays(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glBindVertexArray(0);
}

void GeometryModel::Render()
{
	glUseProgram(this->program);

	mat4 model;
	model = translate(model, position);

	mat4 mvp = camera->GetProjection() * camera->GetView() * model;

	GLuint vpLoc = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, value_ptr(mvp));

	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}
