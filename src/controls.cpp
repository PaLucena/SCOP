/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:34:48 by palucena          #+#    #+#             */
/*   Updated: 2025/01/04 11:37:36 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

glm::mat4	projectionMatrix;
glm::mat4	viewMatrix;

glm::vec3	position = glm::vec3(0, 0, 5);
float		horizontalAngle = 3.14f;
float		verticalAngle = 0.0f;
float		FoV = 45.0f;

float		speed = 3.0f;
float		mouseSpeed = 0.005f;

int			width;
int			height;

glm::mat4	getProjectionMatrix() {
	return (projectionMatrix);
}

glm::mat4	getViewMatrix() {
	return (viewMatrix);
}

void	computeMatricesFromInput(GLFWwindow	*window) {
	static double	lastTime = glfwGetTime();
	double			currTime = glfwGetTime();
	float			deltaTime = float(currTime - lastTime);

	double	xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);

	horizontalAngle += mouseSpeed * float(width / 2 - xpos);
	verticalAngle += mouseSpeed * float(height / 2 - ypos);
	
	glm::vec3	direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3	right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	glm::vec3	up = glm::cross(right, direction);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		position += direction * deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		position -= direction * deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		position += right * deltaTime * speed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		position -= right * deltaTime * speed;

	projectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(
		position,				// Camera is here
		position + direction,	// Camera looks here: same position plus "direction"
		up						// Head is up (set to 0,-1,0 to look upside-down)
	);
	
	lastTime=currTime;
}