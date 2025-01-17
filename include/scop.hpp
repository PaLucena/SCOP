/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:47:21 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 19:33:06 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_HPP
# define SCOP_HPP

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "math.hpp"

#define WIDTH 1024
#define HEIGHT 768

void	throwError(const std::string &str);

// loadShaders.cpp
GLuint	LoadShaders(const char *vertex_file_path, const char *fragmen_file_path);

// loadBMP.cpp
GLuint	loadBMP(const std::string &imgPath);

// loadOBJ
bool	loadOBJ(const std::string path, std::vector<std::vector<double>> &outVertices, std::vector<std::vector<double>> &outUVs, std::vector<std::vector<double>> &outNormals);

// controls.cpp
std::vector<std::vector<double>>	getProjectionMatrix();
std::vector<std::vector<double>>	getViewMatrix();
void	computeMatricesFromInput(GLFWwindow	*window);

#endif