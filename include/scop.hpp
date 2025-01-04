/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:47:21 by palucena          #+#    #+#             */
/*   Updated: 2025/01/04 11:22:10 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_HPP
# define SCOP_HPP

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WIDTH 1024
#define HEIGHT 768

void	throwError(const std::string &str);

// loadShaders.cpp
GLuint	LoadShaders(const char *vertex_file_path, const char *fragmen_file_path);

// loadBMP.cpp
GLuint	loadBMP(const std::string &imgPath);

// controls.cpp
glm::mat4	getProjectionMatrix();
glm::mat4	getViewMatrix();
void	computeMatricesFromInput(GLFWwindow	*window);

#endif