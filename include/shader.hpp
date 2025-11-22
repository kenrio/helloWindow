#ifndef SHADER_HPP
# define SHADER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>

class Shader
{

public:
	unsigned int	ID;

	Shader(const char *vertexPath, const char *fragmentPath);

	void	use(void);

	void	setBool(const std::string &name, bool value) const;
	void	setInt(const std::string &name, int value) const;
	void	setFloat(const std::string &name, float value)const;

private:
	void			checkCompileErrors(unsigned int shader, std::string type);
	unsigned int	createShader(const char *shaderCode, GLenum type);

};

# endif
