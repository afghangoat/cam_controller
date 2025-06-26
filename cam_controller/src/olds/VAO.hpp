#ifndef VAO_HPP
#define VAO_HPP

#include <GL/glew.h>
#include "VBO.hpp"

class VAO{
	public:
		GLuint ID;
		
		VAO();
		
		void LinkVBO(VBO& vbo, GLuint layout);
		void Bind();
		void Unbind();
		void Delete();
};

#endif