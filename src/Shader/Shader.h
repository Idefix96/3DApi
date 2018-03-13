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
	GLuint m_programId;
public:
	Shader();
	void loadProgram(std::string folderName);
	void SetupShader(std::string file_name, GLenum shaderType);
	GLuint getShaderID();
	void setTransformFeedbackVaryings(const char* varyings);
};

#endif