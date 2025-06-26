#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "./external/stb_image.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, /*GLenum format,*/ GLenum pixelType){
	//Texture
	type=texType;
	int widthImg;
	int heightImg;
	int numColCh;
	//(numColCh == 4 ? GL_RGBA : GL_RGB FOR rgb test
	
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image,&widthImg,&heightImg,&numColCh,0);
	//Example for image: "./src/imports/textures/bg_start.png"
	if (!bytes) {
		std::cerr << "Failed to load texture"<< image<<"!" << std::endl;
	}
	
	//GLuint texture;
	glGenTextures(1,&ID);
	glActiveTexture(slot);
	glBindTexture(texType,ID);
	
	glTexParameteri(texType,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	//Horizontal
	glTexParameteri(texType,GL_TEXTURE_WRAP_S,GL_REPEAT);
	//Vertical
	glTexParameteri(texType,GL_TEXTURE_WRAP_T,GL_REPEAT);
	//For clamp to border
	/*
	float flatColor[]={1.0f,1.0f,1.0f,1.0f};
	glTexParameterfv(texType,GL_TEXTURE_BORDER_COLOR,flatColor);
	*/
	//Gen. texture
	
	//For transparent : GL_RGBA
	//For opaque : GL_RGB
	glTexImage2D(texType,0,(numColCh == 4 ? GL_RGBA : GL_RGB),widthImg,heightImg,0,(numColCh == 4 ? GL_RGBA : GL_RGB),pixelType,bytes);
	glGenerateMipmap(texType);
	
	stbi_image_free(bytes);
	glBindTexture(texType,0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}