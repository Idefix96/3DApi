#include "types.h"
#include "GL\glew.h"
#include <iostream>
#include "Config.h"
#include <fstream>
#include <istream>
#include <string>
#include <filesystem>
#include <iostream>

#ifndef _SHADER_H_
#define _SHADER_H_


class Shader
{
private:
	GLuint VertexShaderID;
	GLuint FragmentShaderID;
	GLuint GeometryShaderID;
	GLuint ProgramID;

public:
	Shader();
	void SetupVertexShader(std::string file_name);
	void SetupGeometryShader(std::string file_name);
	void SetupFragmentShader(std::string file_name);
	void LinkShader();
	GLuint getShaderID();
	void setTransformFeedbackVaryings(const char* varyings);
};

#endif