/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadOBJ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:48:08 by palucena          #+#    #+#             */
/*   Updated: 2025/01/07 19:04:21 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

bool	loadOBJ(const std::string path, std::vector<glm::vec3> &outVertices, std::vector<glm::vec2> &outUVs, std::vector<glm::vec3> &outNormals) {
	std::vector<unsigned int>	vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3>		tempVertices;
	std::vector<glm::vec2>		tempUVs;
	std::vector<glm::vec3>		tempNormals;

	FILE	*file = fopen(path.c_str(), "r");
	if (file  == NULL) {
		std::cerr << "Impossible to open file" << std::endl;
		return (false);
	}

	while (1) {
		char	lineHeader[128];
		int		res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break ;
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3	vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2	uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			tempUVs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3	normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string		vertex1, vertex2, vertex3;
			unsigned int	vertexIndex[3], uvIndex[3], normalIndex[3];
			int				matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				std::cerr << "File couldn't be read by parser" << std::endl;
				return (false);
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			char	randomBuffer[1000];
			fgets(randomBuffer, 1000, file);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int	vertexIndex = vertexIndices[i];
		unsigned int	uvIndex = uvIndices[i];
		unsigned int	normalIndex = normalIndices[i];
		glm::vec3		vertex = tempVertices[vertexIndex - 1];
		glm::vec2		uv = tempUVs[uvIndex - 1];
		glm::vec3		normal = tempNormals[normalIndex - 1];
		outVertices.push_back(vertex);
		outUVs.push_back(uv);
		outNormals.push_back(normal);
	}
	fclose(file);
	return (true);
}