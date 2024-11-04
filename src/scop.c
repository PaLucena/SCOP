#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int	main(void) {
	if (!glfwInit()) {
		fprintf(stderr, "Error at initializing GLFW\n");
		return (-1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Not old OpenGl

	GLFWwindow	*window = glfwCreateWindow(800, 800, "SCOP", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		return (1);
	}
	glfwMakeContextCurrent(window); // Initializing GLEW
	glewExperimental = true; // Base profile needed
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Error at initializing GLEW\n");
		return (-1);
	}

	glfwTerminate();
}