/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadShaders.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:47:07 by palucena          #+#    #+#             */
/*   Updated: 2024/12/23 18:25:57 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

GLuint	LoadShaders(const char *vertex_file_path, const char *fragment_file_path) {
	GLuint	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string		VertexShaderCode;
	std::ifstream	VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s\n", vertex_file_path);
		return 0;
	}

	std::string		FragmentShaderCode;
	std::ifstream	FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream	sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint	result = GL_FALSE;
	int		infoLogLength;

	std::cout << "Compiling shader: " << vertex_file_path << std::endl;
	char const	*VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);
	
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char>	VertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, infoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cout << &VertexShaderErrorMessage[0] << std::endl;
	}

	std::cout << "Compiling shader: " << fragment_file_path << std::endl;
	const char	*FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);
	
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		std::cout << &fragmentShaderErrorMessage[0] << std::endl;
	}

	std::cout << "Linking program" << std::endl;
	GLuint	programID = glCreateProgram();
	glAttachShader(programID, VertexShaderID);
	glAttachShader(programID, FragmentShaderID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char>	programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		std::cout << &programErrorMessage[0] << std::endl;
	}

	glDetachShader(programID, VertexShaderID);
	glDetachShader(programID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return programID;
}
