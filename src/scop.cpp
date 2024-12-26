/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:47:17 by palucena          #+#    #+#             */
/*   Updated: 2024/12/26 14:38:43 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

void	throwError(const char *str) {
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

int main() {
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

	GLuint	VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint	programID = LoadShaders("src/shaders/vertexShader.glsl", "src/shaders/fragmentShader.glsl");

	GLuint	MatrixID = glGetUniformLocation(programID, "MVP");
	// Projection matrix
	glm::mat4	projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// View (camera) matrix
	glm::mat4	view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	// Model matrix
	glm::mat4	model = glm::mat4(1.0f);
	// MVP (model view projection) matrix
	glm::mat4	MVP = projection * view * model;

	static const GLfloat	g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLuint	vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	do {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;
}
