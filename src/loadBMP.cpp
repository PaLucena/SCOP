/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadBMP.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:47:49 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 21:54:47 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

GLuint	loadBMP(const std::string &imgPath) {
	std::cout << "Reading image: " << imgPath << std::endl;
	
	unsigned char	header[54];
	unsigned char	*data;
	unsigned int	dataPos;
	unsigned int	imgSize;
	unsigned int	width, height;

	FILE *file = fopen(imgPath.c_str(), "rb");
	if (!file) 
		throwError(imgPath + "could not be opened");
	
	if (fread(header, 1, 54, file) != 54)
		throwError("Not a correct BMP file");
	
	if (header[0] != 'B' || header[1] != 'M') {
		fclose(file);
		throwError("Not a correct BMP file");
	}

	if (*(int *)&(header[0x1E]) != 0 || *(int *)&(header[0x1C])!=24) {
		fclose(file);
		throwError("Not a correct BMP file");
	}

	dataPos = *(int *)&(header[0x0A]);
	imgSize = *(int *)&(header[0x22]);
	width = *(int *)&(header[0x12]);
	height = *(int *)&(header[0x16]);

	if (imgSize == 0)
		imgSize = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;
	
	data = new unsigned char [imgSize];
	
	fread(data, 1, imgSize, file);
	
	fclose (file);
	
	GLuint	textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	delete [] data;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return (textureID);
}
