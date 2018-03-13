#include "Shader.h"
namespace fs = std::experimental::filesystem;
Shader::Shader()
{
	Shader::ProgramID = glCreateProgram();
	for (auto & p : fs::directory_iterator(SHADER_PATH "Simple/"))
		std::cout << p << std::endl;
}


void Shader::SetupVertexShader(std::string file_name)
{
	std::string ShaderText;
	std::ifstream file;
	std::string line;

	Shader::VertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	file_name = SHADER_PATH + file_name;

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
    glShaderSource(Shader::VertexShaderID, 1, &c_str, &Lengths);    
    glCompileShader(Shader::VertexShaderID);

    //check for compilation errors
    GLint success;
    glGetShaderiv(Shader::VertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(Shader::VertexShaderID, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", GL_VERTEX_SHADER, InfoLog);
    }
    glAttachShader(Shader::ProgramID, Shader::VertexShaderID);
	
	}
	else std::cout << "Could not find Vertex Shader" << std::endl;
}

void Shader::SetupGeometryShader(std::string file_name)
{
	std::string ShaderText;
	std::ifstream file;
	std::string line;

	Shader::GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

	file_name = SHADER_PATH + file_name;

	file.open(file_name, std::ios::in);
	if (file.is_open())
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
		glShaderSource(Shader::GeometryShaderID, 1, &c_str, &Lengths);
		glCompileShader(Shader::GeometryShaderID);

		//check for compilation errors
		GLint success;
		glGetShaderiv(Shader::GeometryShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar InfoLog[1024];
			glGetShaderInfoLog(Shader::GeometryShaderID, sizeof(InfoLog), NULL, InfoLog);
			fprintf(stderr, "Error compiling shader type %d: '%s'\n", GL_GEOMETRY_SHADER, InfoLog);
		}
		glAttachShader(Shader::ProgramID, Shader::GeometryShaderID);

	}
	else std::cout << "Could not find Geometry Shader" << file_name << std::endl;
}

void Shader::SetupFragmentShader(std::string file_name)
{
	std::string ShaderText;
	std::ifstream file;
	std::string line;

	Shader::FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	file_name = SHADER_PATH + file_name;

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
    glShaderSource(Shader::FragmentShaderID, 1, &c_str, &Lengths);    
    glCompileShader(Shader::FragmentShaderID);

    //check for compilation errors
    GLint success;
    glGetShaderiv(Shader::FragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(Shader::FragmentShaderID, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", GL_FRAGMENT_SHADER, InfoLog);
    }
    glAttachShader(Shader::ProgramID, Shader::FragmentShaderID);


	}
	else std::cout << "Could not find Fragment Shader" << file_name << std::endl;
}

void Shader::setTransformFeedbackVaryings(const char* varyings)
{

}
void Shader::LinkShader()
{
	//setup final shader program
	glLinkProgram(Shader::ProgramID);
	glValidateProgram(Shader::ProgramID);

}

GLuint Shader::getShaderID()
{
	return Shader::ProgramID;
}