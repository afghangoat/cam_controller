#ifndef EBO_HPP
#define EBO_HPP

#include <GL/glew.h>
class EBO{
	public:
		GLuint ID;
		EBO(GLuint* indices, GLsizeiptr size);
		
		void Bind();
		void Unbind();
		void Delete();
};

#endif