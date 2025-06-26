#include "VAO.hpp"

VAO::VAO(){
	glGenVertexArrays(1,&ID);
}

void VAO::LinkAttrib(VBO& vbo, GLuint layout,GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset){
	vbo.Bind();
	
	glVertexAttribPointer(layout/*inpos*/,numComponents,type,GL_FALSE,stride,offset); //or (void*)0
	glEnableVertexAttribArray(layout);
	
	vbo.Unbind();
}
void VAO::Bind(){
	glBindVertexArray(ID);
}
void VAO::Unbind(){
	glBindVertexArray(0);
}
void VAO::Delete(){
	glDeleteVertexArrays(1,&ID);
}