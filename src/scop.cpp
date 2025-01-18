/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:47:17 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 15:41:37 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

void	throwError(const std::string &str) {
	std::cerr << str << std::endl;
	exit(-1);
}

int	kickstartGLFW() {
	if (!glfwInit())
		throwError("Error at initializing GLFW");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return 0;
}

int main(int ac, char **av) {
	if (ac != 2)
		throwError("Wrong number of arguments");

	kickstartGLFW();

	GLFWwindow	*window;
	window = glfwCreateWindow(WIDTH, HEIGHT, "SCOP", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		throwError("Error at opening GLFW window");
	}
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
		throwError("Error at initializing GLEW");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	GLuint	VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint	programID = LoadShaders("src/shaders/vertexShader.glsl", "src/shaders/fragmentShader.glsl");

	GLuint	MatrixID = glGetUniformLocation(programID, "MVP");

	GLuint texture = loadBMP("resources/uvtemplate.bmp");
	GLuint textureID  = glGetUniformLocation(programID, "myTextureSampler");

	std::vector<std::vector<double>> vertices;
	std::vector<std::vector<double>>	UVs;
	std::vector<std::vector<double>>	normals;
	if (loadOBJ("resources/" + std::string(av[1]), vertices, UVs, normals) == false)
		exit (1);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(std::vector<std::vector<double>>), &vertices[0], GL_STATIC_DRAW);

	GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(std::vector<std::vector<double>>), &UVs[0], GL_STATIC_DRAW);

	GLuint normalBuffer;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(std::vector<std::vector<double>>), &normals[0], GL_STATIC_DRAW);

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		computeMatricesFromInput(window);
		std::vector<std::vector<double>>	projectionM = getProjectionMatrix();
		std::vector<std::vector<double>>	viewM = getViewMatrix();
		std::vector<std::vector<double>>	modelM(4, std::vector<double>(4, 0.0));
		for (size_t i = 0; i < 4; ++i) {
			modelM[i][i] = 1.0;
		}

		std::vector<std::vector<double>>	MVP = multiplyMatrix(multiplyMatrix(projectionM, viewM), modelM);

		GLfloat	value = static_cast<GLfloat>(MVP[0][0]);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &value);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(textureID, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &textureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;
}
