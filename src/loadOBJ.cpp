/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadOBJ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:48:08 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 21:59:23 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

bool	loadOBJ(const std::string path, std::vector<std::vector<double>> &outVertices, std::vector<std::vector<double>> &outUVs, std::vector<std::vector<double>> &outNormals) {
	std::vector<unsigned int>	vertexIndices, uvIndices, normalIndices;
	std::vector<std::vector<double>>		tempVertices;
	std::vector<std::vector<double>>		tempUVs;
	std::vector<std::vector<double>>		tempNormals;

	FILE	*file = fopen(path.c_str(), "r");
	if (file  == NULL) {
		std::cerr << "Impossible to open file: " << path << std::endl;
		return (false);
	}

	while (1) {
		char	lineHeader[128];
		std::cout << "HOLA\n";
		int		res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break ;
		if (strcmp(lineHeader, "v") == 0) {
			std::vector<double>	vertex(3);
			std::cout << "1\n";
			fscanf(file, "%lf %lf %lf\n", &vertex[0], &vertex[1], &vertex[2]);
			std::cout << "1.5\n";
			tempVertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			std::vector<double>	uv;
			std::cout << "2\n";
			fscanf(file, "%lf %lf\n", &uv[0], &uv[1]);
			tempUVs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			std::vector<double>	normal;
			std::cout << "3\n";
			fscanf(file, "%lf %lf %lf\n", &normal[0], &normal[1], &normal[2]);
			tempNormals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string		vertex1, vertex2, vertex3;
			unsigned int	vertexIndex[3], uvIndex[3], normalIndex[3];
			std::cout << "4\n";
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
		std::vector<double>		vertex = tempVertices[vertexIndex - 1];
		std::vector<double>		uv = tempUVs[uvIndex - 1];
		std::vector<double>		normal = tempNormals[normalIndex - 1];
		outVertices.push_back(vertex);
		outUVs.push_back(uv);
		outNormals.push_back(normal);
	}
	fclose(file);
	return (true);
}