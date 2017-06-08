#pragma once

#include "glew.h"
#include "freeglut.h"
#include <iostream>


class TripleShaderLoader
{
private:

	std::string ReadShader(char *filename);
	GLuint CreateShader(GLenum shaderType,
		std::string source,
		char* shaderName);

public:

	TripleShaderLoader(void);
	~TripleShaderLoader(void);
	GLuint CreateProgram(char* VertexShaderFilename,
		char* FragmentShaderFilename, char* GeometryShaderFilename);

};