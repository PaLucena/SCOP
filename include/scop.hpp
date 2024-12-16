/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:47:21 by palucena          #+#    #+#             */
/*   Updated: 2024/12/16 01:41:07 by palucena         ###   ########.fr       */
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
using namespace glm;

#define WIDTH 1024
#define HEIGHT 768

GLuint	LoadShaders(const char *vertex_file_path, const char *fragmen_file_path);

#endif