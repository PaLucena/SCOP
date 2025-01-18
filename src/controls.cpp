/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:34:48 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 19:31:53 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

std::vector<std::vector<double>>	projectionMatrix;
std::vector<std::vector<double>>	viewMatrix;

std::vector<double>	position = {0, 0, 5};
double	horizontalAngle = 3.14f;
double	verticalAngle = 0.0f;
double	FoV = 45.0f;

double	speed = 3.0f;
double	mouseSpeed = 0.005f;

int		width;
int		height;

std::vector<std::vector<double>>	getProjectionMatrix() {
	return (projectionMatrix);
}

std::vector<std::vector<double>>	getViewMatrix() {
	return (viewMatrix);
}

void	computeMatricesFromInput(GLFWwindow	*window) {
	static double	lastTime = glfwGetTime();
	double			currTime = glfwGetTime();
	double			deltaTime = currTime - lastTime;

	double	xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);

	horizontalAngle += mouseSpeed * width / 2 - xpos;
	verticalAngle += mouseSpeed * height / 2 - ypos;
	
	std::vector<double>	direction = {
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	};

	std::vector<double>	right = {
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	};

	std::vector<double>	up = crossProduct(right, direction);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		position = position + direction * deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		position = position - direction * deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		position = position + right * deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		position = position - right * deltaTime * speed;

	projectionMatrix = perspective(toRadians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	viewMatrix = lookAt(
		position,				// Camera is here
		position + direction,	// Camera looks here: same position plus "direction"
		up						// Head is up (set to 0,-1,0 to look upside-down)
	);
	
	lastTime=currTime;
}
