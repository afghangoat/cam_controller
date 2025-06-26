#include "VAO.hpp"

VAO::VAO(){
	glGenVertexArrays(1,&ID);
}

void VAO::LinkVBO(VBO& vbo, GLuint layout){
	vbo.Bind();
	
	glVertexAttribPointer(layout/*inpos*/,3,GL_FLOAT,GL_FALSE,0,(void*)0); //or (void*)0
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