#include "stdafx.h"
#include "Shader.h"

namespace fs = std::experimental::filesystem;

Shader::Shader()
{
	this->m_programId = glCreateProgram();
}

void Shader::loadProgram(std::string folderName)
{
	for (auto & p : fs::directory_iterator(SHADER_PATH + folderName + "/"))
	{
		std::string path = p.path().string();
		if (fs::path(p).extension() == VERTEX_SHADER_EXT)
			this->SetupShader(path, GL_VERTEX_SHADER);
		if (fs::path(p).extension() == FRAGMENT_SHADER_EXT)
			this->SetupShader(path, GL_FRAGMENT_SHADER);
		if (fs::path(p).extension() == GEOMETRY_SHADER_EXT)
			this->SetupShader(path, GL_GEOMETRY_SHADER);
	}
	//setup final shader program
	glLinkProgram(this->m_programId);
	glValidateProgram(this->m_programId);
}

void Shader::SetupShader(std::string file_name, GLenum type)
{
	std::string ShaderText;
	std::ifstream file;
	std::string line;

	GLuint id = glCreateShader(type);

	file.open(file_name, std::ios::in);	
	if(file.is_open())
	{
		while (getline(file, line))
		{
			ShaderText += line;
			if (line.find("version") != std::string::npos)
				ShaderText += '\n';
		}

	GLint Lengths;

    Lengths = strlen(ShaderText.c_str());
	const char *c_str = ShaderText.c_str();
    glShaderSource(id, 1, &c_str, &Lengths);
    glCompileShader(id);

    //check for compilation errors
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(id, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", type, InfoLog);
    }
    glAttachShader(this->m_programId, id);
	
	}
	else std::cout << "Could not find " << type << std::endl;
}

void Shader::setTransformFeedbackVaryings(const char* varyings)
{

}

GLuint Shader::getShaderID()
{
	return this->m_programId;
}