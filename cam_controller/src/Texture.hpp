#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "shaderClass.hpp"
#include <GL/glew.h>
class Texture{
	public:
		GLuint ID;
		GLuint type; //TODO move these to private
		
		Texture(const char* image, GLenum texType, GLenum slot,/* GLenum format, */GLenum pixelType);
		
		void texUnit(Shader& shader,const char* uniform,GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
};

#endif