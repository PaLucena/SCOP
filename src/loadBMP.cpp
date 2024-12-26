/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadBMP.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:47:49 by palucena          #+#    #+#             */
/*   Updated: 2024/12/26 17:35:28 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

GLuint	loadBMP(const std::string &imgPath) {
	std::cout << "Reading image: " << imgPath << std::endl;
	
	// Data read from the header of the BMP file
	unsigned char	header[54];
	// Actual RGB data
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

	// Some BMP files are misformatted, guess missing information
	if (imgSize == 0)
		imgSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)
		dataPos = 54; // The BMP header is done that way
	
	// Create a buffer
	data = new unsigned char [imgSize];
	
	// Read the actual data from the file into the buffer
	fread(data, 1, imgSize, file);
	
	// Everything is in memory now, the file can be closed.
	fclose (file);
	
	// Create an OpenGL texture
	GLuint	textureID;
	glGenTextures(1, &textureID);

	// Bind the newly created texture: all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	delete [] data;
	
	// Nice trilinear filtering...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically
	glGenerateMipmap(GL_TEXTURE_2D);

	return (textureID);
}
