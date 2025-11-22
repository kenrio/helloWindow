#include "shader.hpp"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
	std::string		vertexCode;
	std::string		fragmentCode;
	std::ifstream	vShaderFile;
	std::ifstream	fShaderFile;

	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream	vShaderStream;
		std::stringstream	fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure &e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" <<
		e.what() << "\n -- --------------------------------------------------- -- " << std::endl;
	}

	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();

	unsigned int	vertex;
	unsigned int	fragment;

	vertex = createShader(vShaderCode, GL_VERTEX_SHADER);
	fragment = createShader(fShaderCode, GL_FRAGMENT_SHADER);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void	Shader::use(void)
{
	glUseProgram(ID);
	return ;
}

void	Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	return ;
}

void	Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	return ;
}

void	Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	return ;
}

unsigned int	Shader::createShader(const char *shaderCode, GLenum type)
{
	unsigned int	shader;

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);

	std::string	typeStr;

	typeStr = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
	checkCompileErrors(shader, typeStr);

	return (shader);
}

void	Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int		success;
	char	infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
			<< infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
			<< infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	return ;
}
