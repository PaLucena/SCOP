#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int	main(void) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow	*window(800, 800, "SCOP", NULL, NULL);
	if (!window) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return (1);
	}
	glfw

	glfwTerminate();
}